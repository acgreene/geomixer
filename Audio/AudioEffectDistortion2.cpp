#include <Arduino.h>
#include "AudioEffectDistortion2.h"


  
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

    //Serial.println(*bp);
    for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
    {
        if (*bp != 0){
        if (abs(*bp) > ((output_scalar/3)) && abs(*bp) < ((2 * (output_scalar/3)))){
            //Serial.println(*bp);
            *bp = (*bp/abs(*bp))*(output_scalar)*((3-pow((2-(*bp/abs(*bp))*(3.0*(float)(*bp)/(float)(output_scalar))),2))/6);
        }
        //This if statement above creates the curvature for the clipping when the signal is between 1/3 and 2/3 of the max
        
        
        //else if (abs(*bp) > (2*(output_scalar/3))){
        //  //Serial.println((2*(output_scalar/3)));
        //    *bp = (*bp/abs(*bp))*(output_scalar/2);
        //}
        

        else{
          *bp = min(*bp, (*bp/abs(*bp))*(output_scalar/2));
        }
        //This if statement above flattens the signal when it is beyond 2/3 of the max and leaves it intact if it is less than 1/3
        
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
