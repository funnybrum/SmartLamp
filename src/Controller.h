#pragma once

#include "Lamp.h"

class Controller {
    public:
        Controller(LEDDriver* led, DS18B20* tempSensor) {
            _led = led;
            _tempSensor = tempSensor;
            overheating = false;
        }

        void begin() {
            _lastCorrection = millis() - 1000;
        }

        void loop() {
            if (millis() - _lastCorrection < 1000) {
                // No more than one change each second.
                return;
            }
            _lastCorrection = millis();

            uint8_t ledTemp = _tempSensor->getTemperature();

            if (ledTemp > 80) {
                logger.log("LED temperature is %dC, turning off.", ledTemp);
                _led->off();
                return;
            }

            if (ledTemp > 75) {
                overheating = true;
                // In case of LED temperature over 75C - decrease brightness to protect the LED
                logger.log("LED at %dC, decresing brighness...", ledTemp);
                if (_targetBrightness < _brightness) {
                    _brightness = _targetBrightness;
                } else {
                    _brightness--;
                }
                _led->setBrightness(_brightness);
                return;
            }

            if (ledTemp < 70) {
                overheating = false;
                if (_targetBrightness != _brightness) {
                    _brightness = _targetBrightness;
                }
                _led->setBrightness(_brightness);
                return;
            }

            if (ledTemp < 73) {
                // In the safe limit. It is safe
                if (_targetBrightness > _brightness) {
                    _brightness++;
                    _led->setBrightness(_brightness);
                }
            }

        }

    private:
        LEDDriver* _led;
        DS18B20* _tempSensor;
        uint8_t _brightness;
        uint8_t _targetBrightness;
        unsigned long _lastCorrection;
        boolean overheating;
};