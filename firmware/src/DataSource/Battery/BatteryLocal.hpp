#pragma once

#include "DataSource/Battery.hpp"
#include <stdint.h>

class BatteryLocal : public Battery {
public:
  BatteryLocal(const char _name[5], const uint8_t _pin, const unsigned int _multiplier);
  void begin();
  virtual uint8_t get_value() const; // returns battery voltage in increments of 0.1V
  virtual uint32_t get_colour(); // for LED
private:
  const uint8_t pin;
  const unsigned int multiplier;
};
