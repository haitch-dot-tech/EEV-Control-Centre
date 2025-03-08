/**
 * File: imu.hpp
 */

#pragma once

#include <Arduino.h>
#include <Wire.h>
#include <BMI160Gen.h>

#include "../config.h"

void imu_init(uint8_t addr);
void imu_update(int &x, int &y, int &z);
