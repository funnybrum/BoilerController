#include "Main.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger, systemCheck) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));

    server->on("/ufh/temp", std::bind(&WebServer::handle_ufh_temp, this));
    server->on("/ufh/on", std::bind(&WebServer::handle_ufh_on, this));
    server->on("/ufh/off", std::bind(&WebServer::handle_ufh_off, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);
    ufhTemp.parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);

    char ufh_temp_settings[strlen_P(TEMP_CONFIG_PAGE) + 64];
    ufhTemp.get_config_page(ufh_temp_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        ufh_temp_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_ufh_temp() {
    if (server->args() != 1
        || server->arg(0).length() != 0) {
        server->send(400, "text/plain", "try with /ufh/temp/?{25-45}");
        return;
    }

    int16_t temp = atoi(server->argName(0).c_str());
    if (temp > 100) {
        ufhTemp.setDuty(temp);
        server->send(200);
        // server->send(400, "text/plain", "try with /flapX?{0-100}");
        return;
    }
    
    ufhTemp.setTemp(temp);
    server->send(200);
}

void WebServer::handle_ufh_on() {
    ufhRelay.on();
    server->send(200);
}

void WebServer::handle_ufh_off() {
    ufhRelay.off();
    server->send(200);
}

void WebServer::handle_get() {
    sprintf_P(buffer,
              GET_JSON,
              ufhRelay.isOn()?"true":"false",
              ufhTemp.getTemp(),
              -1);
    server->send(200, "application/json", buffer);
}
