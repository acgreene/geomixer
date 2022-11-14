#include <Arduino.h>
#include "effect_myreverb.h"

void AudioEffectMyReverb::begin(void)
{
  on = true;
  int i;

  apf[0].in_queue = apf1_inqueue;
  apf[0].out_queue = apf1_outqueue;
  apf[0].delay = APF_D1;
  apf[1].in_queue = apf2_inqueue;
  apf[1].out_queue = apf2_outqueue;
  apf[2].delay = APF_D2;
  apf[2].in_queue = apf3_inqueue;
  apf[2].out_queue = apf3_outqueue;
  apf[2].delay = APF_D3;

  for (i = 0; i < 3; i++) {
    apf[i].gain = APF_G;
  }

  comb[0].queue = comb1_queue;
  comb[0].delay = COMB_D1;
  comb[0].gain = COMB_G1;
  comb[1].queue = comb2_queue;
  comb[1].delay = COMB_D2;
  comb[1].gain = COMB_G2;
  comb[2].queue = comb3_queue;
  comb[2].delay = COMB_D3;
  comb[2].gain = COMB_G3;
  comb[3].queue = comb4_queue;
  comb[3].delay = COMB_D4;
  comb[3].gain = COMB_G4;
}

void AudioEffectMyReverb::shiftLeft(short* queue, uint32_t delayAmount)
{
    //Serial.println("Shift Left");
    for(int i = AUDIO_BLOCK_SAMPLES; i < delayAmount+AUDIO_BLOCK_SAMPLES; ++i)
    {
        queue[i-AUDIO_BLOCK_SAMPLES] = queue[i];
    }
}

void AudioEffectMyReverb::insertBlock(short* queue, short* block, uint32_t delayAmount)
{
    shiftLeft(queue, delayAmount); //shift the queue
    //Serial.println("Insert Block");
    short* cpy = block; //copy pointer to the block to insert
    for(int i = delayAmount; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
    {
        queue[i] = *cpy++;
    }
    //Serial.println("end insert block");
}

void AudioEffectMyReverb::turnOff()
{
    on = false;
}

// all-pass filter: y[n] = (−g·x[n]) + x[n−M] + (g·y[n−M])
void AudioEffectMyReverb::run_apf(struct apf *apf, int32_t *in_buf, int32_t *out_buf)
{
  int32_t g;
  g = apf->gain;

  for (n = 0; n < AUDIO_BLOCK_SAMPLES; n++) {
      out_buf[n] = -g*(in_buf[n]) + apf->in_queue[n] + g*(apf->out_queue[n])
  }
}

// comb filter: y[n] = x[n] + g·y[n−M]
void AudioEffectMyReverb::run_comb(struct comb *comb, int32_t *in_buf, int32_t *out_buf)
{
  int32_t g;
  g = comb->gain;

  for (n = 0; n < AUDIO_BLOCK_SAMPLES; n++) {
      out_buf[n] = in_buf[n] + g*(comb->queue[n])
  }
}

void AudioEffectMyReverb::update(void)
{
  audio_block_t *block;
  short *bp;
  int i;

  if(!on) {
    block = receiveWritable(0);
    if(block) {
      bp = block->data;
      for(i = 0; i < 3; i++){
        insertBlock(apf[i]->in_queue, bp, apf[i]->delay);
        insertBlock(apf[i]->out_queue, bp, apf[i]->delay);
      }
      for(i = 0; i < 4; i++){
        insertBlock(comb[i]->queue, bp, comb[i]->delay);
      }
      transmit(block,0);
      release(block);
    }
  }
  else{
    short cpy[AUDIO_BLOCK_SAMPLES]; //copy of input
    block = receiveWritable(0);
    if(block) {
      bp = block->data;
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) //do copy input
      {
          cpy[i] = *(bp+i);
      }

      run_apf(&apf[0], cpy, aux_buf); //run apf1 -> output into aux
      run_apf(&apf[1], aux_buf, aux_buf); //run apf2
      run_apf(&apf[2], aux_buf, aux_buf); //run apf3

      //send input parallel into 3 comb filters using another buff
      run_comb(&comb[0], aux_buf, sum_buf); //send to sum buff
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) //add sum buff to bp output buf
      {
        *bp = sum_buf[i];
        bp++;
      }
      bp -= AUDIO_BLOCK_SAMPLES; //decrement to run next comb filter

      run_comb(&comb[1], aux_buf, sum_buf); //repeat
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
      {
        *bp += sum_buf[i];
        bp++;
      }
      bp -= AUDIO_BLOCK_SAMPLES;

      run_comb(&comb[2], aux_buf, sum_buf);
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
      {
        *bp += sum_buf[i];
        bp++;
      }
      bp -= AUDIO_BLOCK_SAMPLES;

      run_comb(&comb[3], aux_buf, sum_buf);
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
      {
        *bp += sum_buf[i];
        bp++;
      }
      bp -= AUDIO_BLOCK_SAMPLES;

      for(i = 0; i < 3; i++){ //move copy of input into in_queue, move output into out_queue
        insertBlock(apf[i]->in_queue, cpy, apf[i]->delay);
        insertBlock(apf[i]->out_queue, bp, apf[i]->delay);
      }
      for(i = 0; i < 4; i++){ //move output into comb queues
        insertBlock(comb[i]->queue, bp, comb[i]->delay);
      }

      transmit(block,0);
      release(block);
    }
  }
}
