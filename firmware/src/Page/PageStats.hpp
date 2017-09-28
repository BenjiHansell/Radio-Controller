#ifndef PageStats_H
#define PageStats_H

#include "Page.hpp"
#include "DataSource.hpp"
#include "memorable.hpp"

#include <stddef.h>
#include <stdint.h>
#include <Arduino.h>

#include <StandardCPlusPlus.h>
#include <array>

enum custom_characters{
  left_arrow = 0,
  right_arrow = 1,
  up_arrow_left = 2,
  up_arrow_right = 3,
  down_arrow_left = 4,
  down_arrow_right = 5,
  battery_radio = 6,
  battery_craft = 7
};

// stats page is main page which reports e.g. battery level
template<size_t number_of_data_sources>
class PageStats : public Page {
  static const int max_number_of_columns = 5;
  public:
    PageStats();
    virtual void initialise(LCD&);
    virtual void draw(LCD&);
    virtual void draw(LCD&, bool full);
    virtual direction move(direction d);
    bool addDataSource(DataSource* d);
  private:
    uint8_t x_position_upper_limit();
    void draw_full(LCD&);  // redraws everything (in case of page change or menu movement)
    void declare_menu_as_active() {time_of_last_menu_activity = millis();}
    bool is_menu_active() {return millis() - time_of_last_menu_activity < 2000;}
    decltype(millis()) time_of_last_menu_activity;
    uint8_t x_position = 0;
    Memorable<std::array<counter_rollover<int8_t, 0, number_of_data_sources-1>, max_number_of_columns>> selected_data_source_per_column;
    DataSource* array_of_data_sources[number_of_data_sources];
    bool vertical;
    size_t actual_number_of_data_sources = 0;
    bool previous_is_menu_active;
};

template<size_t number_of_data_sources>
PageStats<number_of_data_sources>::PageStats()
 :selected_data_source_per_column()
{
  for (size_t i = 0; i < max_number_of_columns; i++) selected_data_source_per_column.x[i].normalise();
}

template<size_t number_of_data_sources>
bool PageStats<number_of_data_sources>::addDataSource(DataSource* d){
  if(actual_number_of_data_sources == number_of_data_sources) return 0;
  array_of_data_sources[actual_number_of_data_sources++] = d;
  return 1;
}

template<size_t number_of_data_sources>
void PageStats<number_of_data_sources>::draw(LCD& lcd){
  draw(lcd, false);
}

template<size_t number_of_data_sources>
void PageStats<number_of_data_sources>::draw_full(LCD& lcd){
  draw(lcd, true);
}

template<size_t number_of_data_sources>
void PageStats<number_of_data_sources>::draw(LCD& lcd, bool full){
  lcd.home();
  if(previous_is_menu_active/* || is_menu_active()*/ || full  || !random(0,20)){  // the first line of the menu rarely changes, so it is only drawn under certin conditions
    for(int i = 0; i < max_number_of_columns; i++){
      if (i == x_position) lcd.write(is_menu_active()?vertical?uint8_t(up_arrow_left):uint8_t(left_arrow):' ');
      else if (i == x_position + 1) lcd.write(is_menu_active()?vertical?uint8_t(up_arrow_right):uint8_t(right_arrow):' ');
      else lcd.print(' ');
      char temp[17]; // 16+1 is an arbitrary maximum expected data source string length
      const char* const name = array_of_data_sources[selected_data_source_per_column.x[i]]->get_name(temp);
      lcd.print(name);
    }
    lcd.write((x_position == max_number_of_columns - 1 && is_menu_active()) ? vertical ? uint8_t(up_arrow_right) : uint8_t(right_arrow) : ' ');
  }
  previous_is_menu_active = is_menu_active();

  lcd.setCursor(0,1);
  for(int i = 0; i < max_number_of_columns; i++){
    if (i == x_position) lcd.write((vertical&&is_menu_active())?uint8_t(down_arrow_left):uint8_t(' '));
    else if (i == x_position + 1) lcd.write((vertical&&is_menu_active())?uint8_t(down_arrow_right):uint8_t(' '));
    else lcd.print(' ');
    char temp[17]; // 16+1 is an arbitrary maximum expected data source string length
    const char* const name = array_of_data_sources[selected_data_source_per_column.x[i]]->get_data(temp);
    if(array_of_data_sources[selected_data_source_per_column.x[i]]->has_changed() || full || previous_is_menu_active){
      lcd.print(name);
    }else{
      for(unsigned int i = 0; i < array_of_data_sources[selected_data_source_per_column.x[i]]->get_recomended_length(); i++) lcd.moveCursorRight();
    }
  }
  lcd.write((x_position == max_number_of_columns - 1 && vertical && is_menu_active()) ? uint8_t(down_arrow_right) : ' ');

}

