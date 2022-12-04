#ifndef effect_phaser_h_
#define effect_phaser_h_
#include "Arduino.h"
#include "AudioStream.h"
#include "circular_buffer.h"

class AudioEffectPhaser : public AudioStream
{
public:
        #define OSCILLATION_AMP 128
        static const int MAX_DELAY = 3000 + 128 + OSCILLATION_AMP;
        //standard delay times seem to be 5ms to 30 ms, use 30 as max, 5 as default
        //converting to samples, with a 44.1 kHz sampling rate (actual rate tbd)
        //Max = 1323 samples
        //Default = 220.5 samples round to 220
        AudioEffectPhaser() : AudioStream(1, inputQueueArray), queue(3000 + 128 + 128)
        {
            on = false;
            delayAmount = 220;
            sine_idx = 0;
            oscil_delay = 0;
            //circular_buffer queue(1323 + 128 + 40);
            //circular_buffer queue(static_cast<int>(MAX_DELAY));
            //Serial.println("prememset");
            //memset(queue, 0, sizeof(queue));
            //Serial.println("memset");

        }
        //to start the effect
        //Maybe can delete, the delay line was needed for Chorus function,
        //don't really see how it helps with Phaser
        void begin(short delay_length);
        //called via interrupt
        virtual void update(void);
        //easiest implementation would be in samples, may be beneficial to do it in miliseconds instead though
        void changeDelay(short delay_length);

        //will be useful for when effect not in triangle
        //void turnOff();

        bool getOn();

        void setOn(bool status);

private:
        bool on;
        audio_block_t *inputQueueArray[1];
        int delayAmount;
        circular_buffer queue;
        unsigned int sine_idx;
        short oscil_delay;
        //helper function to move the AUDIO_BLOCK_SIZE:delayAmount+AUDIO_BLOCK_SIZE samples over by AUDIO_BLOCK_SIZE
        //void shiftLeft();
        //inserts block at back of queue
        //back of queue not necessarily the end of the array, based on the chosen delayAmount
        //void insertBlock(short* bp);

};
#endif