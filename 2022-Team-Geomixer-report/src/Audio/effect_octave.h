#include <Arduino.h>
#include <AudioStream.h>
#include "arm_math.h"
#include "arm_const_structs.h"

class AudioEffectOctave : public AudioStream
{
public:
        AudioEffectOctave() : AudioStream(1, inputQueueArray) {
          on = false;
        }
        void begin(void);
        virtual void update(void);
        void turnOff(void);
private:
        bool on;
        audio_block_t *inputQueueArray[1];
        short temp[AUDIO_BLOCK_SAMPLES/2+1];
        //short FFT_in_array[AUDIO_BLOCK_SAMPLES/2];
        //short FFT_out_array[AUDIO_BLOCK_SAMPLES];
};
