#include "DigitalSwitch.hpp"
#include "num_to_str.hpp"

#include <string.h>

#include "Arduino.h"

DigitalSwitch::DigitalSwitch(uint_fast8_t _pin, const char _name[3], bool _reverse, bool _pullup):
	pin(_pin),
	reverse(_reverse),
	pullup(_pullup),
	name(_name)
{
}

void DigitalSwitch::begin(){
	if (pullup) {
		pinMode(pin, INPUT_PULLUP);
	}
	else {
		pinMode(pin, INPUT);
	}

}

/*
A DigitalSwitch can be two or three pole.

Hardware configuration for two pole:
Pole one: tied low
Pole two: tied high

Hardware configuration for three pole:
Pole one: tied low
Pole two: pulled low with ~1 Mohm (or any resistor significantly weaker than the internal pullup)
Pole three: tied high

With each call of read(), the state of the pin is read and then the internal
pullup is toggled.  After two calls to read(), the three pole state can be
calculated.  It is done this way because time (<50 us) is needed between
toggling the pullup and reading the pin (probably due to stray capacitance).
*/

uint8_t DigitalSwitch::read() {
	if(previous_read_type){
		//Serial.println("about to read digital pin");
		state_without_pullup = digitalRead(pin);
		//Serial.println("done reading digital pin");
		//Serial.println("about to set digital pin mode as INPUT_PULLUP");
		pinMode(pin, INPUT_PULLUP);
		//Serial.println("done setting digital pin mode as INPUT_PULLUP");
	}else{
		//Serial.println("about to read digital pin");
		state_with_pullup = digitalRead(pin);
		//Serial.println("done reading digital pin");
		//Serial.println("about to set digital pin mode as INPUT");
		pinMode(pin, INPUT);
		//Serial.println("done setting digital pin mode as INPUT");
		// here be freeze

	}

	previous_read_type = !previous_read_type;
	if (state_with_pullup == state_without_pullup){
		if (reverse) return state_with_pullup ? 3 : 0;
		else 				 return state_with_pullup ? 0 : 3;
	}else{
		return 1;
	}
}

const char* DigitalSwitch::get_data(char* const output){
	auto state = read();
	output[0] = state ? '+' : '-';
	output[1] = state > 2 ? '+' : '-';
	output[2] = '\0';
	return output;
}
