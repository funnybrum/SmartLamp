#include "Lamp.h"

void initSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
}

SettingsData settingsData = SettingsData();
Logger logger = Logger();
Settings settings = Settings(&logger, (void*)(&settingsData), sizeof(SettingsData), initSettings);
WiFiManager wifi = WiFiManager(&logger, &settingsData.network);
SystemCheck systemCheck = SystemCheck(&logger);
WebServer webServer = WebServer(&settingsData.network, &logger, &systemCheck);
DS18B20 ds18b20 = DS18B20(13);

void setup()
{ 
    Serial.begin(115200);
    while (! Serial) {
        delay(1);
    }
    settings.begin();
    wifi.begin();
    webServer.begin();
    // systemCheck.begin();

    pinMode(14, OUTPUT);
    digitalWrite(14, HIGH);

    pinMode(12, OUTPUT);
    analogWrite(12, 500);

    wifi.connect();
}

int count = 0;

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    // systemCheck.loop();
    delay(1000);
}
