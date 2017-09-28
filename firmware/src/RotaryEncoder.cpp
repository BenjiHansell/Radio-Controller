#include "RotaryEncoder.hpp"

rotary_encoder_snapshot::rotary_encoder_snapshot(bool _data, bool _clock, bool _sw):
  data(_data),
  clock(_clock),
  sw(_sw){}

  bool rotary_encoder_snapshot::operator!=(const rotary_encoder_snapshot& rhs){
    return data != rhs.data || clock != rhs.clock || sw != rhs.sw;
    // this could be done more efficiently by comparing the objecs' raw data
    // which might be necessary as this is used in an interupt
  }
