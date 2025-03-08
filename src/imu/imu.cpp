/**
 * File: imu.cpp
 */

#include "imu.hpp"

void imu_init(uint8_t addr)
{
    Wire.begin(PB7, PB6);

    BMI160.begin(BMI160GenClass::I2C_MODE, Wire, addr, -1);
    BMI160.setGyroRange(250);
}

void imu_update(int &x, int &y, int &z)
{
    BMI160.readGyro(x, y, z);
}
