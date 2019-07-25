#include "Lamp.h"

void initSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);
}

SettingsData settingsData = SettingsData();
Logger logger = Logger();
Settings settings = Settings(&logger, (void*)(&settingsData), sizeof(SettingsData), initSettings);
WiFiManager wifi = WiFiManager(&logger, &settingsData.network);
WebServer webServer = WebServer(&settingsData.network, &logger);

LEDDriver ledDriver = LEDDriver(12, 14);
DS18B20 tempSensor = DS18B20(13);
Controller controller = Controller(
    &ledDriver,
    &tempSensor
);

Clock rtc = Clock();

void setup()
{ 
    Serial.begin(115200);
    while (! Serial) {
        delay(1);
    }
    logger.begin();
    settings.begin();
    wifi.begin();
    webServer.begin();

    rtc.begin();
    ledDriver.begin();
    tempSensor.begin();
    controller.begin();

    wifi.connect();
}

void loop() {
    logger.loop();
    settings.loop();
    wifi.loop();
    webServer.loop();

    rtc.loop();
    ledDriver.loop();
    tempSensor.loop();
    controller.loop();

    delay(1000);
}
