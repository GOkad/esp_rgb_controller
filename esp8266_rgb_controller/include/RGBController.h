#ifndef RGB_CONTROLLER
#define RGB_CONTROLLER

#include <cstdint>

struct RGBControllerConfig;

class RGBController
{
private:
    bool m_common_cathode;
    std::uint8_t m_id;
    std::uint8_t m_red_pin;
    std::uint8_t m_green_pin;
    std::uint8_t m_blue_pin;
public:
    RGBController(const RGBControllerConfig &config);
    void set_color(std::uint8_t red, std::uint8_t green, std::uint8_t blue);
};

#endif
