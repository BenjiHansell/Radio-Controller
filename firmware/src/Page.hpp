#ifndef PAGE_H
#define PAGE_H

#include "RotaryEncoder.hpp"
#include "counter.hpp"

#include <LCD.h>

// base class
class Page{
  public:
    virtual void initialise(LCD&); // to be called after page change, generally clears the page and loads any custom chars and performs first draw()
    virtual void draw(LCD&){}; // draws to screen, screen must initialised before first call of a page's draw() but the page is expected to manage screen clearing for subsequent calls
    virtual direction move(direction d){return d;} // function takes in direction up/down/left/right/none for use navigating inside the page and returns a direction left/right/none to indicate whether display needs to navgating between pages
};

void Page::initialise(LCD & lcd){
  lcd.clear();
  draw(lcd);
}

#endif
