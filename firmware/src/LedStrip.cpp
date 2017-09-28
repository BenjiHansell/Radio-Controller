#include "LedStrip.hpp"
#include "led_data_source.hpp"

// could possibly be done with a parameter pack
LedStrip::LedStrip(uint8_t pin, led_data_source* d0, led_data_source* d1, led_data_source* d2, led_data_source* d3):
  strip(8, pin, NEO_GRB + NEO_KHZ800)
{
  data_sources[0] = d3;
  data_sources[1] = nullptr; // nullptr means LED is off
  data_sources[2] = d2;
  data_sources[3] = nullptr;
  data_sources[4] = d1;
  data_sources[5] = nullptr;
  data_sources[6] = d0;
  data_sources[7] = nullptr;
  // four off the LEDs are not physically visible, so are off automatically
}

void LedStrip::update(){
  for(int i = 0; i < 8; i++)
    if (data_sources[i])
      strip.setPixelColor(i, data_sources[i]->get_colour());
  strip.show();
}

void LedStrip::begin(){
  strip.begin();
}
