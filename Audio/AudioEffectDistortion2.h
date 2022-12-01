#ifndef effect_distortion2_h_
#define effect_distortion2_h_
#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectDistortion2 : public AudioStream
{
public:
        AudioEffectDistortion2() : AudioStream(1, inputQueueArray)
        {
        output_scalar = 3277;
                
        }
        virtual void update(void);
private:
        int32_t output_scalar;
       
        audio_block_t *inputQueueArray[1];
        
};
#endif
