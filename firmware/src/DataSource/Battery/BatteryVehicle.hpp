#pragma once

#include <string.h>

#include "DataSource/Battery.hpp"

class BatteryVehicle : public Battery {
public:
  BatteryVehicle(const char _name[5]);
  virtual uint8_t get_value() const { return value; }
  virtual size_t get_recomended_length(){ return 4; }
  void setValue(uint8_t _value){ value = _value; }
private:
  uint8_t value;
};
