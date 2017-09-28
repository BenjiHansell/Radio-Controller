#pragma once

#include <stdint.h>
#include <Arduino.h>

uint32_t constexpr compose_colour(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

enum led_colour : uint32_t {
  red = compose_colour(100, 0, 0),
  green = compose_colour(0, 50, 0),
  yellow = compose_colour(50, 0, 50),
  orange = compose_colour(80, 20, 0),
  black = compose_colour(0, 0, 0),
  white = compose_colour(70, 70, 70)
};

inline led_colour flashing(led_colour c){
  return millis() % 1000 < 500 ? c : black;
}

class led_data_source{ // base class for all data sources which dictate an LED's colour
public:
  virtual uint32_t get_colour(){ return white; }
};
