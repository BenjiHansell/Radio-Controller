#pragma once

#include "DataSource/Stick.hpp"

struct midpoints { // a shitty alternative to C++11's <array> container
	uint16_t m[9];
};

class StickCentred : public Stick // a stick which returns to the centre when released
{
public:
	StickCentred(uint8_t _pin, const char name[2] = "??", bool _reverse = 0, uint8_t _margin = 20);
	virtual ~StickCentred() = default;
	virtual uint_fast16_t read();
  virtual const char* get_data(char* const output);
	virtual void begin();
protected:
	uint16_t midpoint; // this is stored unnecessarily, but recalculating it for every read() would be a huge waste of processing power


};
