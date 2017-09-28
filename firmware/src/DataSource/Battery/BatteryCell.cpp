#include "BatteryCell.hpp"

BatteryCell::BatteryCell(const char _name[5], Battery& _battery, uint8_t _number_of_cells):
  Battery(_name),    // parent object
  battery(_battery), // member object reference
  number_of_cells(_number_of_cells)
{
}

uint8_t BatteryCell::get_value() const {
  return battery.get_value() / number_of_cells;
}

uint32_t BatteryCell::get_colour(){
  const auto value = get_value();
  if (value == 0) return black; // LED will be unlit if no telemetry has yet been received
  if (value < 30) return flashing(red);
  if (value < 33) return red;
  if (value < 38) return orange;
  return green;
}
