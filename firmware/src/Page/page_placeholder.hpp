#ifndef PAGE_PLACEHOLDER_H
#define PAGE_PLACEHOLDER_H

#include "page.hpp"

// test page, not for actual use
class page_placeholder: public page{
  public:
    virtual void draw(LCD&);
    virtual direction move(direction d);
  private:
    counter_stop<int8_t, 0, 15> x = 0;
    counter_stop<int8_t, 0, 1> y = 0;
};

void page_placeholder::draw(LCD& lcd){
  lcd.setCursor(0,y);
  for(int i = 0; i < x; i++){
    lcd.print(' ');
  }
  lcd.print('.');
  for(int i = 0; i < 15 - x; i++){
    lcd.print(' ');
  }
  for(int j = 0; j < 2; j++){
    if (j != y){
      lcd.setCursor(0,j);
        for(int i = 0; i < 16; i++){
          lcd.print(' ');
        }
  }
  }
}

direction page_placeholder::move(direction d){
  switch(d){
    case left:
      if (x.at_lower_limit()) return left;
      x--;
      return(none_horizontal);
      break;
    case right:
      if (x.at_upper_limit()) return right;
      x++;
      return(none_horizontal);
      break;
    case up:
      y--;
      return(none_vertical);
      break;
    case down:
      y++;
      return(none_vertical);
      break;
    default:
    break;
  }
  return d;
}

#endif
