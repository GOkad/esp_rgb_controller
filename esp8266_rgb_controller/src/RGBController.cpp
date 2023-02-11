#include <Arduino.h>

#include "config/RGBControllerConfigs.h"
#include "RGBController.h"

RGBController::RGBController(const RGBControllerConfig &config):
    m_common_cathode{config.common_cathode},
    // Redundant info. Consider removing.
    m_id{config.id},
    m_red_pin{config.red_pin},
    m_green_pin{config.green_pin},
    m_blue_pin{config.blue_pin}
{
    pinMode(m_red_pin, OUTPUT);
    pinMode(m_green_pin, OUTPUT);
    pinMode(m_blue_pin, OUTPUT);

    std::uint8_t initial_value = m_common_cathode ? 0 : 255;
    set_color( initial_value,initial_value,initial_value);
}

void RGBController::set_color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
{
    analogWrite(m_red_pin, m_common_cathode ? red : (255 - red));
    analogWrite(m_green_pin, m_common_cathode ? green : (255 - green));
    analogWrite(m_blue_pin, m_common_cathode ? blue : (255 - blue));
}

std::uint8_t RGBController::get_red_color()
{
    return constrain(analogRead(m_red_pin), 0, 255);
}

std::uint8_t RGBController::get_green_color()
{
    return constrain(analogRead(m_green_pin), 0, 255);
}

std::uint8_t RGBController::get_blue_color()
{
    return constrain(analogRead(m_blue_pin), 0, 255);
}

// Useful for debugging
void RGBController::print_data()
{
    Serial.println("---[CONTROLLER_DATA]---");
    Serial.print("ID: ");
    Serial.println(m_id);

    Serial.println(
        m_common_cathode ? "COMMON CATHODE" : "COMMON ANODE"
    );
    
    Serial.print("red_pin: ");
    Serial.println(m_red_pin);
    Serial.print(" | ");
    Serial.print("val :");
    Serial.println(digitalRead(m_red_pin));

    Serial.print("green_pin: ");
    Serial.println(m_green_pin);
    Serial.print(" | ");
    Serial.print("val :");
    Serial.println(digitalRead(m_green_pin));

    Serial.print("blue_pin: ");
    Serial.print(m_blue_pin);
    Serial.print(" | ");
    Serial.print("val :");
    Serial.println(digitalRead(m_blue_pin));
    
    Serial.println("---[CONTROLLER_DATA]---");

}
