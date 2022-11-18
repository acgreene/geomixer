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
        AudioEffectMyReverb(void) : AudioStream(1, inputQueueArray) {
          on = false;
          init();
          clear_buffers();
        }
        void begin(void);
        virtual void update(void);
        void turnOff(void);
        void turnOn(void);
private:
        struct apf {
          int16_t gain;
          int16_t *in_queue;
          int16_t *out_queue;
          uint16_t delay;
        };

        struct comb {
          int16_t gain;
          int16_t *queue;
          uint16_t delay;
        };

        void init(void);
        void clear_buffers(void);
        static void _run_apf(struct apf *apf, int16_t *in_buf, int16_t *out_buf);
        static void _run_comb(struct comb *comb, int16_t *in_buf, int16_t *out_buf);
        void shiftLeft(int16_t *queue, uint16_t delayAmount);
        void insertBlock(int16_t* queue, int16_t* block, uint16_t delayAmount);

        bool on;
        audio_block_t *inputQueueArray[1];
        struct apf apfs[3];
        struct comb combs[4];

        int16_t apf1_inqueue[APF_D1 + AUDIO_BLOCK_SAMPLES];
        int16_t apf1_outqueue[APF_D1 + AUDIO_BLOCK_SAMPLES];
        int16_t apf2_inqueue[APF_D2 + AUDIO_BLOCK_SAMPLES];
        int16_t apf2_outqueue[APF_D2 + AUDIO_BLOCK_SAMPLES];
        int16_t apf3_inqueue[APF_D3 + AUDIO_BLOCK_SAMPLES];
        int16_t apf3_outqueue[APF_D3 + AUDIO_BLOCK_SAMPLES];

        int16_t comb1_queue[COMB_D1 + AUDIO_BLOCK_SAMPLES];
        int16_t comb2_queue[COMB_D2 + AUDIO_BLOCK_SAMPLES];
        int16_t comb3_queue[COMB_D3 + AUDIO_BLOCK_SAMPLES];
        int16_t comb4_queue[COMB_D4 + AUDIO_BLOCK_SAMPLES];

        int16_t sum_buf[AUDIO_BLOCK_SAMPLES];
        int16_t aux_buf[AUDIO_BLOCK_SAMPLES];
};
#endif
