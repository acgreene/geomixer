#include <Arduino.h>
#include "AudioEffectDistortion2.h"


//update is called every 128 samples/2.9 ms
//attempting to write 29 ms delay chorus
void AudioEffectDistortion2::changeNum()
{
  
}

void AudioEffectDistortion2::update(void) {
  
  Serial.println("update");
  audio_block_t *block;
  block = receiveWritable(0);
  if(block)
  {
    short *bp = block->data;
    Serial.println("firstloop");
    Serial.println("after first loop");
    bp = bp/AudioEffectDistortion2.max_
    

    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
    {
        

        if (bp > 1/3 && bp < 2/3){
            bp = (3-((2-3*pow(bp,2)))/6);
        }
        else if (bp < (-1/3) && bp > (-2/3)){
            bp = (-1)*(3-((2+3*pow(bp,2)))/6);
        }
        else if (bp > 2/3){
            bp = 1/2;
        }
        else if (bp < -2/3){
            bp = -1/2;
        }
      }
    
      Serial.println("0");
      transmit(block,0);
      Serial.println("after trasnmit");
      release(block);
      Serial.println("after0");
    }
}