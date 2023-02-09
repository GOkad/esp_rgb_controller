#ifndef APP_CORE
#define APP_CORE

#include <memory>
#include <unordered_map>

struct WebServerConfig;
class AsyncWebServer;
using async_web_server_up = std::unique_ptr<AsyncWebServer>;

class RGBController;
using rgb_controller_up = std::unique_ptr<RGBController>;

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
private:
    void init_controllers();
    void setup_access_point(const WebServerConfig &config);
    void register_web_routes();
};

#endif
