#include <string>
#include <sstream>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"

#include "JSONBuilder.h"
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

std::string AppCore::get_controllers_data()
{
    JSONBuilder json(true);
    
    for (const std::pair<const std::uint8_t, rgb_controller_up> &pair : m_controllers)
    {
        RGBController *controller = pair.second.get();
        JSONBuilder color_values;
        color_values.
            addPair("id", pair.first)->
            addPair("red",controller->get_red_color())->
            addPair("green",controller->get_green_color())->
            addPair("blue",controller->get_blue_color());

        json.push(color_values.build());
    }

    return json.build();
}


void AppCore::connect_to_network(const WebServerConfig &config)
{
    WiFi.begin(config.network_ssid, config.network_password);

    unsigned long stamp = millis();
    while (
        WiFi.status() != WL_CONNECTED &&
        ( millis() - stamp) < config.NETWORK_CONNECTION_TIMEOUT
    )
    {
      delay(500);
      Serial.print(".");
    }

    if ( WiFi.status() == WL_CONNECTED ) {
      Serial.println("");
      Serial.print("Connected to: ");
      Serial.println(config.network_ssid);
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    } else {
      Serial.println("Failed to connect to network!");
    }
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

    m_server->on("/get", HTTP_GET, [core = this](AsyncWebServerRequest *request){
        std::string response = core->get_controllers_data();
        // std::string response = "{\"message\":\"Route is in development!\"}";
        Serial.println(response.c_str());
        request->send(200, "application/json", response.c_str());
    });

    m_server->on("/update", HTTP_GET, [](AsyncWebServerRequest *request){
        std::string response = "{\"message\":\"Route is in development!\"}";
        Serial.println(response.c_str());
        request->send(400, "application/json", response.c_str());
    });
}
