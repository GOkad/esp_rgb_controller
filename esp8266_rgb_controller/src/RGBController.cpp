#include <Arduino.h>

#include "config/RGBControllerConfigs.h"
#include "RGBController.h"

RGBController::RGBController(const RGBControllerConfig &config):
    m_common_cathode{config.common_cathode},
    m_id{config.id},
    m_red_pin{config.red_pin},
    m_green_pin{config.green_pin},
    m_blue_pin{config.blue_pin}
{
    pinMode(m_red_pin, OUTPUT);
    pinMode(m_green_pin, OUTPUT);
    pinMode(m_blue_pin, OUTPUT);
}

void RGBController::set_color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
{
    digitalWrite(m_red_pin, red);
    digitalWrite(m_green_pin, green);
    digitalWrite(m_blue_pin, blue);
}