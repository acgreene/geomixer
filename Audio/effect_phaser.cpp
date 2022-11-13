#include <Arduino.h>
#include "effect_phaser.h"

void AudioEffectPhaser::update(void)
{
    //read first AUDIO_BLOCK_SIZE samples from array
    //call function to shift all the other members of the array over by AUDIO_BLOCK_SIZE
    //insert incoming new sample block to back of array
    //add the samples from front of array to the new sample block
    //transmit
    audio_block_t *block;
    short *bp;
    ////Serial.println("update");
    if(!on) {
    // Just passthrough and add samples to queue
        //Serial.println("test");
        block = receiveWritable(0);
        if(block) {
            bp = block->data;
            shiftLeft();
            insertBlock(bp);
            transmit(block,0);
            release(block);
        }
    }
    //Need to store the data
    else{
        short cpy[AUDIO_BLOCK_SAMPLES];
        block = receiveWritable(0);
            if(block) {
                bp = block->data;

                for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
                {
                    cpy[i] = queue[i];
                }
                shiftLeft();
                insertBlock(bp);
                for(int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
                {
                    *bp = (*bp + cpy[i]);
                    bp++;
                }
                transmit(block,0);
                release(block);
            }
    }
}

void AudioEffectPhaser::shiftLeft()
{
    ////Serial.println("Shift Left");
    for(int i = AUDIO_BLOCK_SAMPLES; i < delayAmount+AUDIO_BLOCK_SAMPLES; ++i)
    {
        queue[i-AUDIO_BLOCK_SAMPLES] = queue[i];
    }
}

void AudioEffectPhaser::insertBlock(short* bp)
{
    ////Serial.println("Insert Block");
    short* cpy = bp;
    for(int i = delayAmount; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
    {
        queue[i] = *cpy++;
    }
    ////Serial.println("end insert block");
}

void AudioEffectPhaser::begin(int delay_length)
{
    ////Serial.print("AudioBlockSamples:");
    ////Serial.println(AUDIO_BLOCK_SAMPLES);
    ////Serial.println("begin");
    on = true;
    int diff = delay_length - delayAmount;
    ////Serial.println(diff);
    if(delay_length <= MAX_DELAY - AUDIO_BLOCK_SAMPLES)
    {
        delayAmount = delay_length;
        if(diff < 0)
        {
            ////Serial.println("Negative case");
            for(int i = diff * -1; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
            {
                queue[i + diff] = queue[i];
            }
        }
        if(diff > 0)
        {
            ////Serial.println("Positive Case");
            for(int i = 0; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
            {
                queue[i + diff] = queue[i];
            }
            for(int i = 0; i < diff; ++i)
            {
                queue[i] = 0;
            }
            
        }
    }
    ////Serial.println("Done begin");
}
void AudioEffectPhaser::turnOff()
{
    on = false;
}

void AudioEffectPhaser::changeDelay(int delay)
{
    int diff = delay - delayAmount;
    ////Serial.println(diff);
    if(delay <= MAX_DELAY - AUDIO_BLOCK_SAMPLES)
    {
        delayAmount = delay;
        if(diff < 0)
        {
            ////Serial.println("negative");
            for(int i = diff * -1; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
            {
                queue[i + diff] = queue[i];
            }
        }
        if(diff > 0)
        {
            ////Serial.println("positive");
            for(int i = 0; i < delayAmount + AUDIO_BLOCK_SAMPLES; ++i)
            {
                queue[i + diff] = queue[i];
            }
            for(int i = 0; i < diff; ++i)
            {
                queue[i] = 0;
            }
            
        }
    }
    ////Serial.println("done changeDelay");
}