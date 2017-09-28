#pragma once

#include "led_data_source.hpp"
#include <Adafruit_NeoPixel.h>

class LedStrip{
public:
  LedStrip(uint8_t pin, led_data_source* = nullptr, led_data_source* = nullptr, led_data_source* = nullptr, led_data_source* = nullptr);
  void begin();
  void update();
private:
  Adafruit_NeoPixel strip;
  led_data_source* data_sources[8] = {nullptr}; // 8 data sources for 8 LEDs
  uint32_t strip_colours[8];
};
