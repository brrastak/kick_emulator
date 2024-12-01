#include "button.hpp"


namespace cmn
{

void Button::update()
{
    bool prev_state = m_is_pressed;
    
    if (is_active())
    {
        m_debounce_counter += 1;
    }
    else
    {
        m_debounce_counter -= 1;
    }

    if (m_debounce_counter >= m_debounce_interval)
    {
        m_debounce_counter = m_debounce_interval;
        m_is_pressed = true;
        m_press_duration += 1;
    }
    if (m_debounce_counter <= 1)
    {
        m_debounce_counter = 1;
        m_is_pressed = false;
    }
    
    if ( (m_is_pressed == true) && (prev_state == false) )
    {
        m_was_pressed = true;
        m_press_duration = 0;
    }
    if ( (m_is_pressed == false) && (prev_state == true) )
    {
        m_was_released = true;
    }
    
}

}

