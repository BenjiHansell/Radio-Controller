/* This class wraps an instance of Battery, and behaves like the contained
 * except that it's value is 1/S where S is a number of cells, so if an S = 3
 * Battery has a voltage of 12.3 V, then the associated BatteryCell will report
 * a voltage of 4.1 V
 */

#pragma once

#include "DataSource/Battery.hpp"
#include "stdint.h"

class BatteryCell : public Battery{
public:
  BatteryCell(const char _name[5], Battery&, uint8_t);
  virtual uint8_t get_value() const;
  virtual uint32_t get_colour();
private:
  const Battery& battery;
  uint8_t number_of_cells;
};
