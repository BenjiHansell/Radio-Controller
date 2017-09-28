#pragma once

#include "page.hpp"

#include <wire.h>
#include <LCD.h>

template <size_t number_of_pages>
class Display{
public:
  void setPage(int idx, Page* p){ array_of_pages[idx] = p; }
  void draw(LCD& lcd);
  direction move(direction d);
private:
  size_t current_page_number = 0; // could just be made into an int, counter_stop causes crashes and therefore isn't relied on anyway
  size_t previous_page_number = -1; // if this doesn't match current_page_number then the screen must be cleared
  Page* array_of_pages[number_of_pages];
  bool current_backlight_state = true;
};

template<size_t number_of_pages>
void Display<number_of_pages>::draw(LCD& lcd){
  lcd.setBacklight(current_backlight_state);
  if(current_page_number != previous_page_number){
    previous_page_number = current_page_number;
    array_of_pages[current_page_number]->initialise(lcd);
  }else{
    array_of_pages[current_page_number]->draw(lcd);
  }
}

template<size_t number_of_pages>
direction Display<number_of_pages>::move(direction d){
  d = array_of_pages[current_page_number]->move(d);
  switch(d){
    case long_press:
      current_backlight_state = !current_backlight_state;
      break;
    case left:
      if(current_page_number > 0){
        current_page_number--;
        return none_horizontal;
      }else{
        return left;
      }
      break;
    case right:
      if(current_page_number < number_of_pages - 1){
        current_page_number++;
        return none_horizontal;
      }else{
        return right;
      }
      break;
    case up:
      return none_vertical;
      break;
    case down:
      return none_vertical;
      break;
    default: break;
  }
  return d;
}
