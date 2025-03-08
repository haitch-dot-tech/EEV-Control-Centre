/**
 * File: can.cpp
 */

#pragma once

#include <Arduino.h>
#include <STM32_CAN.h>

#include "../config.h"

STM32_CAN can(CANX, CAN_PINS);

void can_begin(long baud);
void can_read(CAN_message_t &msg);
