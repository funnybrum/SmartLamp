#include "Lamp.h"

char buffer[4096];

WebServer::WebServer(NetworkSettings* networkSettings, Logger* logger)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/dim", std::bind(&WebServer::handle_dim, this));
    server->on("/auto", std::bind(&WebServer::handle_auto, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    bool save = false;

    wifi.parse_config_params(this, save);
    rtc.parseConfigParams(this);

    if (save) {
        settings.save();
    }

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    char rtc_settings[strlen_P(RTC_CONFIG_PAGE) + 32];

    wifi.get_config_page(network_settings);

    rtc.update();
    rtc.getConfigPage(rtc_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        rtc_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_dim() {
    uint16_t val = server->arg("dim").toInt();
    controller.setBrightness(val);
    logger->log("Dimming to %d", val);
    server->send(200, "text/html", "manual");
}

void WebServer::handle_auto() {
    controller.setAutoBrightness();
    server->send(200, "text/html", "auto");
}

void WebServer::handle_on() {
    controller.turnOn();
    server->send(200, "text/html", "on");
}

void WebServer::handle_off() {
    controller.turnOn();;
    server->send(200, "text/html", "off");
}