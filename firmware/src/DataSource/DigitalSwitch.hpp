#pragma once

#include "DataSource.hpp"

#include <stdint.h>

class DigitalSwitch : public DataSource
{
public:
	DigitalSwitch(uint_fast8_t _pin, const char _name[3] = "D?", bool _reverse = false, bool _pullup = true);
	void begin();
	virtual ~DigitalSwitch() = default;
	uint8_t read();
	virtual const char* get_name(char* const output){return name;}
	virtual const char* get_data(char* const output);
protected:
	const uint8_t pin;
	const bool reverse;
	const bool pullup;
	const char* const name;
	bool state_with_pullup = false;
	bool state_without_pullup = false;
	bool previous_read_type = false;
};
