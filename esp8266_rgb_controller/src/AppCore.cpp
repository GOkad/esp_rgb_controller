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
        JSONBuilder controller_data;
        controller_data.
            addPair("id", pair.first)->
            addPair("red",controller->get_red_color())->
            addPair("green",controller->get_green_color())->
            addPair("blue",controller->get_blue_color());

        json.push(controller_data.build());
    }

    return json.build();
}

bool AppCore::set_color(std::uint8_t id, std::uint8_t red, std::uint8_t green, std::uint8_t blue)
{
    if (m_controllers.find(id) == m_controllers.end())
        return false;

    m_controllers.at(id)->set_color(red, green, blue);
    return true;
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

    if ( WiFi.status() != WL_CONNECTED ) {
        Serial.println("Failed to connect to network!");
        return;
    }

    Serial.println("");
    Serial.print("Connected to: ");
    Serial.println(config.network_ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
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

    m_server->on("/get-data", HTTP_GET, [core = this](AsyncWebServerRequest *request){
        std::string response = core->get_controllers_data();
        Serial.println(response.c_str());
        request->send(200, "application/json", response.c_str());
    });

    m_server->on("/update-color", HTTP_GET, [core = this](AsyncWebServerRequest *request){
        std::uint16_t response_code = 200;
        JSONBuilder json;
        std::vector<std::string> expected_payload = {"id","red","green","blue"};

        for ( std::string key : expected_payload )
        {
            if ( !request->hasParam(key.c_str()) )
            {
                json.addPair(key, "Missing value");
                response_code = 400;
            }
        }
        
        if (response_code == 400)
        {
            std::string response = json.build();
            Serial.println(response.c_str());

            request->send(response_code, "application/json", response.c_str());
        }

        std::uint8_t id = std::stoi(request->getParam("id")->value().c_str());
        std::uint8_t red = std::stoi(request->getParam("red")->value().c_str());
        std::uint8_t green = std::stoi(request->getParam("green")->value().c_str());
        std::uint8_t blue = std::stoi(request->getParam("blue")->value().c_str());

        bool has_color_updated = core->set_color(id, red, green, blue);

        if ( has_color_updated ) {
            json.addPair("message", "Updated sucessfully.");
        } else {
            std::string error_message = "Id not found: "+(id);
            json.addPair("message", error_message);
            response_code = 400;
        }

        std::string response = json.build();
        Serial.println(response.c_str());

        request->send(response_code, "application/json", response.c_str());
    });
}
