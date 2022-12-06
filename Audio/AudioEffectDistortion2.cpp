#include <Arduino.h>
#include "AudioEffectDistortion2.h"

//}

void AudioEffectDistortion2::change_output_scalar(int32_t scalar_factor)
{
  
  output_scalar = (output_scalar/scalar_factor);
}

void AudioEffectDistortion2::update(void)
{
  audio_block_t *block;
  block = receiveWritable(0);
  short *bp = block->data;

  if (!on)
  {
    if (block)
    {
      transmit(block, 0);
      release(block);
    }
  }
  else
  {
    if (block)
    {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++)
      {
        if (*bp != 0)
        {
          if (abs(*bp * input_scalar) > ((output_scalar / 3)) && abs(*bp * input_scalar) < ((2 * (output_scalar / 3))))
          {
            // Serial.println(*bp);
            *bp = (*bp / abs(*bp)) * (output_scalar) * ((3 - pow((2 - (*bp / abs(*bp)) * (3.0 * (float)(*bp * input_scalar) / (float)(output_scalar))), 2)) / 6);
          }
          // This if statement above creates the curvature for the clipping when the signal is between 1/3 and 2/3 of the max

          else if (abs(*bp * input_scalar) > (2 * (output_scalar / 3)))
          {
            // Serial.println((2*(output_scalar/3)));
            *bp = (*bp / abs(*bp)) * (output_scalar / 2);
          }

          else
          {
            *bp = *bp * input_scalar;
          }
          // This if statement above flattens the signal when it is beyond 2/3 of the max and leaves it intact if it is less than 1/3
        }
        bp++;
      }
      transmit(block, 0);
      release(block);
    }
  }
}

void AudioEffectDistortion2::begin()
{
  this->on = true;
}

void AudioEffectDistortion2::setOn(bool status)
{
  on = status;
}

bool AudioEffectDistortion2::getOn()
{
  return on;
}
