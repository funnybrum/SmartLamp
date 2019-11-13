#include "Lamp.h"

LEDDriver::LEDDriver(uint8_t dimPin, uint8_t enablePin) {
    _dimPin = dimPin;
    _enablePin = enablePin;
    pinMode(_dimPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    off();
    setBrightness(0);
}

void LEDDriver::begin() {
}

void LEDDriver::loop() {
}

void LEDDriver::on() {
    digitalWrite(_enablePin, HIGH);
}

void LEDDriver::off() {
    digitalWrite(_enablePin, LOW);
}

void LEDDriver::setBrightness(uint8_t brightness) {
    // analogWrite(0) -> full brightness
    // analogWrite(1023) -> minimum brightness
    int pwmValue = map(brightness, 0, 100, 1023, 0);
    analogWrite(_dimPin, pwmValue);
}
