#include <Arduino.h>
#include <AudioStream.h>
#include "circular_buffer.h"

// max delay determined using the precedence effect which states that
// two sounds less than 40ms apart will still be percieved as one sound
// 40 ms at 44.1 khz -> 1764 samples
#define DELAY 1764

class AudioEffectStereo : public AudioStream
{
public:
        AudioEffectStereo() : AudioStream(1, inputQueueArray), buff((128 + DELAY)) { //change buff 2nd number for delay
          on = false;
          delay_val = 0;
        }
        void begin(void);
        virtual void update(void);
        void turnOff(void);
        void mix(float val);
private:
        bool on;
        audio_block_t *inputQueueArray[1];
        circular_buffer buff;
        int delay_val;
};
