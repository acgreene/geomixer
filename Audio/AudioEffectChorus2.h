#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>
#include "Arduino.h"
#include "AudioStream.h"


class AudioEffectChorus2 : public AudioStream
{
public:
        AudioEffectChorus2() : AudioStream(1, inputQueueArray){}
        virtual void update(void);
        void changeNum(int numVoices);
private:
        audio_block_t *inputQueueArray[1];
        int num_voices = 0;
        //short *l_delayline;
        //int delayLength = 40;
        int numCalls = 0;
        audio_block_t *pastSamples[40];
        int pastSize = 40;
};

