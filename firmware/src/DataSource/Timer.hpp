#ifndef TIMER_H
#define TIMER_H

#include "DataSource.hpp"
#include "num_to_str.hpp"
#include "DataSource/Stick/StickLoose.hpp"

#include <Arduino.h>

typedef decltype(millis()) time_t;

class Timer: public DataSource{
public:
  Timer(StickLoose& _throttle);
  virtual size_t get_recomended_length(){ return 5; }
  virtual const char* get_name(char* const output, size_t length);
  virtual const char* get_data(char* const output);
  time_t get_time();
private:
  StickLoose& throttle;
  time_t previousTime = 0;
  time_t totalTime = 0;
};



#endif
