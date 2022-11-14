#ifndef effect_myreverb_
#define effect_myreverb_
#include "AudioStream.h"

#define APF_G 0.7
#define APF_D1 441
#define APF_D2 341
#define APF_D3 225
#define COMB_G1 0.742
#define COMB_G2 0.733
#define COMB_G3 0.715
#define COMB_G4 0.697
#define COMB_D1 1116
#define COMB_D2 1356
#define COMB_D3 1422
#define COMB_D4 1617

class AudioEffectMyReverb : public AudioStream
{
public:
        AudioEffectMyReverb() : AudioStream(1, inputQueueArray) {
          begin();
        }
        virtual void update(void);
        void begin(void);
        void turnOff(void);
private:
        struct apf {
          int32_t gain;
          short *in_queue;
          short *out_queue;
          uint32_t delay;
        };

        struct comb {
          int32_t gain;
          short *queue;
          uint32_t delay;
        }

        void run_apf(struct apf *apf, short *in_buf, short *out_buf);
        void run_comb(struct lpf *lpf, short *in_buf, short *out_buf);
        void shiftLeft(short *queue, uint32_t delayAmount);
        void insertBlock(short* queue, short* block, uint32_t delayAmount);

        bool on;
        audio_block_t *inputQueueArray[1];
        struct apf apfs[3];
        struct comb combs[4];

        short apf1_inqueue[APF_D1 + AUDIO_BLOCK_SAMPLES];
        short apf1_outqueue[APF_D1 + AUDIO_BLOCK_SAMPLES];
        short apf2_inqueue[APF_D2 + AUDIO_BLOCK_SAMPLES];
        short apf2_outqueue[APF_D2 + AUDIO_BLOCK_SAMPLES];
        short apf3_inqueue[APF_D3 + AUDIO_BLOCK_SAMPLES];
        short apf3_outqueue[APF_D3 + AUDIO_BLOCK_SAMPLES];

        short comb1_queue[COMB_D1 + AUDIO_BLOCK_SAMPLES];
        short comb2_queue[COMB_D2 + AUDIO_BLOCK_SAMPLES];
        short comb3_queue[COMB_D3 + AUDIO_BLOCK_SAMPLES];
        short comb4_queue[COMB_D4 + AUDIO_BLOCK_SAMPLES];

        short sum_buf[AUDIO_BLOCK_SAMPLES];
        short aux_buf[AUDIO_BLOCK_SAMPLES];
};
