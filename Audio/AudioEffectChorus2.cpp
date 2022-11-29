#include <Arduino.h>
#include "AudioEffectChorus2.h"


//update is called every 128 samples/2.9 ms
//attempting to write 29 ms delay chorus
void AudioEffectChorus2::changeNum(int numVoices)
{
  //Serial.println("changeNum");
  num_voices = numVoices;
}


void AudioEffectChorus2::update(void) {
  
  //Serial.println("update");
  int start = micros();
  audio_block_t *block;
  block = receiveWritable(0);
  //new code with one array, remember to change private variables when switching
  
    if(block)
    {
      short *bp = block->data;
      //Serial.println("firstloop");
      //Serial.println("after first loop");
      //Serial.println(num_voices);
      if(num_voices == 0)
      {
        short* cpy = bp;
        buffer.insertBlock(cpy);
        
        
        transmit(block,0);
        //Serial.println("after trasnmit");
        release(block);
        //Serial.println("after0");
      }
      else if(num_voices == 1)
      {
        //Serial.println("one voice");
        
        short* cpy = bp;
        buffer.insertBlock(cpy);
        
        
        for(int i = 20*AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES; i++)
        {
          short current1 = buffer.getValue(i);
          bp[i-20*AUDIO_BLOCK_SAMPLES] = (bp[i-20*AUDIO_BLOCK_SAMPLES] +current1)/2; 
        }
        transmit(block,0);
        release(block);
      }
      else if(num_voices == 2)
      {
        
        short* cpy = bp;
        buffer.insertBlock(cpy);
        
        
        for(int i = 20*AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES; i++)
        {
          short current1 = buffer.getValue(i);
          short current2 = buffer.getValue((i-10*AUDIO_BLOCK_SAMPLES));
          bp[i-20*AUDIO_BLOCK_SAMPLES] = (bp[i-20*AUDIO_BLOCK_SAMPLES] +current1+current2)/3; 
        }
        transmit(block,0);
        release(block);
      }
      else if(num_voices == 3)
      {
        
        short* cpy = bp;
        buffer.insertBlock(cpy);
        
        for(int i = 20*AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES; i++)
        {
          short current1 = buffer.getValue(i);
          short current2 = buffer.getValue((i-10*AUDIO_BLOCK_SAMPLES));
          short current3 = buffer.getValue((i-20*AUDIO_BLOCK_SAMPLES));
          short toAdd = (bp[i-20*AUDIO_BLOCK_SAMPLES] + current1)/4;
          toAdd += current2/4;
          toAdd += current3/4;
          bp[i-20*AUDIO_BLOCK_SAMPLES] = toAdd;
          //bp[i-20*AUDIO_BLOCK_SAMPLES] = (bp[i-20*AUDIO_BLOCK_SAMPLES] + current1)/4 + (current2 + current3)/4; 
        }
        transmit(block,0);
        release(block);
      }
      
      //Serial.println("endloop");
    }
    int end = micros();
    Serial.println(end - start);
}