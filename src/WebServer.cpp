#include "Lamp.h"

char buffer[4096];

WebServer::WebServer(NetworkSettings* networkSettings, Logger* logger)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/dim", std::bind(&WebServer::handle_dim, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
}

void WebServer::handle_root() {
    systemCheck->registerWebCall();
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    systemCheck->registerWebCall();

    bool save = false;

    wifi.parse_config_params(this, save);

    if (save) {
        settings.save();
    }

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);


    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_dim() {
    uint16_t val = server->arg("dim").toInt();
    controller.setBrightness(val);
    logger->log("Dimming to %d", val);
    server->send(200, "text/html", "Done");
}

void WebServer::handle_on() {
    controller.setPower(true);
    server->send(200);
}

void WebServer::handle_off() {
    controller.setPower(false);
    server->send(200);
}