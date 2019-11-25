#pragma once

#include "Lamp.h"

class LEDDriver {
    public:
        LEDDriver(uint8_t dimPin, uint8_t enablePin);
        void begin();
        void loop();
        void on();
        void off();
        void setBrightness(uint8_t brightness);

    private:
        uint8_t _dimPin;
        uint8_t _enablePin;
        int _currentPWM;
        // TODO: Add calibration value that specify the analog value of the max brightness. This
        // should be unique per lamp instance (resistor tolerance at least would impact it).

        int _dimMatrix[2][3] = {
            {0, 30, 100}, // Dim %
            {823, 716, 0} // PWM
        };
};