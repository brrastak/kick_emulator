#include "bsp.hpp"
#include "config.hpp"

#include <Arduino.h>


namespace bsp
{


Bsp& Bsp::take() {
    static Bsp instance {};

    return instance;
}

Bsp::Bsp() :
    m_led1 {bsp::led1_pin, hal::PinMode::output},
    m_led2 {bsp::led2_pin, hal::PinMode::output},
    m_mode_button_pin {bsp::mode_btn_pin, hal::PinMode::input_pullup},
    m_forth_button_pin {bsp::forth_btn_pin, hal::PinMode::input_pullup},
    m_back_button_pin {bsp::back_btn_pin, hal::PinMode::input_pullup},
    m_mode_button {m_mode_button_pin, cmn::BtnType::active_low},
    m_forth_button {m_forth_button_pin, cmn::BtnType::active_low},
    m_back_button {m_back_button_pin, cmn::BtnType::active_low}
{
    hal::Pin r_en {bsp::r_en_pin, hal::PinMode::output};
    r_en.set();
    hal::Pin l_en {bsp::l_en_pin, hal::PinMode::output};
    l_en.set();
    hal::Pin r_pwm {bsp::r_pwm_pin, hal::PinMode::output};
    r_pwm.reset();
    hal::Pin l_pwm {bsp::l_pwm_pin, hal::PinMode::output};
    l_pwm.reset();
}

void Bsp::update() {
    m_mode_button.update();
    m_forth_button.update();
    m_back_button.update();
}

hal::Pin& Bsp::led1() {
    return m_led1;
}
hal::Pin& Bsp::led2() {
    return m_led2;
}

cmn::Button& Bsp::mode_button() {
    return m_mode_button;
}

cmn::Button& Bsp::forth_button() {
    return m_forth_button;
}

cmn::Button& Bsp::back_button() {
    return m_back_button;
}

void Bsp::move_forth() {
    analogWrite(bsp::l_en_pin, 0);
    analogWrite(bsp::r_pwm_pin, bsp::pwm_value);
}

void Bsp::move_back() {
    analogWrite(bsp::r_en_pin, 0);
    analogWrite(bsp::l_pwm_pin, bsp::pwm_value);
}

void Bsp::stop_motor() {
    analogWrite(bsp::l_en_pin, 0);
    analogWrite(bsp::r_pwm_pin, 0);
}


}
