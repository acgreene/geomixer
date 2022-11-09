#ifndef effect_phaser_h_
#define effect_phaser_h_
#include "AudioStream.h"
#include "Arduino.h"

class AudioEffectPhaser : public AudioStream
{
public:
        #define AUDIO_BLOCK_SIZE 180
        static const int MAX_DELAY = 1323 + AUDIO_BLOCK_SIZE;
        //standard delay times seem to be 5ms to 30 ms, use 30 as max, 5 as default
        //converting to samples, with a 44.1 kHz sampling rate (actual rate tbd)
        //Max = 1323 samples
        //Default = 220.5 samples round to 220
        AudioEffectPhaser() : AudioStream(1, inputQueueArray)
        {
            //do constructor stuff
            on = false;
            delayAmount = 220;
            memset(queue, 0, sizeof(queue));

        }
        //to start the effect
        //Maybe can delete, the delay line was needed for Chorus function,
        //don't really see how it helps with Phaser
        boolean begin(short *delayline,int delay_length)
        //called via interrupt
        virtual void update(void);
        //easiest implementation would be in samples, may be beneficial to do it in miliseconds instead though
        void changeDelay(uint32_t delay);

        //will be useful for when effect not in triangle, not sure about implementation right now
        void turnOff();

private:
        bool on;
        audio_block_t *inputQueueArray[1];
        uint32_t delayAmount;
        short *queue[MAX_DELAY];
        //helper function to move the AUDIO_BLOCK_SIZE:delayAmount+AUDIO_BLOCK_SIZE samples over by AUDIO_BLOCK_SIZE
        void shiftLeft();
        //inserts block at back of queue
        //back of queue not necessarily the end of the array, based on the chosen delayAmount
        void insertBlock(short* bp);

};