#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include <Arduino.h>
#include "AudioEffectChorus2.h"


//update is called every 128 samples/2.9 ms
//attempting to write 29 ms delay chorus
void AudioEffectChorus2::changeNum(int numVoices)
{
  num_voices = numVoices;
}
void AudioEffectChorus2::update(void) {
  audio_block_t *block;
  block = receiveWritable(0);
  audio_block_t *temp[40];
  temp[0] = block;
  short *bp = block->data;
  for(int i = 0; i < pastSize-1; i++)
    {
      temp[i+1] = pastSamples[i];
      
      
    }
  if(num_voices == 0)
  {
    transmit(block,0);
    release(block);
  }
  if(num_voices == 1)
  {
    for(int i  = 0; i < 128; i++)
    {
      short *individual1 = temp[9]->data;
      bp[i] += individual1[i];
      transmit(block,0);
      release(block);
    }
  }
  if(num_voices == 2)
  {
    for(int i  = 0; i < 128; i++)
    {
      short *individual1 = temp[9]->data;
      short *individual2 = temp[19]->data;
      bp[i] += individual1[i];
      bp[i] += individual2[i];
      transmit(block,0);
      release(block);
    }
  }
  if(num_voices == 3)
  {
    for(int i  = 0; i < 128; i++)
    {
      short *individual1 = temp[9]->data;
      short *individual2 = temp[19]->data;
      short *individual3 = temp[29]->data;
      bp[i] += individual1[i];
      bp[i] += individual2[i];
      bp[i] += individual3[i];
      transmit(block,0);
      release(block);
    }
  }
  if(num_voices == 4)
  {
    for(int i  = 0; i < 128; i++)
    {
      short *individual1 = temp[9]->data;
      short *individual2 = temp[19]->data;
      short *individual3 = temp[29]->data;
      short *individual4 = temp[39]->data;
      bp[i] += individual1[i];
      bp[i] += individual2[i];
      bp[i] += individual3[i];
      bp[i] += individual4[i];
      transmit(block,0);
      release(block);
    }
  }
  for(int i = 0; i < pastSize; i++)
  {
    pastSamples[i] = temp[i];
  }
}