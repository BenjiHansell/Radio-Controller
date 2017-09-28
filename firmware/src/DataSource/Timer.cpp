#include "Timer.hpp"

Timer::Timer(StickLoose& _throttle)
 :throttle(_throttle)
{

}

time_t Timer::get_time(){ // returns time in seconds
  const time_t currentTime = millis();
  if (throttle.read() > 50){ // if throttle is active
    const time_t deltaT = currentTime - previousTime;
    totalTime += deltaT;
  }
  previousTime = currentTime;
  return totalTime/1000;
}

const char* Timer::get_name(char* const output, size_t length){
  output[0] = 'A';
  output[1] = 'i';
  output[2] = 'r';
  output[3] = ' ';
  output[4] = 'T';
  output[length] = '\0';
  return output;
}

const char* Timer::get_data(char* const output){
  for(size_t i = 0; i < 5; i++) output[i] = ' ';
  output[0] = unit_to_char(((get_time()/600)%10)); // %10 allows 100 minutes before rolover, %6 would allow 60 minutes before rollover
  output[1] = unit_to_char(((get_time()/60)%10));
  output[2] = ':';
  output[3] = unit_to_char(((get_time()/10)%6));
  output[4] = unit_to_char(get_time()%10);
  output[5] = '\0';
  return output;
}
