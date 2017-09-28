#include "BatteryLocal.hpp"

#include <Arduino.h>

BatteryLocal::BatteryLocal(const char _name[5], const uint8_t _pin, const unsigned int _multiplier)
: Battery(_name),
  pin(_pin),
  multiplier(_multiplier)
{}

void BatteryLocal::begin(){
  pinMode(pin, INPUT);
}

uint8_t BatteryLocal::get_value() const {
  const auto raw = analogRead(pin);
  uint32_t intermediate = (uint32_t)raw * (uint32_t)multiplier;
  return intermediate / 1000;
}

uint32_t BatteryLocal::get_colour(){
  const auto value = get_value();
  if (value == 0) return black; // LED will be unlit if no telemetry has yet been received
  if (value < 50) return flashing(red);
  if (value < 55) return red;
  if (value < 75) return orange;
  return green;
}
