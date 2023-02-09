#ifndef RGB_CONTROLLERS_CONFIG
#define RGB_CONTROLLERS_CONFIG

#include <cstdint>

struct RGBControllerConfig
{
    bool         common_cathode;
    std::uint8_t id;
    std::uint8_t red_pin;
    std::uint8_t green_pin;
    std::uint8_t blue_pin;
};

#endif
