// Pin wrapper
#pragma once

#include <Arduino.h>


namespace hal
{

enum class PinMode
{
    input,
    input_pullup,
    output,
};


class Pin
{
public:
    Pin(uint8_t pin_number, PinMode mode);
    Pin(const Pin&) = delete;
    Pin& operator=(const Pin&) = delete;

    void set();
    void reset();
    void toggle();
    bool is_set();
    bool is_reset();

private:
    uint8_t pin;
};


}


namespace hal
{

Pin::Pin(uint8_t pin_number, PinMode mode):
    pin{pin_number}
{
    switch (mode)
    {
    case PinMode::input:
        pinMode(pin, INPUT);
        break;

    case PinMode::input_pullup:
        pinMode(pin, INPUT_PULLUP);
        break;

    case PinMode::output:
        pinMode(pin, OUTPUT);
        break;
    }
}

void Pin::set()
{
    digitalWrite(pin, HIGH);
}

void Pin::reset()
{
    digitalWrite(pin, LOW);
}

void Pin::toggle()
{
    if (is_set())
    {
        reset();
    }
    else
    {
        set();
    }
}

bool Pin::is_set()
{
    return digitalRead(pin) == HIGH;
}

bool Pin::is_reset()
{
    return digitalRead(pin) == LOW;
}


}
