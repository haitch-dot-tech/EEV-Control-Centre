/**
 * File: gps.cpp
 */

#include "gps.hpp"

TinyGPSPlus gps;

void gps_init(int baud)
{
    Serial1.begin(baud);
}

stat gps_update()
{
    if (Serial1.available())
    {
        gps.encode(Serial1.read());
    }
    else
    {
        return HAS_NONE;
    }
    
    int i = 0;

    i += gps.time.isUpdated() ? 1 : 0;
    i += gps.satellites.isUpdated() ? 1 : 0;
    i += gps.location.isUpdated() ? 1 : 0;
    i += gps.speed.isUpdated() ? 1 : 0;

    return (stat)i;
}

gpsd gps_data()
{
    struct gpsd d;

    d.hour = gps.time.hour();
    d.minute = gps.time.minute();
    d.second = gps.time.second();

    d.day = gps.date.day();
    d.month = gps.date.month();
    d.year = gps.date.year();

    d.lat = gps.location.lat();
    d.lon = gps.location.lng();

    d.course = gps.course.deg();

    d.alt = gps.altitude.meters();

    d.speed = gps.speed.kmph();

    d.sats = gps.satellites.value();

    return d;
}