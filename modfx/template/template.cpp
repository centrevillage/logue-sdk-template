#include "usermodfx.h"
#include "biquad.hpp"

static dsp::BiQuad filter_l, filter_r;
static float cutoff;

void MODFX_INIT(uint32_t platform, uint32_t api) {
  cutoff = 1.0f;
  filter_l.flush();
  filter_l.mCoeffs.setPoleLP(1.f - (cutoff*2.f));
  filter_r.flush();
  filter_r.mCoeffs = filter_l.mCoeffs;
}


void MODFX_PROCESS(const float *main_xn, float *main_yn,
                   const float *sub_xn,  float *sub_yn,
                   uint32_t frames) {
  const float * mx = main_xn;
  float * __restrict my = main_yn;
  const float * my_e = my + 2*frames;

  const float *sx = sub_xn;
  float * __restrict sy = sub_yn;
  
  for (; my != my_e; ) {
    *(my++) = filter_l.process_so(*(mx++));
    *(my++) = filter_r.process_so(*(mx++));
    *(sy++) = filter_l.process_so(*(sx++));
    *(sy++) = filter_r.process_so(*(sx++));
  }
}


void MODFX_PARAM(uint8_t index, int32_t value) {
  const float valf = q31_to_f32(value);
  switch (index) {
  case k_user_modfx_param_time:
    cutoff = valf;
    filter_l.mCoeffs.setPoleLP(1.f - (cutoff*2.f));
    filter_r.mCoeffs = filter_l.mCoeffs;
    break;
  case k_user_modfx_param_depth:
    break;
  default:
    break;
  }
}

