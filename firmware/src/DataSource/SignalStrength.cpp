#include "SignalStrength.hpp"
#include "num_to_str.hpp"

SignalStrength::SignalStrength(frequency_counter& _sent, frequency_counter& _received):
  sent(_sent), received(_received)
{

}

uint8_t SignalStrength::get(){
  auto temp = received.get_frequency();
  if(temp == 0) return 0;
  else return temp*100/sent.get_frequency();
}

const char* SignalStrength::get_name(char* const output){
  output[0] = 'S';
  output[1] = 'i';
  output[2] = '\0';
  return output;
}

const char* SignalStrength::get_data(char* const output){
  auto val = get();
  if (val > 99) val = 99;
  output[0] = val > 9 ? unit_to_char(val/10) : ' ';
  output[1] = unit_to_char(val%10);
  output[2] = '\0';
  return output;
}

uint32_t SignalStrength::get_colour(){
  auto val = get();
  return val ? val > 90 ? green : orange : red;
}
