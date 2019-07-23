#pragma once

#include "Lamp.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20 {
    public:
        DS18B20(uint8_t pin) {
            _oneWire = new OneWire(pin);
            _sensor = new DallasTemperature(_oneWire);
        }

        void begin() {
            _sensor->begin();
            _lastConversion = millis() - 1000 * 10;
            logger.log("Found %d OneWire devices.", _sensor->getDeviceCount());
            logger.log("Found %d DS18 devices.", _sensor->getDS18Count());
        }

        void loop() {
            if (millis() - _lastConversion > 5000) {
                // Request temperature every 5 seconds.
                _sensor->requestTemperatures();
            }
        }

        int8_t getTemperature() {
            // TODO - adjust to proper interval.
            // For some reason there should be delay between the requestTemperature and getTemp calls. Without such
            // the call below results in failure.
            if (millis() - _lastConversion < 200) {
                delay(200 - millis() - _lastConversion);
            }
            return _sensor->getTempCByIndex(0);
        }

    private:
        DallasTemperature* _sensor;
        OneWire* _oneWire;
        unsigned long _lastConversion;
};