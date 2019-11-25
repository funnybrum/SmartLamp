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
    logger.begin();

    // If RX pin is LOW - enter debug mode.
    pinMode(3, INPUT);
    if (digitalRead(3) == LOW) {
        logger.log("Entering DEBUG mode.");
        webServer.begin();
        wifi.begin();
        wifi.connect();
        while (true) {
            wifi.loop();
            webServer.loop();
            delay(100);
        }
    }


    rtc.begin();
    ledDriver.begin();
    tempSensor.begin();
    controller.begin();

    Serial.begin(115200);
    settings.begin();
    webServer.begin();

    wifi.begin();
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

    delay(100);
}
