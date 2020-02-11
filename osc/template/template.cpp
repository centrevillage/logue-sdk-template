#include "userosc.h"

typedef struct State {
  float w0; // current delta phase for update
  float phase; // current phase
  float lfo;  // current lfo value
  float lfoz;
  float shape;
  float shiftshape;
} State;

static State state;

void OSC_INIT(uint32_t platform, uint32_t api) {
  state.w0 = 0.f;
  state.phase = 0.f;
  state.lfo = 0.f;
  state.lfoz = 0.f;
  state.shape = 0.f;
  state.shiftshape = 0.f;
}

// phase: current oscilaltor phase
// lfoz: current shape value
__fast_inline float oscillator_process(float phase, float shape) {
  // TODO: your fantastic oscillator
  return 0.f;
}

// params: oscillator parameter
// yn: write address
// frames: requested frame count for write
void OSC_CYCLE(const user_osc_param_t * const params, int32_t *yn, const uint32_t frames) {
  // convert pitch(1 octave = 12 * 256 pitch value) to delta phase
  const float w0 = state.w0 = osc_w0f_for_note((params->pitch)>>8, params->pitch & 0xFF);
  q31_t * __restrict y = (q31_t *)yn;
  const q31_t * y_e = y + frames;
  state.lfo = q31_to_f32(params->shape_lfo);
  float lfoz = state.lfoz;
  const float lfo_inc = (state.lfo - lfoz) / frames;
  float phase = state.phase;
  for (; y != y_e; ) {
    // calculate current signal value
    const float sig = osc_softclipf(0.05f, oscillator_process(phase, state.shape + lfoz));
    // convert Floating-Point[-1, 1] to Fixed-Point[-0x7FFFFFFF, 0x7FFFFFFF] and update signal
    *(y++) = f32_to_q31(sig);
    // inclement wave phase
    phase += w0;
    // reset wave phase if it overlap
    phase -= (uint32_t)phase;
    lfoz += lfo_inc;
  }
  state.phase = phase;
  state.lfoz = lfoz;
}

void OSC_NOTEON(const user_osc_param_t * const params) {
  // TODO:
  (void)params;
}

void OSC_NOTEOFF(const user_osc_param_t * const params) {
  // TODO:
  (void)params;
}

void OSC_PARAM(uint16_t index, uint16_t value) {
  const float valf = param_val_to_f32(value);
  
  switch (index) {
  case k_user_osc_param_id1:
    break;
  case k_user_osc_param_id2:
    break;
  case k_user_osc_param_id3:
    break;
  case k_user_osc_param_id4:
    break;
  case k_user_osc_param_id5:
    break;
  case k_user_osc_param_id6:
    break;
  case k_user_osc_param_shape:
    state.shape = valf;
    break;
  case k_user_osc_param_shiftshape:
    state.shiftshape = valf;
    break;
  default:
    break;
  }
}

