/**
 * File: can.cpp
 */

#include "can.hpp"

void can_begin(long baud)
{
    can.begin();
    can.setBaudRate(baud);
}

void can_read(CAN_message_t &msg)
{
    can.read(msg);
}
