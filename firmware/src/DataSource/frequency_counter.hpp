#pragma once

#include "DataSource.hpp"

#include <Arduino.h>

class frequency_counter : public DataSource{
public:
  frequency_counter(const char _name[3] = "Frq"){ // _name could be made const
    strcpy(name, _name);
  }
  void log(int amount = 1);
  unsigned int get_frequency(); // in Hz
  unsigned int get_period(); // in ms, only accurate for values << 1000 ms
  virtual const char* get_name(char* const output);
  virtual const char* get_data(char* const output);
private:
  char name[3+1];
  unsigned int total_amount; // number of calls to log() since time_of_previous_frequency_calculation
  int latest_frequency;  // frequency calculated in previous period / Hz
  unsigned long time_of_previous_frequency_calculation = 0;
  static constexpr int minimum_period = 1000; // number of milliseconds between calculations of frequency
};
