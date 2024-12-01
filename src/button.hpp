// Button class
// Takes button pin as parameter
// Makes debouncing 
// Detects current button state, press/release events, press duration
#pragma once

#include "pin.hpp"


namespace cmn
{

enum class BtnType
{
    active_low,
    active_high
};

class Button
{
public:
    // Button goes to pressed state after pin is pressed summary time in ms of debounce_interval
    Button(hal::Pin& pin, BtnType btn_type, uint8_t debounce_interval = 20)
        : m_pin{pin}
        , m_btn_type{btn_type}
        , m_debounce_interval{debounce_interval}
        , m_debounce_counter{1}
        , m_press_duration{0}
        , m_is_pressed{false}
        , m_was_pressed{false}
        , m_was_released{false}
    {} 

    // should be called every 1ms
    void update();
    
    bool is_pressed()
    {
        return m_is_pressed;
    }
    bool was_pressed()
    {
        return return_and_reset(m_was_pressed);
    }
    bool was_released()
    {
        return return_and_reset(m_was_released);
    }
    uint16_t get_press_duration()
    {
        return m_press_duration;
    }

private:
    bool return_and_reset(bool& flag)
    {
        if (flag)
        {
            flag = false;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_active()
    {
        bool active_state;

        switch (m_btn_type)
        {
        case BtnType::active_high:
            active_state = true;
            break;

        case BtnType::active_low:
            active_state = false;
            break;
        }

        return (m_pin.is_set() == active_state);
    }

    hal::Pin& m_pin;
    const BtnType m_btn_type;

    const uint8_t m_debounce_interval;
    uint8_t m_debounce_counter;
    uint16_t m_press_duration;
    
    bool m_is_pressed;
    bool m_was_pressed;
    bool m_was_released;
};


}
