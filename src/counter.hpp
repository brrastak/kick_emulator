// Timeout counter
#pragma once

#include <Arduino.h>


namespace hal
{

/// Gets current time and compares it with the specified timeout
class Counter
{
public:
    Counter();

    /// @brief Check if specified timeout has passed; in that case reset counting
    /// @param timeout in milliseconds
    /// @return True if timeout passed; False otherwise
    bool is_timeout_passed(uint32_t timeout_ms);

    /// @brief Checking for timeout passed always returns False
    void disable();

    /// @brief Reset counter and start counting
    void enable();

    /// @brief Start counting ticks from the current tick number
    void reset();

private:
    Counter(const Counter&) = delete;

    uint32_t m_start_time;
    /// @brief Is inactiv and always returns False
    bool m_disabled{false};
};

}
