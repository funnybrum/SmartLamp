#include "Lamp.h"

LEDDriver::LEDDriver(uint8_t dimPin, uint8_t enablePin) {
    _dimPin = dimPin;
    _enablePin = enablePin;
    pinMode(_dimPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    off();
    setBrightness(0);
}

void LEDDriver::begin() {
}

void LEDDriver::loop() {
}

void LEDDriver::on() {
    digitalWrite(_enablePin, HIGH);
}

void LEDDriver::off() {
    digitalWrite(_enablePin, LOW);
}

void LEDDriver::setBrightness(uint8_t brightness) {
    if (brightness < 0) {
        brightness = 0;
    }
    if (brightness > 100) {
        brightness = 100;
    }
    // analogWrite(0) -> full brightness
    // analogWrite(1023) -> minimum brightness
    int len = sizeof(_dimMatrix[0])/sizeof(_dimMatrix[0][0]);

    int l_in = -1;
    int h_in = -1;
    int l_out = -1;
    int h_out = -1;

    for (int i = 0; i < len-1; i++) {
        if (_dimMatrix[0][i] <= brightness && brightness <= _dimMatrix[0][i+1]) {
            l_in = _dimMatrix[0][i];
            h_in = _dimMatrix[0][i+1];
            l_out = _dimMatrix[1][i];
            h_out = _dimMatrix[1][i+1];
            break;       
        }
    }
    if (l_in < 0) {
        logger.log("Something went wrong.");
        return;
    }
    int pwmValue = map(brightness, l_in, h_in, l_out, h_out);
    analogWrite(_dimPin, pwmValue);
}
