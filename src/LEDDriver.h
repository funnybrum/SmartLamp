#pragma once

#include "Lamp.h"

class LEDDriver {
    public:
        LEDDriver(uint8_t dimPin, uint8_t enablePin);
        void begin();
        void loop();
        void on();
        void off();
        void setBrightness(int brightness);

    private:
        uint8_t _dimPin;
        uint8_t _enablePin;
        int _currentBrightness;
        // TODO: Add calibration value that specify the analog value of the max brightness. This
        // should be unique per lamp instance (resistor tolerance at least would impact it).

        int _dimMatrix[2][8] = {
            // Dim % in 0.1, i.e. 10% = 100, 30% = 300
            {0,    20,   70,   240,  300 , 500 , 800 , 1000},

            // PWM, 0 would be max brightness, 5000 would be min.
            {4000, 3900, 3820, 3650, 3250, 2500, 1300, 0} 
        };
};