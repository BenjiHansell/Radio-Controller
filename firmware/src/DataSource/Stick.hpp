#pragma once

#include "memorable.hpp"
#include "DataSource.hpp"

#include <stdint.h>

class Stick : public DataSource
{
public:
	Stick(uint8_t _pin, const char name[3] = "??", const bool _reverse = 0, const uint8_t _margin = 20); // name could be made const
	virtual ~Stick() = default;
	virtual void begin();
	virtual uint_fast16_t read(); // on first read it reads previous min and max from EEPROM, on a later read it writes new min and max values (minus a small amount)
	static void new_loop();
	virtual const char* get_name(char* const output){return name;}
	virtual const char* get_data(char* const output){return name;} // this version of get_data should never be called (only overloads)
protected:
	void do_a_read_maybe(); // adjusts min and max for a particular read if necessary
	const uint_fast8_t pin;
	const uint_fast8_t margin;
	Memorable<uint16_t> max; // the maximum raw value the stick has ever seen
	Memorable<uint16_t> min; // the minimum raw value the stick has ever seen
	uint16_t raw; // defaults to 1024 to indicate first call or read();
	const bool reverse;
	bool last_loop_identifier;
	static bool loop_identifier; // tells the read() function whether a new loop has happened (and hence whether a new analogRead() is needed)
	const char* name;
};
