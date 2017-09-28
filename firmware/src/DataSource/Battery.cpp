#include "DataSource/Battery.hpp"

Battery::Battery(const char _name[5])
 :name(_name)
{
}

const char* Battery::get_data(char* const output){
  auto val = get_value();
  output[0] = val >= 100 ? unit_to_char(val/100) : ' ';
  output[1] = unit_to_char((val%100) / 10);
  output[2] = '.';
  output[3] = unit_to_char(val%10);
  output[4] = '\0';
  return output;
}
