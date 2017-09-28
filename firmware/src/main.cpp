/*
To do:
  - Add option to turn screen off
  - Check constness of member functions
*/

#include "DataSource/Battery/BatteryVehicle.hpp"
#include "DataSource/Battery/BatteryCell.hpp"
#include "DataSource/Battery/BatteryLocal.hpp"
#include "LedStrip.hpp"
#include "led_data_source.hpp"
#include "DataSource/DigitalSwitch.hpp"
#include "DataSource/SignalStrength.hpp"
#include "DataSource/frequency_counter.hpp"
#include "Wireless.hpp"
#include "DataSource/Stick/StickLoose.hpp"
#include "DataSource/Stick/StickCentred.hpp"
#include "page/PageStats.hpp"
#include "RotaryEncoder.hpp"
#include "Display.hpp"
#include "counter.hpp"
#include "DataSource.hpp"
#include "DataSource/Timer.hpp"
#include <Adafruit_NeoPixel.h>

#include <wire.h>
#include <LiquidCrystal_I2C.h>

#include "Arduino.h"

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

Wireless wireless(7, 8);

DigitalSwitch aux0(5, "A0", 0);
DigitalSwitch aux1(A2, "A1", 1);
DigitalSwitch aux2(0, "A2", 0);
StickLoose throttle(A7,"Th",0);
StickCentred roll (A1, "Ro", 1);
StickCentred yaw(A0, "Ya", 0);
StickCentred pitch(A6, "Pi", 0);

BatteryVehicle batteryVehicle("Qu/V");
BatteryCell batteryCell("Ce/V", batteryVehicle, 3);
BatteryLocal batteryLocal("Tr/V", A3, 97);
Timer timer(throttle);
SignalStrength signalStrength(wireless.transmissionFrequencyCounter, wireless.telemetryFrequencyCounter);

PageStats<14> page1;
Display<1> display;
LedStrip ledStrip(9, &signalStrength, nullptr, &batteryLocal, &batteryCell);

RotaryEncoder<3, 6, 4> rotaryEncoder;

void interruptWrapper(){ // to attach an interupt to a method, the method must be wrapped in a non-member function
  rotaryEncoder.refresh();
}

void setup() {
    // interupt attached for rotaryEncoder
    attachInterrupt(digitalPinToInterrupt(3), interruptWrapper, CHANGE);

    // initialising LCD library stuff
    lcd.begin(16, 2);
    lcd.setBacklightPin(3, POSITIVE);
    lcd.setBacklight(HIGH);

    // initialising radio
    wireless.begin();

    // initialising control inputs
    throttle.begin();
    pitch.begin();
    roll.begin();
    yaw.begin();
    aux0.begin();
    aux1.begin();
    aux2.begin();

    batteryLocal.begin();

    // initialising outputs
    display.setPage(0, &page1);
    ledStrip.begin();

    // associating data sources with stats page
    // in future this might be done in the constructor
    page1.addDataSource(&throttle);
    page1.addDataSource(&pitch);
    page1.addDataSource(&roll);
    page1.addDataSource(&yaw);
    page1.addDataSource(&aux0);
    page1.addDataSource(&aux1);
    page1.addDataSource(&aux2);
    page1.addDataSource(&timer);
    page1.addDataSource(&wireless.transmissionFrequencyCounter);
    page1.addDataSource(&wireless.telemetryFrequencyCounter);
    page1.addDataSource(&signalStrength);
    page1.addDataSource(&batteryVehicle);
    page1.addDataSource(&batteryCell);
    page1.addDataSource(&batteryLocal);

}

void loop(){
  Stick::new_loop(); // tells every Stick that the programs main loop has completed a cycle, this allows sticks to only access the ADC once per loop, no matter how many times they are read

  // transfering data from the control inputs to the radio
  wireless.controlPacket.throttle = throttle.read();
  wireless.controlPacket.pitch = pitch.read();
  wireless.controlPacket.roll = roll.read();
  wireless.controlPacket.yaw = yaw.read();
  wireless.controlPacket.aux0 = aux0.read() == 0 ? 0 : aux0.read() == 3 ? 1000 : 500;
  wireless.controlPacket.aux1 = aux1.read() == 0 ? 0 : aux1.read() == 3 ? 1000 : 500;
  wireless.controlPacket.aux2 = aux2.read();
  wireless.send();

  batteryVehicle.setValue(wireless.telemetryPacket.v_bat); // transfering the battery voltage from the radio to the DataSource which can be accessed by the display and LED

  ledStrip.update(); // the ledStrip will collect the data from its accosiated LedDataSources and update the LED outputs

  display.draw(lcd); // the display will collect the data from its associated DataSources and update the LCD accordingly

  display.move(rotaryEncoder.get()); // input data is transfered from the rotaryEncoder to the display for navigating the menu

}
