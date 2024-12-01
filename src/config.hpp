#pragma once

#include <Arduino.h>


namespace config
{

// Timings in ms
constexpr uint16_t moving_time = 1000;
constexpr uint16_t waiting_time = 5000;

}


// HW config
namespace bsp
{

// On-board LEDs
constexpr uint8_t led1_pin = 13;
constexpr uint8_t led2_pin = 12;

// Button pins
constexpr uint8_t mode_btn_pin = 11;
constexpr uint8_t forth_btn_pin = 3;
constexpr uint8_t back_btn_pin = 2;

// HW-039 motor driver control pins
constexpr uint8_t r_pwm_pin = 6;
constexpr uint8_t l_pwm_pin = 5;
constexpr uint8_t r_en_pin = 7;
constexpr uint8_t l_en_pin = 4;

// PWM value for motor control pins
constexpr uint8_t pwm_value = 0xFF;

}
