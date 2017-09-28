#include "StickLoose.hpp"
#include <Arduino.h>
#include "num_to_str.hpp"

StickLoose::StickLoose(uint8_t _pin, const char _name[3], bool _reverse, uint8_t _margin) :
	Stick(_pin, _name, _reverse, _margin)
{
}

const char* StickLoose::get_data(char* const output){
 auto val = read()/10;
	if(val != 100){
		output[0] = unit_to_char(val/10);
		output[1] = unit_to_char(val%10);
	}else{
		output[0] = 'X';
		output[1] = 'X';
	}
	output[2] = '\0';
//	previous_raw = raw;
	return output;
}

 uint_fast16_t StickLoose::read() {
 	do_a_read_maybe();
 	int32_t output = (int32_t)(raw - min) * (1000 + 2 * (margin)) / (max - min) - (margin);
 	if (output < 0) output = 0;
 	if (output > 1000) output = 1000;
 	//return raw; // test
 	return output;
 }
