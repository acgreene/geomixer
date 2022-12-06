#ifndef effect_distortion2_h_
#define effect_distortion2_h_
#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectDistortion2 : public AudioStream
{
public:
        AudioEffectDistortion2() : AudioStream(1, inputQueueArray)
        {
                max_ = 3277;
                input_scalar = 1;
        }
        virtual void update(void);
        void begin();
        bool getOn();
        void setOn(bool status);
        void change_output_scalar(float scalar_factor);

private:
        float output_scalar;
        float scalar_factor;
        int32_t max_;
        float input_scalar;
        bool on;

        audio_block_t *inputQueueArray[1];
};
#endif
