#ifndef effect_chorus2_h_
#define effect_chorus2_h_
#include "Arduino.h"
#include "AudioStream.h"


class AudioEffectChorus2 : public AudioStream
{
public:
        AudioEffectChorus2() : AudioStream(1, inputQueueArray)
        {
                num_voices = 0;
                pastSize = 11+AUDIO_BLOCK_SAMPLES;
                memset(voice1, 0, sizeof(voice1));
                memset(voice2, 0, sizeof(voice2));
                memset(voice3, 0, sizeof(voice3));
                memset(voice4, 0, sizeof(voice4));
        }
        virtual void update(void);
        void changeNum(int numVoices);
private:
        audio_block_t *inputQueueArray[1];
        int num_voices;
        //short *l_delayline;
        //int delayLength = 40;
        //int numCalls = 0;
        short voice1[11*AUDIO_BLOCK_SAMPLES];
        short voice2[21*AUDIO_BLOCK_SAMPLES];
        short voice3[31*AUDIO_BLOCK_SAMPLES];
        short voice4[41*AUDIO_BLOCK_SAMPLES];
        int pastSize;
};
#endif

