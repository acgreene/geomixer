#include "effect_phaser.h"
#include <arduino.h>

void AudioEffectPhaser::update(void)
{
    //read first AUDIO_BLOCK_SIZE samples from array
    //call function to shift all the other members of the array over by AUDIO_BLOCK_SIZE
    //insert incoming new sample block to back of array
    //add the samples from front of array to the new sample block
    //transmit
    audio_block_t *block;
    short *bp;
    int sum;
    if(!on) {
    // Just passthrough and add samples to queue
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
    short cpy[AUDIO_BLOCK_SIZE];
    block = receiveWritable(0);
        if(block) {
            bp = block->data;

            for(size_t i = 0; i < AUDIO_BLOCK_SIZE; ++i)
            {
                cpy[i] = queue[i]
            }
            shiftLeft();
            insertBlock(bp);
            for(size_t i = 0; i < AUDIO_BLOCK_SIZE; ++i)
            {
                *bp += cpy[i];
            }
            transmit(block,0);
            release(block);
        }
}

    AudioEffectPhaser::shiftLeft()
    {
        for(size_t i = AUDIO_BLOCK_SIZE; i < delayAmount+AUDIO_BLOCK_SIZE; ++i)
        {
            queue[i-AUDIO_BLOCK_SIZE] = queue[i];
        }
    }

    AudioEffectPhaser::insertBlock(short* bp)
    {
        short* cpy = bp;
        for(size_t i = delayAmount; i < delayAmount + AUDIO_BLOCK_SIZE; ++i)
        {
            queue[i] = *cpy++;
        }
    }