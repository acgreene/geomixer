#include <Arduino.h>
#include "AudioEffectDistortion2.h"


//update is called every 128 samples/2.9 ms
//attempting to write 29 ms delay chorus
//void AudioEffectDistortion2::changeNum()
//{
  
//}

void AudioEffectDistortion2::update(void) {
int start = micros();
  
  //Serial.println("update");
  audio_block_t *block;
  block = receiveWritable(0);
  if(block)
  {
    short *bp = block->data;
    //Serial.println("firstloop");
    //Serial.println("after first loop");

    //sign = 0x8000 & *bp < 0 ? -1 : 1
    // if necessary replace *bp/abs(*bp)
    
/*
TO DO: If necessary scale input and output depending on the desired sound
*/


    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
    {
        if (*bp != 0){
        if (abs(*bp) > ((1/3)*(float)(AudioEffectDistortion2::max_)) && abs(*bp) < ((2/3)*(float)(AudioEffectDistortion2::max_))){
            *bp = (*bp/abs(*bp))*(float)(AudioEffectDistortion2::max_)*((3-pow((2-(*bp/abs(*bp))*(3.0*(float)(*bp)/(float)(AudioEffectDistortion2::max_))),2))/6);
        }
        //This if statement above creates the curvature for the clipping when the signal is between 1/3 and 2/3 of the max
        
        
        else if (abs(*bp) > ((2/3)*(float)(AudioEffectDistortion2::max_))){
            *bp = (*bp/abs(*bp))*(1/2)*(float)(AudioEffectDistortion2::max_);
        }
        //This if statement above flattens the signal when it is beyond 2/3 of the max
        }
        
        bp++;
      }
    
      //Serial.println("0");
      transmit(block,0);
      //Serial.println("after trasnmit");
      release(block);
      //Serial.println("after0");
    }
int end = micros();
int duration = end - start;
Serial.println(duration);

}
