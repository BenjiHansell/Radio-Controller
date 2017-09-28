#pragma once

#include <stdint.h>
#include <RF24.h>

#include "DataSource/frequency_counter.hpp"

#pragma pack(1)

struct ControlPacket
{
	uint16_t roll : 10;
	uint16_t pitch : 10;
	uint16_t throttle : 10;
	uint16_t yaw : 10;
	uint16_t aux0 : 10;
	uint16_t aux1 : 10;
	uint8_t aux2 : 2;
	uint8_t aux3 : 2;
};

struct TelemetryPacket
{
	uint8_t v_bat = 0;
};

class Wireless
{
public:
	Wireless(uint8_t _cepin, uint8_t _csnpin);
	void begin();       // Sets up the NRF24L01+
	void send();        // Sends a packet and store any ackPayload in an array of size 32 where the first memory address is *rx
	bool signal(uint32_t period = 100);      // Checks is there was an ack payload within the last period of milliseconds
	ControlPacket controlPacket;
	TelemetryPacket telemetryPacket;
	frequency_counter transmissionFrequencyCounter;
	frequency_counter telemetryFrequencyCounter;
private:
	RF24 radio;
	uint32_t last;  // = when radio was last recieved
	bool last_attempt; // not sure if this is really needed
};
