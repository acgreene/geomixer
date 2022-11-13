#include <Arduino.h>
#include "AudioEffectChorus2.h"


//update is called every 128 samples/2.9 ms
//attempting to write 29 ms delay chorus
void AudioEffectChorus2::changeNum(int numVoices)
{
  Serial.println("changeNum");
  num_voices = numVoices;
}

void AudioEffectChorus2::update(void) {
  
  Serial.println("update");
  audio_block_t *block;
  block = receiveWritable(0);
  if(block)
  {
    short *bp = block->data;
    Serial.println("firstloop");
    Serial.println("after first loop");
    Serial.println(num_voices);
    if(num_voices == 0)
    {
      Serial.println("0");
      transmit(block,0);
      Serial.println("after trasnmit");
      release(block);
      Serial.println("after0");
    }
    else if(num_voices == 1)
    {
      short* cpy = bp;
      Serial.println("one voice");
      short cpy1[AUDIO_BLOCK_SAMPLES];
      for(int i = 0; i <AUDIO_BLOCK_SAMPLES; i++)
      {
        cpy1[i]=voice1[i];
      }
      for(int i = AUDIO_BLOCK_SAMPLES; i<11*AUDIO_BLOCK_SAMPLES;i++ )
      {
        voice1[i-AUDIO_BLOCK_SAMPLES] = voice1[i];
      }
      for(int i = 10*AUDIO_BLOCK_SAMPLES; i<11*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice1[i] = *cpy++;
      }
      cpy = bp;
      for(int i = 20*AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice2[i] = *cpy++;
      }
      cpy = bp;
      for(int i = 30*AUDIO_BLOCK_SAMPLES; i<31*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice3[i] = *cpy++;
      }
      cpy = bp;
      for(int i = 40*AUDIO_BLOCK_SAMPLES; i<41*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice4[i] = *cpy++;
      }
      for(int i = 0; i<AUDIO_BLOCK_SAMPLES; i++)
      {
        bp[i] = (bp[i] +cpy1[i])/2; 
      }
      transmit(block,0);
      release(block);
    }
    else if(num_voices == 2)
    {
      short cpy1[AUDIO_BLOCK_SAMPLES];
      short cpy2[AUDIO_BLOCK_SAMPLES];
      for(int i = 0; i <AUDIO_BLOCK_SAMPLES; i++)
      {
        cpy1[i]=voice1[i];
        cpy2[i] = voice2[i];
      }
      for(int i = AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES;i++ )
      {
        if(i<11*AUDIO_BLOCK_SAMPLES)
        {
          voice1[i-AUDIO_BLOCK_SAMPLES] = voice1[i];
        }
        voice2[i-AUDIO_BLOCK_SAMPLES]=voice2[i];
        
      }
      for(int i = 10*AUDIO_BLOCK_SAMPLES; i<11*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice1[i] = bp[i];
      }
      for(int i = 20*AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice2[i] = bp[i];
      }
      for(int i = 30*AUDIO_BLOCK_SAMPLES; i<31*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice3[i] = bp[i];
      }
      for(int i = 40*AUDIO_BLOCK_SAMPLES; i<41*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice4[i] = bp[i];
      }
      for(int i = 0; i<AUDIO_BLOCK_SAMPLES; i++)
      {
        bp[i] = (bp[i]/3 +cpy1[i]/3+cpy2[i]/3); 
      }
      transmit(block,0);
      release(block);
    }
    else if(num_voices == 3)
    {
      short cpy1[AUDIO_BLOCK_SAMPLES];
      short cpy2[AUDIO_BLOCK_SAMPLES];
      short cpy3[AUDIO_BLOCK_SAMPLES];
      for(int i = 0; i <AUDIO_BLOCK_SAMPLES; i++)
      {
        cpy1[i]=voice1[i];
        cpy2[i] = voice2[i];
        cpy3[i] = voice3[i];
      }
      for(int i = AUDIO_BLOCK_SAMPLES; i<31*AUDIO_BLOCK_SAMPLES;i++ )
      {
        if(i<11*AUDIO_BLOCK_SAMPLES)
        {
          voice1[i-AUDIO_BLOCK_SAMPLES] = voice1[i];
        }
        if(i<21*AUDIO_BLOCK_SAMPLES)
        {
          voice2[i-AUDIO_BLOCK_SAMPLES]=voice2[i];
        }
        voice3[i-AUDIO_BLOCK_SAMPLES]=voice3[i];
        
      }
      for(int i = 10*AUDIO_BLOCK_SAMPLES; i<11*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice1[i] = bp[i];
      }
      for(int i = 20*AUDIO_BLOCK_SAMPLES; i<21*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice2[i] = bp[i];
      }
      for(int i = 30*AUDIO_BLOCK_SAMPLES; i<31*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice3[i] = bp[i];
      }
      for(int i = 40*AUDIO_BLOCK_SAMPLES; i<41*AUDIO_BLOCK_SAMPLES; i++)
      {
        voice4[i] = bp[i];
      }
      for(int i = 0; i<AUDIO_BLOCK_SAMPLES; i++)
      {
        bp[i] = (bp[i]/4 +cpy1[i]/4+cpy2[i]/4+cpy3[i]/4); 
      }
      transmit(block,0);
      release(block);
    }
    
    Serial.println("endloop");
  }
  
}