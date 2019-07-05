#pragma once

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266mDNS.h>

#include "user_interface.h"

#include "esp8266-base.h"

#include "DS18B20.h"

#define HTTP_PORT 80
#define HOSTNAME "blank"

struct SettingsData {
    NetworkSettings network;
};

extern Logger logger;
extern Settings settings;
extern SettingsData settingsData;
extern WiFiManager wifi;
extern SystemCheck systemCheck;
extern DS18B20 ds18b20;
