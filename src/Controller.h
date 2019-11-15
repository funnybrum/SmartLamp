#pragma once

#include "Lamp.h"

enum Mode {
    AUTO,
    MANUAL
};

enum State {
    ON,
    OFF
};

class Controller {
    public:
        Controller(LEDDriver* led, DS18B20* tempSensor);
        void begin();
        void loop();

        void setBrightness(uint8_t brightness);
        void setAutoBrightness();

        void turnOn();
        void turnOff();
        bool isOn();
 
    private:
        int calcTargetBrightness();
        int calcMaxBrightness();

        LEDDriver* _led;
        DS18B20* _tempSensor;
        uint8_t _brightness = 0;

        Mode _mode = AUTO;
        State _state = ON;
};