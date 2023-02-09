#ifndef WEB_SERVER_CONFIG
#define WEB_SERVER_CONFIG

struct WebServerConfig
{
    /**
     * Soft Access Point credentials
     */
    static inline const char* SSID             = "RGB_CONTROLLER";
    static inline const char* PASSWORD         = "";
    
    /**
     * Network credentials
     */
    static inline const char* NETWORK_SSID     = "YourNetworkSSID";
    static inline const char* NETWORK_PASSWORD = "YourPassword";

    const char* ssid{SSID};
    const char* password{PASSWORD};
    const char* network_ssid{NETWORK_SSID};
    const char* network_password{NETWORK_PASSWORD};
};

#endif