#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"

#include "config/WebServerConfig.h"
#include "AppCore.h"
#include "HMTLInterface.h"

AppCore::AppCore(const WebServerConfig &web_config):
    m_server{std::make_unique<AsyncWebServer>(80)}
{
    setup_access_point(web_config);
    register_web_routes();
    m_server->begin();
}

AppCore::~AppCore() = default;

void AppCore::setup_access_point(const WebServerConfig &config)
{
    WiFi.softAP(config.ssid, config.password);
    Serial.println(WiFi.softAPIP().toString());
}

void AppCore::register_web_routes()
{
    m_server->on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", index_html);
    });
}