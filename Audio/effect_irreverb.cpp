#include <Arduino.h>
#include "effect_irreverb.h"
#include "arm_math.h"
#include "dspinst.h"

void AudioEffectIrReverb::update(void)
{
    //read first AUDIO_BLOCK_SIZE samples from array
    //call function to shift all the other members of the array over by AUDIO_BLOCK_SIZE
    //insert incoming new sample block to back of array
    //add the samples from front of array to the new sample block
    //transmit
    //Serial.println("update");
    audio_block_t *block;
    short *bp;
    int i,j,sum;
    if(!on) {
    // Just passthrough and add samples to queue
        //Serial.println("off");
        block = receiveWritable(0);
        if(block) {
            bp = block->data;
            //shiftLeft();
            queue.insertBlock(bp);
            transmit(block,0);
            //Serial.println("transmit");
            release(block);
            //Serial.println("release");
        }
    }
    //Need to store the data
    else if(on)
    {
        block = receiveWritable(0);
        if(block) {
            b_new = allocate();
            bp = block->data;
            queue.insertBlock(bp);
            // arm_fir_fast_q15(&filter.fir_inst, (q15_t *)block->data,
            //     (q15_t *)b_new->data, AUDIO_BLOCK_SAMPLES);
            for(i = 0; i < 128; i++){
              sum = 0;
              for(j = 0; j < 9000; j++){
                sum += multiply_16bx16b(queue.getValue(j+i),Reverb_IR[j]);
              }
              out[i] = sum;
            }
            arm_q31_to_q15(out,(q15_t *)b_new->data,AUDIO_BLOCK_SAMPLES);
            transmit(b_new,0);
            release(b_new);
            release(block);
        }
    }
}

void AudioEffectIrReverb::begin()
{
    //Serial.println("begin");
    this->on = true;
    //Serial.println("Done begin");
}
void AudioEffectIrReverb::turnOff()
{
    //Serial.println("Sanity check");
    this->on = false;
}
