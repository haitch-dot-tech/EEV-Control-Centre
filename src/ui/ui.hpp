/**
 * File: ui.hpp
 */

#include <Arduino.h>
#include <lvgl.h>

#include "../config.h"

extern lv_obj_t *gpsScreen;
extern lv_obj_t *gpsTitle;
extern lv_obj_t *gpsTime;
extern lv_obj_t *gpsDate;
extern lv_obj_t *gpsLat;
extern lv_obj_t *gpsLon;
extern lv_obj_t *gpsAlt;
extern lv_obj_t *gpsSpeed;
extern lv_obj_t *gpsSats;

extern lv_obj_t *imuScreen;
extern lv_obj_t *imuTitle;
extern lv_obj_t *imuAx;
extern lv_obj_t *imuAy;
extern lv_obj_t *imuAz;
extern lv_obj_t *imuAxSlider;
extern lv_obj_t *imuAySlider;
extern lv_obj_t *imuAzSlider;
extern lv_obj_t *imuAxVal;
extern lv_obj_t *imuAyVal;
extern lv_obj_t *imuAzVal;
extern lv_obj_t *iumGx;
extern lv_obj_t *imuGy;
extern lv_obj_t *imuGz;
extern lv_obj_t *imuGxSlider;
extern lv_obj_t *imuGySlider;
extern lv_obj_t *imuGzSlider;
extern lv_obj_t *imuGxVal;
extern lv_obj_t *imuGyVal;
extern lv_obj_t *imuGzVal;

extern lv_obj_t *vescScreen;
extern lv_obj_t *vescTitle;
extern lv_obj_t *vescStatus;
extern lv_obj_t *vescVoltage;
extern lv_obj_t *vescRPM;
extern lv_obj_t *vescSpeed;
extern lv_obj_t *vescAh;
extern lv_obj_t *vescWh;

void ui_init();
void ui_update_label(lv_obj_t *obj, const char *fmt, ...);
void ui_update_slider(lv_obj_t *obj, int val);
void ui_switchScreen(lv_obj_t *screen);
void ui_handle();

void vescScreen_init();
void gpsScreen_init();
void imuScreen_init();
