#ifndef APP_CORE
#define APP_CORE

#include <memory>
#include <unordered_map>

struct WebServerConfig;
class AsyncWebServer;
using async_web_server_up = std::unique_ptr<AsyncWebServer>;
class AsyncWebServerRequest;

class RGBController;
using rgb_controller_up = std::unique_ptr<RGBController>;

class JSONBuilder;

class AppCore
{
private:
    async_web_server_up m_server;
    std::unordered_map<std::uint8_t, rgb_controller_up> m_controllers;
public:
    AppCore(const WebServerConfig &web_config);
    ~AppCore();
    static void connect_to_network(const WebServerConfig &config);
    std::string get_controllers_data();
    bool set_color(std::uint8_t id, std::uint8_t red, std::uint8_t green, std::uint8_t blue);
private:
    void init_controllers();
    void setup_access_point(const WebServerConfig &config);
    void register_web_routes();
};

#endif
