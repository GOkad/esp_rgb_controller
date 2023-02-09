#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"

#include "config/WebServerConfig.h"
#include "config/RGBControllerConfigs.h"
#include "AppCore.h"
#include "RGBController.h"
#include "HMTLInterface.h"

AppCore::AppCore(const WebServerConfig &web_config):
    m_server{std::make_unique<AsyncWebServer>(80)}
{
    init_controllers();
    setup_access_point(web_config);
    register_web_routes();
    m_server->begin();
}

AppCore::~AppCore() = default;

void AppCore::init_controllers()
{
    /**
     * Rethink this
     */
    RGBControllerConfig controller_1 = {false, 1,14,15,16};

    m_controllers.insert({
        controller_1.id,
        std::make_unique<RGBController>(controller_1)
    });

    RGBController *cont = m_controllers.at(controller_1.id).get();
    cont->print_data();
}

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

    m_server->on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        std::string response = "{\"message\":\"Route is in development!\"}";
        Serial.println(response.c_str());
        request->send(400, "application/json", response.c_str());
    });

    m_server->on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        std::string response = "{\"message\":\"Route is in development!\"}";
        Serial.println(response.c_str());
        request->send(400, "application/json", response.c_str());
    });
}
