/**
 * File: helpers.hpp
 */

#include <Arduino.h>

void irq_attach(int pin, callback_function_t cb)
{
    pinMode(pin, INPUT_PULLDOWN);
    attachInterrupt(pin, cb, FALLING);
}