// Board support package
#pragma once


#include "button.hpp"
#include "pin.hpp"


namespace bsp
{

class Bsp
{
public:
    /// @return BSP instance
    static Bsp& take();

    /// @brief Update states of all the buttons. To be called once a 1ms
    void update();
    hal::Pin& led1();
    hal::Pin& led2();
    /// @brief Button to switch modes
    cmn::Button& mode_button();
    /// @brief Button to control rotation direction
    cmn::Button& forth_button();
    /// @brief Button to control rotation direction
    cmn::Button& back_button();
    /// @brief Control motor connected to reflector
    void move_forth();
    /// @brief Control motor connected to reflector
    void move_back();
    /// @brief Control motor connected to reflector
    void stop_motor();

private:
    Bsp();
    Bsp(const Bsp&) = delete;

    hal::Pin m_led1;
    hal::Pin m_led2;
    hal::Pin m_mode_button_pin;
    hal::Pin m_forth_button_pin;
    hal::Pin m_back_button_pin;
    cmn::Button m_mode_button;
    cmn::Button m_forth_button;
    cmn::Button m_back_button;
};

}


