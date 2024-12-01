#include "counter.hpp"


namespace hal
{

Counter::Counter()
{
    enable();
}

bool Counter::is_timeout_passed(uint32_t timeout)
{
    if (m_disabled)
    {
        return false;
    }

    if (millis() - m_start_time >= timeout)
    {
        reset();
        return true;
    }
    else
    {
        return false;
    }
}

void Counter::disable()
{
    m_disabled = true;
}

void Counter::enable()
{
    m_disabled = false;
    reset();
}

void Counter::reset()
{
    m_start_time = millis();
}
}
