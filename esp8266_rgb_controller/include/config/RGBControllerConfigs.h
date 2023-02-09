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

/**
 * Rethink this
 */
RGBControllerConfig controller_1 = {false, 1,0,0,0};
RGBControllerConfig controller_2 = {false, 2,0,0,0};

#endif
