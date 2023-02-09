#ifndef APP_CORE
#define APP_CORE

#include <memory>

struct WebServerConfig;
class AsyncWebServer;
using async_web_server_up = std::unique_ptr<AsyncWebServer>;

class AppCore
{
private:
    async_web_server_up m_server;
public:
    AppCore(const WebServerConfig &web_config);
    ~AppCore();
private:
    void setup_access_point(const WebServerConfig &config);
    void register_web_routes();
};

#endif
