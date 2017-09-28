#pragma once

#include "DataSource.hpp"
#include "led_data_source.hpp"
#include "frequency_counter.hpp"
#include <stdint.h>

class SignalStrength : public DataSource, public led_data_source{
public:
  SignalStrength(frequency_counter&, frequency_counter&);
  uint8_t get(); // 0 to 100
  virtual const char* get_name(char* const output);
  virtual const char* get_data(char* const output);
  virtual uint32_t get_colour();
private:
  frequency_counter& sent;
  frequency_counter& received;
};
