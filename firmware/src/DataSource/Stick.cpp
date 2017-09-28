#include "Stick.hpp"

//#include <string.h> // for copying char arrays
#include "num_to_str.hpp"

bool Stick::loop_identifier = 0;

Stick::Stick(uint8_t _pin, const char _name[3], const bool _reverse, const uint8_t _margin) :
	pin(_pin),
	margin(_margin),
	max(), // the constructor of a memorable<type> needs to be called to read from EEPROM
	min(),
	raw(1024),
	reverse(_reverse),
	last_loop_identifier(1),
	name(_name)
{
	//strcpy(name, _name);
}

#include <Arduino.h>

void Stick::begin(){
	pinMode(pin, INPUT);
	max = max - 16;
	if (max > 1024) max = 0;
	min = min + 16;
	// in case of EEPROM corruption or change in stick hardware, the min and max will tend towards valid values with each boot
}

uint_fast16_t Stick::read() {
	return 0;
}

void Stick::do_a_read_maybe() {
// this code should be modified such that it only runs once per loop
if(last_loop_identifier != loop_identifier){
		last_loop_identifier = loop_identifier;
		raw = analogRead(pin);
		if (reverse) raw = 1023-raw;
		if (min > raw) min = raw;
		if (max < raw) max = raw;
  }
}

void Stick::new_loop() {
	loop_identifier = !loop_identifier;
}
