#include <Arduino.h>
#include "effect_octave.h"
#include "dspinst.h"

void AudioEffectOctave::update(void) {
  audio_block_t *block;
  short *bp;
  if(!on) {
      block = receiveWritable(0);
      if(block) {
          transmit(block,0);
          release(block);
      }
  }
  else if(on)
  {
      Serial.println("buffer");
      block = receiveWritable(0);
      if(block) {
          bp = block->data;

          // WAY 1 - get rid of half of the values, copy those after
          /*int out = 0;
          for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i+=2){
            bp[out++] = bp[i];
          }
          for(int i = 0; i < AUDIO_BLOCK_SAMPLES/2; i+=2){
            bp[out++] = bp[i];
          }*/

          // WAY 2 - get rid of half the values, interpolate between
          int out = 0;
          for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i+=4){
            temp[out++] = bp[i];
            //Serial.printf("val: %d, index: %i - ", bp[i], (out-1));
          }
          temp[out] = 0;
          //Serial.printf("val: %d, index: %i \n", temp[out], out);

          out = 0;
          short div = 0.5;
          short prod;
          for(int i = 0; i < AUDIO_BLOCK_SAMPLES;){
            prod = temp[out] + temp[out+1];
            bp[i++] = temp[out++];
            //Serial.printf("val: %d, index: %i - ", bp[i-1], (i-1));
            bp[i++] = multiply_16bx16b(prod, div);
            //Serial.printf("val: %d, index: %i - ", bp[i-1], (i-1));
          }

          out = 0;
          for(int i = 0; i < AUDIO_BLOCK_SAMPLES;){
            prod = temp[out] + temp[out+1];
            bp[i++] = temp[out++];
            //Serial.printf("val: %d, index: %i - ", bp[i-1], (i-1));
            bp[i++] = multiply_16bx16b(prod, div);
            //Serial.printf("val: %d, index: %i - ", bp[i-1], (i-1));
          }

          // WAY 3 - fft way - need to shift the whole spectrum somehow
          // note: just the two below lines don't work - should just pass through audio
          //use fft
          //arm_cfft_q15(&arm_cfft_sR_q15_len128, bp, 0, 1);
          //invert fft
          //arm_cfft_q15(&arm_cfft_sR_q15_len128, bp, 1, 1);


          transmit(block,0);
          release(block);
      }
  }
}

void AudioEffectOctave::begin()
{
    //Serial.println("begin");
    this->on = true;
    //Serial.println("Done begin");
}

void AudioEffectOctave::turnOff()
{
    //Serial.println("Sanity check");
    this->on = false;
}
