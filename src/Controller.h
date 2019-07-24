#pragma once

#include "Lamp.h"

class Controller {
    public:
        Controller(LEDDriver* led, DS18B20* tempSensor);
        void begin();
        void loop();
        void setBrightness(uint8_t brightness);
        void setPower(bool enable);
 
    private:
        LEDDriver* _led;
        DS18B20* _tempSensor;
        Logger* _logger;
        uint8_t _brightness;
        uint8_t _targetBrightness;
        unsigned long _lastCorrection;
        bool _powered;

};