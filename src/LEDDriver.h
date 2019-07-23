#pragma once

#include "Lamp.h"

class LEDDriver {
    public:
        LEDDriver(uint8_t dimPin, uint8_t enablePin) {
            _dimPin = dimPin;
            _enablePin = enablePin;
            pinMode(_dimPin, OUTPUT);
            pinMode(_enablePin, OUTPUT);
            off();
            setBrightness(100);
        }

        void begin() {
        }

        void loop() {
        }

        void on() {
            digitalWrite(_enablePin, HIGH);
        }

        void off() {
            digitalWrite(_enablePin, LOW);
        }

        void setBrightness(uint8_t brightness) {
            // analogWrite(0) -> full brightness
            // analogWrite(1023) -> minimum brightness
            int pwmValue = map(0, 100, 1023, 0, brightness);
            analogWrite(_dimPin, pwmValue);
        }

    private:
        uint8_t _dimPin;
        uint8_t _enablePin;
};