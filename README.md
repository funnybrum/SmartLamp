# No WiFi

*!!!Work In Progress!!!*

ESP8258 based smart bulb. Smart becasue it can switch between cold and warm light based on the current date/time.

Features (v1):
 * Uses LM3414 for driving the LED with "analog" current regulation. The only switching frequency is ~1MHz even when the LED is being dimmed.
 * Monitor the LED temperature and adjust the brigthness in order to protect it in case of overheating.
 * RTC clock for fast brightnes adjustment. Less than 100ms to adjust the brightness based on the date/time when started.
 * WiFi interface for adjusting the datetime/dimming settings.

Features (v2):
 * Multiple cold/warm LEDs (driven by LM3414 in "analog" dimming mode) to adjust the light based on the daytime. 


## Building the project

The project uses a common set of tools that are availabe in another repo - https://github.com/funnybrum/esp8266-base. Clone the esp8266-base repo in the lib folder:

```
cd lib
git clone https://github.com/funnybrum/esp8266-base.git
```

There are also a few additional libraries requred:
 * OneWire
 * DallasTemperature
 * TODO - the RTC library

## PCB

The PCB is availabe at https://easyeda.com/funnybrum/smalrt-bulb. This is still work in progress and the current PCB almost works with v1. Almost because you need to switch the OneWire pin to GPIO13.

Required libraries: OneWire, DallasTemperature, RTClib (included).