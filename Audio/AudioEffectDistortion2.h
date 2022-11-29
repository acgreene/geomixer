#ifndef effect_distortion2_h_
#define effect_distortion2_h_
#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectDistortion2 : public AudioStream
{
public:
        AudioEffectDistortion2() : AudioStream(1, inputQueueArray)
        {
        
                
        }
        virtual void update(void);
private:
        int max = 32767;
       
        audio_block_t *inputQueueArray[1];
        
};
#endif
