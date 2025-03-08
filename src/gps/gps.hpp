/**
 * File: gps.hpp
 */

#include <Arduino.h>
#include <TinyGPS++.h>

#include "../config.h"

struct gpsd
{
    int hour; int minute; int second;
    int day; int month; int year;
    int lat; int lon;
    int course;
    int alt;
    int speed;
    int sats;
};

enum stat
{
    HAS_NONE,
    HAS_TIME,
    HAS_SATS,
    HAS_LOCATION,
    HAS_SPEED
};

void gps_init(int baud);
stat gps_update();
gpsd gps_data();