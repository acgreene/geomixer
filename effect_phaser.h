#ifndef effect_phaser_h_
#define effect_phaser_h_
#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectPhaser : public AudioStream
{
public:
        #define AUDIO_BLOCK_SIZE 180
        static const int MAX_DELAY = 1323 + AUDIO_BLOCK_SAMPLES;
        //standard delay times seem to be 5ms to 30 ms, use 30 as max, 5 as default
        //converting to samples, with a 44.1 kHz sampling rate (actual rate tbd)
        //Max = 1323 samples
        //Default = 220.5 samples round to 220
        AudioEffectPhaser() : AudioStream(1, inputQueueArray)
        {
            on = false;
            delayAmount = 220;
            //Serial.println("prememset");
            memset(queue, 0, sizeof(queue));
            //Serial.println("memset");

        }
        //to start the effect
        //Maybe can delete, the delay line was needed for Chorus function,
        //don't really see how it helps with Phaser
        void begin(int delay_length);
        //called via interrupt
        virtual void update(void);
        //easiest implementation would be in samples, may be beneficial to do it in miliseconds instead though
        void changeDelay(int delay);

        //will be useful for when effect not in triangle
        void turnOff();

private:
        bool on;
        audio_block_t *inputQueueArray[1];
        int delayAmount;
        short queue[MAX_DELAY];
        //helper function to move the AUDIO_BLOCK_SIZE:delayAmount+AUDIO_BLOCK_SIZE samples over by AUDIO_BLOCK_SIZE
        void shiftLeft();
        //inserts block at back of queue
        //back of queue not necessarily the end of the array, based on the chosen delayAmount
        void insertBlock(short* bp);

};
#endif