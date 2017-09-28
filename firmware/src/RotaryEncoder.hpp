#pragma once

#include "Arduino.h"

#include <StandardCplusplus.h>
#define STD_LIB_AVAILABLE // for static_queue.h
#include <static_queue.h>

enum direction{ up, down, left, right, none_vertical, none_horizontal, long_press };

struct rotary_encoder_snapshot{
  rotary_encoder_snapshot(bool _data = 1, bool _clock = 1, bool _sw = 1);
  bool data : 1;
  bool clock : 1;
  bool sw : 1;
  bool operator!=(const rotary_encoder_snapshot& rhs);
};

typedef decltype(millis()) time_t;

template<uint8_t pin_data, uint8_t pin_clock, uint8_t pin_switch>
class RotaryEncoder{
public:
  void begin();
  void refresh(); // takes a snapshot of the current pin states and records it for use in future calls of get(), should be attached to an interupt on either the data or clock pin
  direction get();
private:
  static_queue<rotary_encoder_snapshot, 20> record;
  bool previous_data = 1;
  bool previous_switch = 1;
  bool vertical = 0;
  bool long_press_has_been_acknowledged = 0;
  time_t time_button_was_last_not_pressed = 0;
};

template<uint8_t pin_data, uint8_t pin_clock, uint8_t pin_switch>
void RotaryEncoder<pin_data, pin_clock, pin_switch>::begin(){
  pinMode(pin_data, INPUT);
  pinMode(pin_clock, INPUT);
  pinMode(pin_switch, INPUT);
}

template<uint8_t pin_data, uint8_t pin_clock, uint8_t pin_switch>
void RotaryEncoder<pin_data, pin_clock, pin_switch>::refresh(){
  record.push(rotary_encoder_snapshot(digitalRead(pin_data), digitalRead(pin_clock), digitalRead(pin_switch)));
}

template<uint8_t pin_data, uint8_t pin_clock, uint8_t pin_switch>
direction RotaryEncoder<pin_data, pin_clock, pin_switch>::get(){
  time_t time_now = millis();
  if (long_press_has_been_acknowledged == 0 && time_now > time_button_was_last_not_pressed + 1000){
    long_press_has_been_acknowledged = 1;
    return long_press;
  }
  refresh();
  direction output = vertical ? none_vertical : none_horizontal;
  while (output == none_vertical || output == none_horizontal){
    if (record.empty()) return output;
    const rotary_encoder_snapshot& s = record.front();
    const bool current_data = s.data;
    const bool current_clock = s.clock;
    const bool current_switch = s.sw;
    if (current_switch) {
      time_button_was_last_not_pressed = time_now;
      long_press_has_been_acknowledged = 0;
    }
    record.pop();
    if(current_switch == 0 && current_switch != previous_switch) vertical = !vertical;
    previous_switch = current_switch;
    if(current_data == 0 && previous_data == 1){
      if (vertical == true){
        output = current_clock ? down : up;
      } else {
        output = current_clock ? left : right;
      }
    }
    previous_data = current_data;
  }
  return output;
}
