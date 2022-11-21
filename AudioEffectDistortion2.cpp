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
    

    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
    {

        if (abs((*bp)) > ((1/3)*float(AudioEffectDistortion2.max_)) && abs(*bp) < ((2/3)*float(AudioEffectDistortion2.max_))){
            *bp = (*bp/abs(*bp))*float(AudioEffectDistortion2.max_)*((3-pow((2-(*bp/abs(*bp))*(3.0*float(*bp)/float(AudioEffectDistortion2.max_))),2))/6);
        }

        
        
        else if (abs(*bp) > ((2/3)*float(AudioEffectDistortion2.max_))){
            *bp = (*bp/abs(*bp))*(1/2)*float(AudioEffectDistortion2.max_);
        }
        
        bp++;
      }
    
      Serial.println("0");
      transmit(block,0);
      Serial.println("after trasnmit");
      release(block);
      Serial.println("after0");
    }
}
