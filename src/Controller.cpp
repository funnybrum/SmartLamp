#include "Lamp.h"

Controller::Controller(LEDDriver* led, DS18B20* tempSensor) {
    _led = led;
    _tempSensor = tempSensor;
    _powered = false;
}

void Controller::begin() {
    _lastCorrection = millis() - 1000;
}

void Controller::loop() {
    if (!_powered) {
        return;
    }

    _calculateTargetBrightness();

    uint8_t ledTemp = _tempSensor->getTemperature();
    uint8_t max_brightness = 100;

    // Simple logic for decreasing the brightness. Start dimming at 75C and fully turn off
    // the LED at 90C.
    // TODO - PID controller will fit better here. Or at least some threshold to limit the
    // disco effect...
    if (ledTemp >= LED_DIM_TEMP) {
        max_brightness = 10 * max(LED_DIM_TEMP - ledTemp, 0);
        logger.log("LED at %dC, limitting max brighness to %d%%", ledTemp, max_brightness);
    }

    // TODO: Additional logic based on the current time to adjust the brightness.

    if (_targetBrightness > _brightness) {
        _brightness++;
    }

    if (_targetBrightness < _brightness) {
        _brightness--;
    }

    if (_brightness > max_brightness) {
        _brightness = max_brightness;
    }

    _led->setBrightness(_brightness);
    logger.log("Temp: %d, brightness: %d", ledTemp, _brightness);
}

void Controller::setBrightness(uint8_t brightness) {
    _targetBrightness = brightness;
}

void Controller::setPower(bool enable) {
    _powered = enable;
    if (_powered) {
        _led->on();
    } else {
        _led->off();
    }
}

bool Controller::getPower() {
    return _powered;
}

void Controller::calculateTargetBrightness() {

}