#pragma once

#include "Lamp.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class DS18B20 {
    public:
        DS18B20(uint8_t pin);
        void begin();
        void loop();
        int8_t getTemperature();

    private:
        DallasTemperature* _sensor;
        OneWire* _oneWire;
        unsigned long _lastRead;
        bool _pendingUpdate;
        int _temp;
};