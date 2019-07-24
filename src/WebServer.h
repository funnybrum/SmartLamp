#pragma once

#include "Lamp.h"
#include "WebServerBase.h"
#include "WebPages.h"

class WebServer: public WebServerBase {
    public:
        WebServer(NetworkSettings* networkSettings, Logger* logger);
        void registerHandlers();
        void handle_root();
        void handle_settings();
        void handle_dim();
        void handle_on();
        void handle_off();
};
