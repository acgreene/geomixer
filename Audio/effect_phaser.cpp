#include <Arduino.h>
#include "effect_phaser.h"
#include "arm_math.h"

void AudioEffectPhaser::update(void)
{
    // int start = micros();
    // read first AUDIO_BLOCK_SIZE samples from array
    // call function to shift all the other members of the array over by AUDIO_BLOCK_SIZE
    // insert incoming new sample block to back of array
    // add the samples from front of array to the new sample block
    // transmit
    // Serial.println("update");
    audio_block_t *block;
    short *bp;
    if (!on)
    {
        // Just passthrough and add samples to queue
        // Serial.println("off");
        block = receiveWritable(0);
        if (block)
        {
            bp = block->data;
            // shiftLeft();
            queue.insertBlock(bp);
            transmit(block, 0);
            // Serial.println("transmit");
            release(block);
            // Serial.println("release");
        }
    }
    // Need to store the data
    else if (on)
    {
        short sineOut = arm_sin_q15((q15_t)(sine_idx >> 16));
        // Serial.println(sineOut*10);
        int increment = (20 * 2147483648.0) / AUDIO_SAMPLE_RATE_EXACT;
        // Serial.println(increment);
        sine_idx += increment;
        // Serial.println("else");
        oscil_delay = (sineOut * OSCILLATION_AMP) >> 15;
        // Serial.println(oscil_delay);
        // Serial.println(delayAmount);
        short cpy[AUDIO_BLOCK_SAMPLES];
        // OSCILLATION_AMP = 40
        // oscil_delay should be on the order of -40 to 40
        // negative delay implies sample older samples, i.e. start 10-oscil_delay
        // positive delay implies take newer samples, i.e. start 10+oscil_delay
        int buffer = oscil_delay + OSCILLATION_AMP;
        // Serial.println(buffer);
        block = receiveWritable(0);
        if (block)
        {
            bp = block->data;
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
            {
                cpy[i] = queue.getValue((MAX_DELAY - delayAmount) + buffer++);
            }
            queue.insertBlock(bp);
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; ++i)
            {
                int sum = *bp + cpy[i];
                *bp = sum/2;
                bp++;
            }
            transmit(block, 0);
            release(block);
        }
        if (sine_idx & 0x80000000)
        {
            sine_idx &= 0x7fffffff;
        }
    }
    // int end = micros();
    // Serial.println(end - start);
}

/* void AudioEffectPhaser::shiftLeft()
{
    //Serial.println("Shift Left");
    for(int i = AUDIO_BLOCK_SAMPLES; i < delayAmount+AUDIO_BLOCK_SAMPLES+OSCILLATION_AMP; ++i)
    {
        queue[i-AUDIO_BLOCK_SAMPLES] = queue[i];
    }
}

void AudioEffectPhaser::insertBlock(short* bp)
{
    //Serial.println("Insert Block");
    short* cpy = bp;
    for(int i = delayAmount + OSCILLATION_AMP; i < delayAmount + AUDIO_BLOCK_SAMPLES + OSCILLATION_AMP; ++i)
    {
        queue[i] = *cpy++;
    }
    //Serial.println("end insert block");
} */

void AudioEffectPhaser::begin(short delay_length = 220)
{
    this->on = true;
    // int diff = delayAmount - delay_length;
    // queue.phaserChangeDelay(diff);
    if (delay_length > 1323)
        delay_length = 1323;
    delayAmount = delay_length;

    /*if(delay_length <= MAX_DELAY - AUDIO_BLOCK_SAMPLES)
    {
        if(diff < 0)
        {
            //Serial.println("Negative case");
            for(int i = (diff * -1); i < (delayAmount + 128 + OSCILLATION_AMP); ++i)
            {
                queue[i + diff] = queue[i];
            }
            this->delayAmount = delay_length;
        }
        if(diff > 0)
        {
            //Serial.println("Positive Case");
            for(int i = 0; i < delayAmount + 128 + OSCILLATION_AMP; ++i)
            {
                queue[i + diff] = queue[i];
            }
            for(int i = 0; i < diff; ++i)
            {
                queue[i] = 0;
            }
            this->delayAmount = delay_length;

        }
    } */
}
void AudioEffectPhaser::setOn(bool status)
{
    // Serial.println("Sanity check");
    on = status;
}

bool AudioEffectPhaser::getOn()
{
    return on;
}

void AudioEffectPhaser::changeDelay(short delay_length)
{
    if (delay_length > 1323)
        delay_length = 1323;
    delayAmount = delay_length;

    /*int diff = delay - delayAmount;
    //Serial.println(diff);
    if(delay <= MAX_DELAY - AUDIO_BLOCK_SAMPLES)
    {
        if(diff < 0)
        {
            //Serial.println("Negative case");
            for(int i = (diff * -1); i < (delayAmount + 128 + OSCILLATION_AMP); ++i)
            {
                queue[i + diff] = queue[i];
            }
            this->delayAmount = delay;
        }
        if(diff > 0)
        {
            //Serial.println("Positive Case");
            for(int i = 0; i < delayAmount + 128 + OSCILLATION_AMP; ++i)
            {
                queue[i + diff] = queue[i];
            }
            for(int i = 0; i < diff; ++i)
            {
                queue[i] = 0;
            }
            this->delayAmount = delay;

        }
    }*/
    // Serial.println("done changeDelay");
}
