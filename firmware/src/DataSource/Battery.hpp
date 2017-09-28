#pragma once

#include <string.h>

#include "DataSource.hpp"
#include "led_data_source.hpp"
#include "num_to_str.hpp"

class Battery : public DataSource, public led_data_source {
public:
  Battery(const char _name[5]);
  virtual uint8_t get_value() const { return 0; } // returns battery voltage in increments of 0.1V
  virtual size_t get_recomended_length(){ return 4; }
  virtual const char* get_name(char* const output){return name;}
  virtual const char* get_data(char* const output);
private:
  const char* const name;
};
