#include "userrevfx.h"
#include "delayline.hpp"

#define BUFFER_SIZE 48000

static dsp::DualDelayLine buffer;
static int32_t delay_time;
static float delay_feedback;

static __sdram f32pair_t buffer_ram[BUFFER_SIZE];

void REVFX_INIT(uint32_t platform, uint32_t api) {
  buffer.setMemory(buffer_ram, BUFFER_SIZE);
  delay_time = BUFFER_SIZE / 2;
  delay_feedback = 0.0f;
}

void REVFX_PROCESS(float *xn, uint32_t frames) {
  float * __restrict x = xn;
  const float * x_e = x + 2*frames;

  for (; x != x_e ; x+=2) {
    f32pair_t lr = buffer.read(delay_time);
    *x = fx_softclipf(0.05f, (*x) + lr.a * delay_feedback);
    *(x+1) = fx_softclipf(0.05f, (*(x+1)) + lr.b * delay_feedback);
    buffer.write((f32pair_t){*x, *(x+1)});
  }
}


void REVFX_PARAM(uint8_t index, int32_t value) {
  const float valf = q31_to_f32(value);
  switch (index) {
    case k_user_revfx_param_time:
      delay_time = clipminmaxf(0.05f, valf, 1.0f) * BUFFER_SIZE;
      break;
    case k_user_revfx_param_depth:
      delay_feedback = clipminmaxf(0.05f, valf, 1.0f);
      break;
    case k_user_revfx_param_shift_depth:
      break;
    default:
      break;
  }
}

