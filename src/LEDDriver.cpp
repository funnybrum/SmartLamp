#include "Lamp.h"
#include "pwm.h"

#define PWM_PERIOD 5000


LEDDriver::LEDDriver(uint8_t dimPin, uint8_t enablePin) {
    _dimPin = dimPin;
    _enablePin = enablePin;
    _currentBrightness = -1;
    
    // Setup the on/off pin.
    pinMode(_enablePin, OUTPUT);
    off();

    // Setup the dim pin.
    pinMode(_dimPin, OUTPUT);
    // Refer to lib/pwm/README.md for the next few lines.
    uint32 io_info[1][3] = {
        {PERIPHS_IO_MUX_MTDI_U,  FUNC_GPIO12, 12}
    };
    uint32 pwm_duty_init[1] = {0};
    pwm_init(PWM_PERIOD, pwm_duty_init, 1, io_info);
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

void LEDDriver::setBrightness(int brightness) {
    if (_currentBrightness == brightness) {
        return;
    }
    _currentBrightness = brightness;

    if (brightness < 0) {
        brightness = 0;
    }
    if (brightness > 1000) {
        brightness = 1000;
    }
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
        logger.log("Something is wrong.");
        return;
    }
    int pwmValue = map(brightness, l_in, h_in, l_out, h_out);
    pwm_set_duty(pwmValue, 0);
    pwm_start();

    // Old approach with analogWrite.
    // analogWrite(0) -> full brightness
    // analogWrite(1023) -> minimum brightness
    // analogWrite(_dimPin, pwmValue);
}
