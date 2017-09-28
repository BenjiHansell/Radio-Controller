#include "Wireless.hpp"

Wireless::Wireless(uint8_t _cepin, uint8_t _csnpin):
  transmissionFrequencyCounter("Sen"),
  telemetryFrequencyCounter("Rcv"),
	radio(_cepin, _csnpin),
	last(0)
	{
}

void Wireless::begin() {
	radio.begin();
	radio.openWritingPipe(0xE8E8F0F0E1LL);
	//radio.setDataRate(RF24_250KBPS);
	radio.setAutoAck(1);
	//    radio.setRetries(1,1);
	radio.enableAckPayload();
	radio.setPALevel(RF24_PA_MAX);
}

void Wireless::send() {
	last_attempt = radio.write(&controlPacket, sizeof controlPacket);
	transmissionFrequencyCounter.log();
	telemetryFrequencyCounter.log(last_attempt);
	while (radio.isAckPayloadAvailable()) {
		radio.read(&telemetryPacket, sizeof telemetryPacket);
		last = millis();
	}
}

bool Wireless::signal(uint32_t period) {
	if (!last) return 0;
	if (!period) return last_attempt;
	return (last + period > millis());
}
