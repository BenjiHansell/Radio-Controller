#include "frequency_counter.hpp"
#include "num_to_str.hpp"

void frequency_counter::log(int amount){
  total_amount += amount;
}

unsigned int frequency_counter::get_frequency(){
  auto time_now = millis();
  if(time_of_previous_frequency_calculation+minimum_period < time_now){
    auto actual_period = time_now - time_of_previous_frequency_calculation;
    latest_frequency = (total_amount * 1000)/actual_period;
    time_of_previous_frequency_calculation = time_now; // resets timer
    total_amount = 0; // resets counter
  }
  return latest_frequency;
}

unsigned int frequency_counter::get_period(){
  return 1000 / get_frequency();
}

const char* frequency_counter::get_name(char* const output){
  return name;
}

const char* frequency_counter::get_data(char* const output){
  unsigned int val = get_frequency();
  volatile bool too_big = val > 999;
  // not sure why this needs to be volatile but it breaks otherwise
  if(too_big){
    output[0] = '-';
    output[1] = '-';
    output[2] = '-';
  }else{
    output[0] = unit_to_char(val/100);
    output[1] = unit_to_char((val%100)/10);
    output[2] = unit_to_char(val%10);
  }
  output[3] = '\0';
  return output;
}
