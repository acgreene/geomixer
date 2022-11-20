#include <Arduino.h>
#include "effect_myreverb.h"

void AudioEffectMyReverb::init(void)
{
  Serial.println("init");
  int i;

  apfs[0].in_queue = apf1_inqueue;
  apfs[0].out_queue = apf1_outqueue;
  apfs[0].delay = APF_D1;
  apfs[1].in_queue = apf2_inqueue;
  apfs[1].out_queue = apf2_outqueue;
  apfs[2].delay = APF_D2;
  apfs[2].in_queue = apf3_inqueue;
  apfs[2].out_queue = apf3_outqueue;
  apfs[2].delay = APF_D3;

  for (i = 0; i < 3; i++) {
    apfs[i].gain = APF_G;
  }

  combs[0].queue = comb1_queue;
  combs[0].delay = COMB_D1;
  combs[0].gain = COMB_G1;
  combs[1].queue = comb2_queue;
  combs[1].delay = COMB_D2;
  combs[1].gain = COMB_G2;
  combs[2].queue = comb3_queue;
  combs[2].delay = COMB_D3;
  combs[2].gain = COMB_G3;
  combs[3].queue = comb4_queue;
  combs[3].delay = COMB_D4;
  combs[3].gain = COMB_G4;

}

void AudioEffectMyReverb::clear_buffers(void)
{
  memset(apf1_inqueue, 0, sizeof(apf1_inqueue));
  memset(apf1_outqueue, 0, sizeof(apf1_outqueue));
  memset(apf2_inqueue, 0, sizeof(apf2_inqueue));
  memset(apf2_outqueue, 0, sizeof(apf2_outqueue));
  memset(apf3_inqueue, 0, sizeof(apf3_inqueue));
  memset(apf3_outqueue, 0, sizeof(apf3_outqueue));

  memset(comb1_queue, 0, sizeof(comb1_queue));
  memset(comb2_queue, 0, sizeof(comb2_queue));
  memset(comb3_queue, 0, sizeof(comb3_queue));
  memset(comb4_queue, 0, sizeof(comb4_queue));
}

void AudioEffectMyReverb::begin(void)
{
  init();
  clear_buffers();
  Serial.println("begin");
  on = true;
}

void AudioEffectMyReverb::shiftLeft(int16_t* queue, uint16_t delayAmount)
{
    //Serial.println("Shift Left");
    for(int i = AUDIO_BLOCK_SAMPLES; i < delayAmount+AUDIO_BLOCK_SAMPLES; ++i)
    {
        queue[i-AUDIO_BLOCK_SAMPLES] = queue[i];
    }
}

void AudioEffectMyReverb::insertBlock(int16_t* queue, int16_t* block, uint16_t delayAmount)
{
    shiftLeft(queue, delayAmount); //shift the queue
    Serial.println("Insert Block");
    int16_t* cpy = block; //copy pointer to the block to insert
    for(int i = delayAmount; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
    {
        queue[i] = *cpy++;
    }
}

void AudioEffectMyReverb::turnOff()
{
    on = false;
}

void AudioEffectMyReverb::turnOn()
{
    on = true;
}

// all-pass filter: y[n] = (−g·x[n]) + x[n−M] + (g·y[n−M])
void AudioEffectMyReverb::_run_apf(struct apf *apf, int16_t *in_buf, int16_t *out_buf)
{
  int16_t g, n;
  g = apf->gain;

  for (n = 0; n < AUDIO_BLOCK_SAMPLES; n++) {
      out_buf[n] = -g*(in_buf[n]) + apf->in_queue[n] + g*(apf->out_queue[n]);
  }
}

// comb filter: y[n] = x[n] + g·y[n−M]
void AudioEffectMyReverb::_run_comb(struct comb *comb, int16_t *in_buf, int16_t *out_buf)
{
  int16_t g, n;
  g = comb->gain;

  for (n = 0; n < AUDIO_BLOCK_SAMPLES; n++) {
      out_buf[n] = in_buf[n] + g*(comb->queue[n]);
  }
}

void AudioEffectMyReverb::update(void)
{
  audio_block_t *block;
  int16_t *bp;
  int16_t i;

  if(!on) {
    Serial.print("update - off");
    block = receiveWritable(0);
    if(block) {
      Serial.println(" - got block");
      bp = block->data;
      for(i = 0; i < 3; i++){
        insertBlock(apfs[i].in_queue, bp, apfs[i].delay);
        insertBlock(apfs[i].out_queue, bp, apfs[i].delay);
      }
      for(i = 0; i < 4; i++){
        insertBlock(combs[i].queue, bp, combs[i].delay);
      }
      transmit(block,0);
      release(block);
    }
    Serial.println(" - no block");
  }
  else{
    Serial.println("update - on");
    int16_t cpy[AUDIO_BLOCK_SAMPLES]; //copy of input
    block = receiveWritable(0);
    if(block) {
      Serial.println(" - got block");
      bp = block->data;
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) //do copy input
      {
          cpy[i] = bp[i];
      }

      _run_apf(&apfs[0], bp, aux_buf); //run apf1 -> output into aux
      _run_apf(&apfs[1], aux_buf, aux_buf); //run apf2
      _run_apf(&apfs[2], aux_buf, aux_buf); //run apf3

      //send input parallel into 3 comb filters using another buff
      _run_comb(&combs[0], aux_buf, sum_buf); //send to sum buff
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i) //add sum buff to bp output buf
      {
        bp[i] = sum_buf[i];
      }

      _run_comb(&combs[1], aux_buf, sum_buf); //repeat
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
      {
        bp[i] += sum_buf[i];
      }

      _run_comb(&combs[2], aux_buf, sum_buf);
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
      {
        bp[i] += sum_buf[i];
      }

      _run_comb(&combs[3], aux_buf, sum_buf);
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
      {
        bp[i] += sum_buf[i];
      }

      for(i = 0; i < 3; i++){ //move copy of input into in_queue, move output into out_queue
        insertBlock(apfs[i].in_queue, cpy, apfs[i].delay);
        insertBlock(apfs[i].out_queue, bp, apfs[i].delay);
      }
      for(i = 0; i < 4; i++){ //move output into comb queues
        insertBlock(combs[i].queue, bp, combs[i].delay);
      }

      transmit(block,0);
      release(block);
    }
  }
}
