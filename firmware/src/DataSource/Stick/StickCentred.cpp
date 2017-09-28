#include "StickCentred.hpp"
#include "num_to_str.hpp"

#include <StandardCplusplus.h>
#include <algorithm> // for sorting stick start values

#include <Arduino.h>

StickCentred::StickCentred(uint8_t _pin, const char _name[3], bool _reverse, uint8_t _margin) :
	Stick(_pin, _name, _reverse, _margin)
{
}

const char* StickCentred::get_data(char* const output){
	//Stick::begin();
	int_fast16_t val = ((int_fast16_t)read()-500)/50;
	if(val > 0){
	 output[0] = '+';
	 output[1] = (val == 10) ? 'X' : unit_to_char(val);
	}else if(val < 0){
	 output[0] = '-';
	 output[1] = (val == -10) ? 'X' : unit_to_char(-val);
	}else{
	 output[0] = '0';
	 output[1] = '0';
	}
  output[2] = '\0';
  return output;
}

uint_fast16_t StickCentred::read() {
	if (raw == 1024) {
		begin();
	}
	do_a_read_maybe();
	int_fast16_t output;
	if (raw > midpoint + margin) {
		const uint_fast16_t range = max - midpoint - margin;
		const uint_fast16_t subtended = raw - midpoint;
		output = 500 + (uint_fast32_t)500 * subtended / range;
	}
	else if (raw < midpoint - margin) {
		const uint_fast16_t range = midpoint - min - margin;
		const uint_fast16_t subtended = midpoint - raw;
		output = 500 - (uint_fast32_t)500 * subtended / range;
	}
	else {
		output = 500;
	}
	if (output < 0) output = 0;
	if (output > 1000) output = 1000;
	return output;
}

void StickCentred::begin() {
	Stick::begin();
	Memorable<midpoints> mid;
	last_loop_identifier = !loop_identifier; // guarantees that do_a_read_maybe() will perform a read
	do_a_read_maybe();
	for (int i = 0; i < 8; i++)
		mid.x.m[i] = mid.x.m[i + 1];
	mid.x.m[8] = raw;
	mid.write(); // write() is manually called because copy constructor was never called
	uint16_t temp[9];
	for (int i = 0; i < 9; i++)
		temp[i] = mid.x.m[i];
	std::sort(temp, temp + sizeof temp / sizeof temp[0]);
	midpoint = temp[4]; // midpoint is now the median, there are probably smarter alternative algorithms, but this seems pretty robust
}