template<size_t number_of_data_sources>
direction PageStats<number_of_data_sources>::move(direction d){
  static direction d_previous = left;
  if (d_previous != d){
    declare_menu_as_active();
    d_previous = d;
  }
  switch(d){
    case long_press:
      return long_press; // long press is promoted to control the object owning the page (i.e. the display)
      break;
    case left:
      vertical = false;
      if (x_position == 0) return left;
      x_position--;
      return none_horizontal;
      break;
    case right:
      vertical = false;
      if (x_position >= x_position_upper_limit()) return right;
      x_position++;
      return none_horizontal;
      break;
    case up:
      vertical = true;
      selected_data_source_per_column.x[x_position]--;
      selected_data_source_per_column.write();
      break;
    case down:
      vertical = true;
      selected_data_source_per_column.x[x_position]++;
      selected_data_source_per_column.write();
      break;
    case none_vertical:
      vertical = true;
      break;
    case none_horizontal:
     vertical = false;
     break;
  }
  return d;
}

template<size_t number_of_data_sources>
uint8_t PageStats<number_of_data_sources>::x_position_upper_limit(){
  uint8_t x_pos = 0;
  uint8_t number_of_columns = 0;
  while(x_pos <= 14 && number_of_columns <= max_number_of_columns){
    x_pos += (array_of_data_sources[selected_data_source_per_column.x[number_of_columns]]->get_recomended_length() + 1);
    number_of_columns++;
  }
  return number_of_columns - 1;
}

template<size_t number_of_data_sources>
void PageStats<number_of_data_sources>::initialise(LCD& lcd){
  lcd.clear();
  //declare_menu_as_active();
  draw_full(lcd);
  uint8_t customChar0[8] = { // using PROGMEM for these does not seem to help
    0b00000,
  	0b00010,
  	0b00100,
  	0b01111,
  	0b00100,
  	0b00010,
  	0b00000,
  	0b00000
  };
  lcd.createChar(left_arrow, customChar0);
  uint8_t customChar1[8] = {
  	0b00000,
  	0b01000,
  	0b00100,
  	0b11110,
  	0b00100,
  	0b01000,
  	0b00000,
  	0b00000
  };
    lcd.createChar(right_arrow, customChar1);
  {
    uint8_t customChar[8] = {
      0b00001,
    	0b00011,
    	0b00101,
    	0b00001,
    	0b00001,
    	0b00001,
    	0b00001,
    	0b00001
    };
    lcd.createChar(up_arrow_left, customChar);
  }
  {
    uint8_t customChar[8] = {
      0b10000,
    	0b11000,
    	0b10100,
    	0b10000,
    	0b10000,
    	0b10000,
    	0b10000,
    	0b10000
    };
    lcd.createChar(up_arrow_right, customChar);
  }
  {
    uint8_t customChar[8] = {
      0b00001,
    	0b00001,
    	0b00001,
    	0b00001,
    	0b00101,
    	0b00011,
    	0b00001,
    	0b00000
    };
    lcd.createChar(down_arrow_left, customChar);
  }
  {
    uint8_t customChar[8] = {
      0b10000,
    	0b10000,
    	0b10000,
    	0b10000,
    	0b10100,
    	0b11000,
    	0b10000,
    	0b00000
    };
    lcd.createChar(down_arrow_right, customChar);
  }
}

#endif
