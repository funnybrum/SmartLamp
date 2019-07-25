#pragma once

#include "Lamp.h"
#include "RTClib.h"

const char RTC_CONFIG_PAGE[] PROGMEM = R"=====(
<fieldset style='display: inline-block; width: 300px'>
<legend>Time settings</legend>
Date:<br>
<input type="text" size="4" name="year" value="%d">
<input type="text" size="2" name="month" value="%d">
<input type="text" size="2" name="day" value="%d"><br>
<small><em>year/month/day</em></small><br><br>
Time:<br>
<input type="text" size="2" name="hour" value="%d">
<input type="text" size="2" name="minute" value="%d"><br>
<small><em>hour/minute</em></small><br><br>
</fieldset>
)=====";


class Clock {
    public:
        void begin();
        void loop();

        uint16_t getYear();
        uint8_t getMonth();
        uint8_t getDay();
        uint8_t getHour();
        uint8_t getMinute();

        void getConfigPage(char* buffer);
        void parseConfigParams(WebServerBase* webServer);

    private:
        DateTime _now;
        RTC_DS1307 _rtc;
        unsigned long _lastRTCRead;
        
};
