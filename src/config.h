/**
 * File: config.h
 */

#include <Arduino.h>

/* Display pins */
#define DISP_RST  PA2
#define DISP_DC   PA3
#define DISP_CS   PA4
#define DISP_CLK  PA5
#define DISP_MISO PA6
#define DISP_MOSI PA7

/* Display config */
#define WIDTH 240
#define HEIGHT 320

/* SD card */
#define SD_D0 PC8
#define SD_D1 PC9
#define SD_D2 PC10
#define SD_D3 PC11
#define SD_CLK PC12
#define SD_CMD PD2

/* CAN pins */
#define CANX    CAN1
#define CAN_PINS DEF