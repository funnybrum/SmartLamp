#include "Lamp.h"

/**
 * ESPxxxx has issues with OneWire/I2C communication. If any of these is used heavily the WiFi
 * functionality is being impacted. Reducing the number of OneWire/I2C reads makes the issue
 * almost undetectable. These below are the intervals for OneWire communication with the DS18B20.
 */
#define DS18B20_POOL_INTERVAL_SHORT 5000
#define DS18B20_POOL_INTERVAL_LONG 30000

DS18B20::DS18B20(uint8_t pin) {
    _oneWire = new OneWire(pin);
    _sensor = new DallasTemperature(_oneWire);
}

void DS18B20::begin() {
    _sensor->begin();
    _lastRead = millis() - DS18B20_POOL_INTERVAL_LONG;
    if (_sensor->getDS18Count() != 1) {
        logger.log("Detected %d DS18B20 devices!", _sensor->getDS18Count());
    }
    _pendingUpdate = false;
    _temp = 0;
}

void DS18B20::loop() {
    if (_sensor->getDS18Count() != 1) {
        return;
    }

    // Higher pool inteval results in less WiFi interferences.
    unsigned long poolInterval = DS18B20_POOL_INTERVAL_LONG;
    if (controller.isOn() && _temp > LED_DIM_TEMP) {
        poolInterval = DS18B20_POOL_INTERVAL_SHORT;
    }

    if (millis() - _lastRead > poolInterval) {
        // Request temperature update from the sensor;
        _sensor->requestTemperatures();
        _lastRead = millis();
        _pendingUpdate = true;
    }

    if (_pendingUpdate && millis() - _lastRead > 500) {
        // Direct call to ->getTempCByIndex(0) after ->requestTemperatures() results to an error.
        // Wait a bit before calling the ->getTempCByIndex(0).
        _pendingUpdate = false;
        float temp = _sensor->getTempCByIndex(0);
        if (0 < temp && temp < 100) {
            _temp = temp;
        } else {
            logger.log("Detected invalid temperature %d, ignoring it.", (int)temp);
            _lastRead = millis() - DS18B20_POOL_INTERVAL_LONG;
        }
    }
}

int8_t DS18B20::getTemperature() {
    return _temp;
}