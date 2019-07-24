#include "Lamp.h"

Controller::Controller(LEDDriver* led, DS18B20* tempSensor) {
    _led = led;
    _tempSensor = tempSensor;
    _powered = true;
}

void Controller::begin() {
    _lastCorrection = millis() - 1000;
}

void Controller::loop() {
    if (millis() - _lastCorrection < 1000) {
        // No more than one change each second.
        return;
    }
    _lastCorrection = millis();

    if (!_powered) {
        return;
    }

    uint8_t ledTemp = _tempSensor->getTemperature();
    uint8_t max_brightness = 100;

    // Simple logic for decreasing the brightness. Start dimming at 76C and fully turn off
    // the LED at 85C.
    if (ledTemp > 75) {
        uint8_t max_brightness = map(ledTemp, 76, 85, 0, 100);
        logger.log("LED at %dC, limitting max brighness to %d%%.", ledTemp, max_brightness);
    }

    // TODO: Additional logic based on the current time to adjust the brightness.

    _brightness = min(_targetBrightness, max_brightness);
    _led->setBrightness(_brightness);
}

void Controller::setBrightness(uint8_t brightness) {
    _targetBrightness = brightness;
}

void Controller::setPower(bool enable) {
    _powered = enable;
    if (_powered) {
        _led->off();
    } else {
        _led->on();
    }
}
