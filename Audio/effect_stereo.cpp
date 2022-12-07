#include <Arduino.h>
#include "effect_stereo.h"

void AudioEffectStereo::update(void) {
  int temp_delay_val = delay_val;
  //int start = micros();
  audio_block_t *block, *b_new;
  short *bp;
  //Serial.println("run stereo");
  if(!on || (delay_val == 0)) {
      block = receiveWritable(0);
      if(block) {
          bp = block->data;
          buff.insertBlock(bp);
          transmit(block,0);
          release(block);
      }
  }
  else
  {
      //Serial.println("buffer");
      block = receiveWritable(0);
      if(block) {
          bp = block->data;

          buff.insertBlock(bp);
          b_new = allocate();
          for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
          {
              b_new->data[i] = buff.getValue((DELAY - temp_delay_val) + i);
          }

          transmit(b_new,0);
          release(b_new);
          release(block);
      }
  }
  //int end = micros();
  //int duration = end - start;
  //Serial.println(duration);
}

void AudioEffectStereo::setOn(bool b)
{
    this->on = b;
}

bool AudioEffectStereo::getOn(void)
{
    return this->on;
}

void AudioEffectStereo::mix(float val) //val from 0 to 1 guaranteed
{
    //val = floor(val * 10.) / 10.;
    val = (val * val * val * val) / 8.0;
    delay_val = val * DELAY; //make new delay val from 0-DELAY
    //Serial.println(delay_val);
}
