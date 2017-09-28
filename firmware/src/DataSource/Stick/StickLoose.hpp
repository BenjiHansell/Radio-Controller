#pragma once

#include "DataSource/Stick.hpp"

class StickLoose : public Stick // a stick which holds its position when released
{
public:
	StickLoose(uint8_t _pin, const char name[2] = "??", bool _reverse = 0, uint8_t _margin = 20);
	virtual ~StickLoose() = default;
	virtual uint_fast16_t read();
	virtual const char* get_data(char* const output);
};
