#include "Lamp.h"

Controller::Controller(LEDDriver* led, DS18B20* tempSensor) {
    _led = led;
    _tempSensor = tempSensor;
}

void Controller::begin() {
    if (_state == ON) {
        _brightness = calcTargetBrightness();
        _led->setBrightness(_brightness);
        _led->on();
    }
}

void Controller::loop() {
    if (_state == OFF) {
        return;
    }

    int targetBrightness = min(calcTargetBrightness(), calcMaxBrightness());
    if (_brightness < targetBrightness) {
        _brightness++;
    }

    if (_brightness > targetBrightness) {
        _brightness--;
    }

    _led->setBrightness(_brightness);
    logger.log("Temp: %d, brightness: %d.%d",
               _tempSensor->getTemperature(),
               _brightness/10,
               _brightness%10);
}

void Controller::setBrightness(int brightness) {
    // Here we take %, but brightness stores it in 0.1% units.
    _brightness = brightness * 10;
    _mode = MANUAL;
}

void Controller::setAutoBrightness() {
    _mode = AUTO;
}

void Controller::turnOn() {
    if (_state == OFF) {
        _state = ON;
        _led->on();
    }
}

void Controller::turnOff() {
    if (_state == ON) {
        _state = OFF;
        _led->off();
    }
}

bool Controller::isOn() {
    return _state == ON;
}

#define EV_DIM_START 20
#define EV_DIM_FULL 24
#define MOR_DIM_FULL 6
#define MOR_DIM_END 8

int Controller::calcTargetBrightness() {
    // In manual mode - return current value;
    if (_mode == MANUAL) {
        return _brightness;
    }

    int hour = rtc.getHour();
    int minute = rtc.getMinute();

    // Note: the below would fail if the dimming/undimming interval starts and end in different
    // days.
    if (hour < MOR_DIM_FULL) {
        // Night mode.
        return 0;
    } else if (MOR_DIM_FULL <= hour && hour < MOR_DIM_END) {
        // Morning undimming mode.
        int m = (hour - MOR_DIM_FULL) * 60 + minute;
        return map(m, 0, (MOR_DIM_END - MOR_DIM_FULL) * 60, 0, 1000);
    } else if (MOR_DIM_END <= hour && hour < EV_DIM_START) {
        // Day mode.
        return 1000;
    } else if (EV_DIM_START <= hour && hour < EV_DIM_FULL) {
        // Evening dimming mode.
        int m = (hour - EV_DIM_START) * 60 + minute;
        return map(m, 0, (EV_DIM_FULL - EV_DIM_START) * 60, 1000, 0);
    } else {
        // Night mode
        return 0;
    }
}

int Controller::calcMaxBrightness() {
    // Limit max brightnes based on the LED temperature.
    uint8_t ledTemp = _tempSensor->getTemperature();

    if (ledTemp < LED_DIM_TEMP) {
        return 1000;
    }

    return map(ledTemp, LED_DIM_TEMP, LED_OFF_TEMP, 1000, 0);
}