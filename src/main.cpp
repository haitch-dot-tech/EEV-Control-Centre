/**
 * File: main.cpp
 */

#include <Arduino.h>
#include "ui/ui.hpp"
// #include "imu/imu.hpp"
// #include "gps/gps.hpp"

#include "config.h"
#include "helpers.hpp"

// int x;
// int y;
// int z;

int currentScreen = 1, numScreens = 3;

// gpsd d;

void btn_cb()
{
    digitalWrite(PB2, HIGH);
    currentScreen++;
    switch (currentScreen)
    {
        case 2:
            ui_switchScreen(imuScreen);
            break;
        case 3:
            ui_switchScreen(gpsScreen);
            break;
        case 4:
            ui_switchScreen(vescScreen);
            currentScreen = 1;
            break;
        default:
            ui_switchScreen(vescScreen);
            break;
    }
    digitalWrite(PB2, LOW);
}

void setup()
{
    ui_init();
    // imu_init(0x69);
    // gps_init(9600);

    pinMode(PB2, OUTPUT);

    irq_attach(PC13, btn_cb);
}

void loop()
{
    // imu_update(x, y, z);
    // if (gps_update() == HAS_SPEED)
    //     d = gps_data();

    // ui_update_label(imuGxVal, "X: %d", x);
    // ui_update_label(imuGyVal, "Y: %d", y);
    // ui_update_label(imuGzVal, "Z: %d", z);

    ui_handle();
}
