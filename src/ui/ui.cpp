/**
 * File: ui.cpp
 */

#include "ui.hpp"

lv_obj_t *gpsScreen;
lv_obj_t *gpsTitle;
lv_obj_t *gpsTime;
lv_obj_t *gpsDate;
lv_obj_t *gpsLat;
lv_obj_t *gpsLon;
lv_obj_t *gpsAlt;
lv_obj_t *gpsSpeed;
lv_obj_t *gpsSats;

lv_obj_t *imuScreen;
lv_obj_t *imuTitle;
lv_obj_t *imuAx;
lv_obj_t *imuAy;
lv_obj_t *imuAz;
lv_obj_t *imuAxSlider;
lv_obj_t *imuAySlider;
lv_obj_t *imuAzSlider;
lv_obj_t *imuAxVal;
lv_obj_t *imuAyVal;
lv_obj_t *imuAzVal;
lv_obj_t *iumGx;
lv_obj_t *imuGy;
lv_obj_t *imuGz;
lv_obj_t *imuGxSlider;
lv_obj_t *imuGySlider;
lv_obj_t *imuGzSlider;
lv_obj_t *imuGxVal;
lv_obj_t *imuGyVal;
lv_obj_t *imuGzVal;

lv_obj_t *vescScreen;
lv_obj_t *vescTitle;
lv_obj_t *vescStatus;
lv_obj_t *vescVoltage;
lv_obj_t *vescRPM;
lv_obj_t *vescSpeed;
lv_obj_t *vescAh;
lv_obj_t *vescWh;

uint32_t draw_buf[(WIDTH * HEIGHT / 10 * (LV_COLOR_DEPTH / 8)) / 4];

static uint32_t lv_tick(void)
{
    return millis();
}

void ui_init()
{
    lv_init();
    lv_tick_set_cb(lv_tick);

    lv_display_t *disp = lv_tft_espi_create(WIDTH, HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_180);

    vescScreen_init();
    imuScreen_init();
    gpsScreen_init();

    lv_screen_load(vescScreen);
}

void ui_update_label(lv_obj_t *obj, const char *fmt, ...)
{
    char *c;
    va_list args;
    va_start(args, fmt);
    vsnprintf(c, sizeof(c), fmt, args);
    lv_label_set_text(obj, c);
    va_end(args);
}

void ui_update_slider(lv_obj_t *obj, int val)
{
    lv_slider_set_value(obj, val, LV_ANIM_OFF);
}

void ui_switchScreen(lv_obj_t *screen)
{
    lv_screen_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 0, false);
}

void ui_handle()
{
    lv_timer_handler();
}

void vescScreen_init()
{
    vescScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(vescScreen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(vescScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(vescScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescTitle = lv_label_create(vescScreen);
    lv_obj_set_width(vescTitle, LV_SIZE_CONTENT);
    lv_obj_set_height(vescTitle, LV_SIZE_CONTENT);
    lv_obj_set_align(vescTitle, LV_ALIGN_TOP_MID);
    lv_label_set_text(vescTitle, "VESC");
    lv_obj_set_style_text_font(vescTitle, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescStatus = lv_label_create(vescScreen);
    lv_obj_set_width(vescStatus, LV_SIZE_CONTENT);
    lv_obj_set_height(vescStatus, LV_SIZE_CONTENT);
    lv_obj_set_x(vescStatus, 0);
    lv_obj_set_y(vescStatus, 40);
    lv_label_set_text(vescStatus, "Status:%s%s");
    lv_obj_set_style_text_font(vescStatus, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescVoltage = lv_label_create(vescScreen);
    lv_obj_set_width(vescVoltage, LV_SIZE_CONTENT);
    lv_obj_set_height(vescVoltage, LV_SIZE_CONTENT);
    lv_obj_set_x(vescVoltage, 0);
    lv_obj_set_y(vescVoltage, 60);
    lv_label_set_text(vescVoltage, "Battery:%d.%02dV,%d.%02dA");
    lv_obj_set_style_text_font(vescVoltage, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescRPM = lv_label_create(vescScreen);
    lv_obj_set_width(vescRPM, LV_SIZE_CONTENT);
    lv_obj_set_height(vescRPM, LV_SIZE_CONTENT);
    lv_obj_set_x(vescRPM, 0);
    lv_obj_set_y(vescRPM, 80);
    lv_label_set_text(vescRPM, "%dRPM");
    lv_obj_set_style_text_font(vescRPM, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescSpeed = lv_label_create(vescScreen);
    lv_obj_set_width(vescSpeed, LV_SIZE_CONTENT);
    lv_obj_set_height(vescSpeed, LV_SIZE_CONTENT);
    lv_obj_set_x(vescSpeed, 0);
    lv_obj_set_y(vescSpeed, 100);
    lv_label_set_text(vescSpeed, "%d.%02dkm/h");
    lv_obj_set_style_text_font(vescSpeed, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescAh = lv_label_create(vescScreen);
    lv_obj_set_width(vescAh, LV_SIZE_CONTENT);
    lv_obj_set_height(vescAh, LV_SIZE_CONTENT);
    lv_obj_set_x(vescAh, 0);
    lv_obj_set_y(vescAh, 120);
    lv_label_set_text(vescAh, "%d.%02dAh");
    lv_obj_set_style_text_font(vescAh, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    vescWh = lv_label_create(vescScreen);
    lv_obj_set_width(vescWh, LV_SIZE_CONTENT);
    lv_obj_set_height(vescWh, LV_SIZE_CONTENT);
    lv_obj_set_x(vescWh, 0);
    lv_obj_set_y(vescWh, 140);
    lv_label_set_text(vescWh, "%d.%02dWh");
    lv_obj_set_style_text_font(vescWh, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void gpsScreen_init()
{
    gpsScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(gpsScreen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(gpsScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(gpsScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsTitle = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsTitle, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsTitle, LV_SIZE_CONTENT);
    lv_obj_set_align(gpsTitle, LV_ALIGN_TOP_MID);
    lv_label_set_text(gpsTitle, "GPS");
    lv_obj_set_style_text_font(gpsTitle, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsTime = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsTime, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsTime, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsTime, 0);
    lv_obj_set_y(gpsTime, 40);
    lv_label_set_text(gpsTime, "%02d:%02d:%02d");
    lv_obj_set_style_text_font(gpsTime, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsDate = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsDate, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsDate, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsDate, 0);
    lv_obj_set_y(gpsDate, 60);
    lv_label_set_text(gpsDate, "%02d/%02d/%04d");
    lv_obj_set_style_text_font(gpsDate, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsLat = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsLat, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsLat, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsLat, 0);
    lv_obj_set_y(gpsLat, 80);
    lv_label_set_text(gpsLat, "Lat:%d.%06d");
    lv_obj_set_style_text_font(gpsLat, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsLon = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsLon, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsLon, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsLon, 0);
    lv_obj_set_y(gpsLon, 100);
    lv_label_set_text(gpsLon, "Lon:%d.%06d");
    lv_obj_set_style_text_font(gpsLon, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsAlt = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsAlt, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsAlt, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsAlt, 0);
    lv_obj_set_y(gpsAlt, 120);
    lv_label_set_text(gpsAlt, "Alt:%dm");
    lv_obj_set_style_text_font(gpsAlt, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsSpeed = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsSpeed, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsSpeed, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsSpeed, 0);
    lv_obj_set_y(gpsSpeed, 140);
    lv_label_set_text(gpsSpeed, "Speed:%d.%02dkm/h");
    lv_obj_set_style_text_font(gpsSpeed, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    gpsSats = lv_label_create(gpsScreen);
    lv_obj_set_width(gpsSats, LV_SIZE_CONTENT);
    lv_obj_set_height(gpsSats, LV_SIZE_CONTENT);
    lv_obj_set_x(gpsSats, 0);
    lv_obj_set_y(gpsSats, 160);
    lv_label_set_text(gpsSats, "Satellites:%d");
    lv_obj_set_style_text_font(gpsSats, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void imuScreen_init()
{
    imuScreen = lv_obj_create(NULL);
    lv_obj_remove_flag(imuScreen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(imuScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    imuTitle = lv_label_create(imuScreen);
    lv_obj_set_width(imuTitle, LV_SIZE_CONTENT);
    lv_obj_set_height(imuTitle, LV_SIZE_CONTENT);
    lv_obj_set_align(imuTitle, LV_ALIGN_TOP_MID);
    lv_label_set_text(imuTitle, "IMU");
    lv_obj_set_style_text_font(imuTitle, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);

    imuAx = lv_label_create(imuScreen);
    lv_obj_set_width(imuAx, LV_SIZE_CONTENT);
    lv_obj_set_height(imuAx, LV_SIZE_CONTENT);
    lv_obj_set_x(imuAx, -200);
    lv_obj_set_y(imuAx, 56);
    lv_obj_set_align(imuAx, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(imuAx, "Ax");

    imuAy = lv_label_create(imuScreen);
    lv_obj_set_width(imuAy, LV_SIZE_CONTENT);
    lv_obj_set_height(imuAy, LV_SIZE_CONTENT);
    lv_obj_set_x(imuAy, -200);
    lv_obj_set_y(imuAy, 76);
    lv_obj_set_align(imuAy, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(imuAy, "Ay");

    imuAz = lv_label_create(imuScreen);
    lv_obj_set_width(imuAz, LV_SIZE_CONTENT);
    lv_obj_set_height(imuAz, LV_SIZE_CONTENT);
    lv_obj_set_x(imuAz, -200);
    lv_obj_set_y(imuAz, 96);
    lv_obj_set_align(imuAz, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(imuAz, "Az");

    imuAxSlider = lv_slider_create(imuScreen);
    lv_slider_set_range(imuAxSlider, -255, 255);
    lv_slider_set_value(imuAxSlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(imuAxSlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(imuAxSlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(imuAxSlider, 150);
    lv_obj_set_height(imuAxSlider, 10);
    lv_obj_set_x(imuAxSlider, 0);
    lv_obj_set_y(imuAxSlider, 60);
    lv_obj_set_align(imuAxSlider, LV_ALIGN_TOP_MID);
    lv_obj_set_style_bg_color(imuAxSlider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAxSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuAxSlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAxSlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuAxSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAxSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    imuAySlider = lv_slider_create(imuScreen);
    lv_slider_set_range(imuAySlider, -255, 255);
    lv_slider_set_value(imuAySlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(imuAySlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(imuAySlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(imuAySlider, 150);
    lv_obj_set_height(imuAySlider, 10);
    lv_obj_set_x(imuAySlider, 0);
    lv_obj_set_y(imuAySlider, 80);
    lv_obj_set_align(imuAySlider, LV_ALIGN_TOP_MID);
    lv_obj_set_style_bg_color(imuAySlider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAySlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuAySlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAySlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuAySlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAySlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    imuAzSlider = lv_slider_create(imuScreen);
    lv_slider_set_range(imuAzSlider, -255, 255);
    lv_slider_set_value(imuAzSlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(imuAzSlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(imuAzSlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(imuAzSlider, 150);
    lv_obj_set_height(imuAzSlider, 10);
    lv_obj_set_x(imuAzSlider, 0);
    lv_obj_set_y(imuAzSlider, 100);
    lv_obj_set_align(imuAzSlider, LV_ALIGN_TOP_MID);
    lv_obj_set_style_bg_color(imuAzSlider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAzSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuAzSlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAzSlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuAzSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuAzSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    imuAxVal = lv_label_create(imuScreen);
    lv_obj_set_width(imuAxVal, LV_SIZE_CONTENT);
    lv_obj_set_height(imuAxVal, LV_SIZE_CONTENT);
    lv_obj_set_x(imuAxVal, 200);
    lv_obj_set_y(imuAxVal, 56);
    lv_label_set_text(imuAxVal, "%d");

    imuAyVal = lv_label_create(imuScreen);
    lv_obj_set_width(imuAyVal, LV_SIZE_CONTENT);
    lv_obj_set_height(imuAyVal, LV_SIZE_CONTENT);
    lv_obj_set_x(imuAyVal, 200);
    lv_obj_set_y(imuAyVal, 76);
    lv_label_set_text(imuAyVal, "%d");

    imuAzVal = lv_label_create(imuScreen);
    lv_obj_set_width(imuAzVal, LV_SIZE_CONTENT);
    lv_obj_set_height(imuAzVal, LV_SIZE_CONTENT);
    lv_obj_set_x(imuAzVal, 200);
    lv_obj_set_y(imuAzVal, 96);
    lv_label_set_text(imuAzVal, "%d");

    iumGx = lv_label_create(imuScreen);
    lv_obj_set_width(iumGx, LV_SIZE_CONTENT);
    lv_obj_set_height(iumGx, LV_SIZE_CONTENT);
    lv_obj_set_x(iumGx, -200);
    lv_obj_set_y(iumGx, 136);
    lv_obj_set_align(iumGx, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(iumGx, "Gx");

    imuGy = lv_label_create(imuScreen);
    lv_obj_set_width(imuGy, LV_SIZE_CONTENT);
    lv_obj_set_height(imuGy, LV_SIZE_CONTENT);
    lv_obj_set_x(imuGy, -200);
    lv_obj_set_y(imuGy, 156);
    lv_obj_set_align(imuGy, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(imuGy, "Gy");

    imuGz = lv_label_create(imuScreen);
    lv_obj_set_width(imuGz, LV_SIZE_CONTENT);
    lv_obj_set_height(imuGz, LV_SIZE_CONTENT);
    lv_obj_set_x(imuGz, -200);
    lv_obj_set_y(imuGz, 176);
    lv_obj_set_align(imuGz, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(imuGz, "Gz");

    imuGxSlider = lv_slider_create(imuScreen);
    lv_slider_set_range(imuGxSlider, -255, 255);
    lv_slider_set_value(imuGxSlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(imuGxSlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(imuGxSlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(imuGxSlider, 150);
    lv_obj_set_height(imuGxSlider, 10);
    lv_obj_set_x(imuGxSlider, 0);
    lv_obj_set_y(imuGxSlider, 140);
    lv_obj_set_align(imuGxSlider, LV_ALIGN_TOP_MID);
    lv_obj_set_style_bg_color(imuGxSlider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGxSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuGxSlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGxSlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuGxSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGxSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    imuGySlider = lv_slider_create(imuScreen);
    lv_slider_set_range(imuGySlider, -255, 255);
    lv_slider_set_value(imuGySlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(imuGySlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(imuGySlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(imuGySlider, 150);
    lv_obj_set_height(imuGySlider, 10);
    lv_obj_set_x(imuGySlider, 0);
    lv_obj_set_y(imuGySlider, 160);
    lv_obj_set_align(imuGySlider, LV_ALIGN_TOP_MID);
    lv_obj_set_style_bg_color(imuGySlider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGySlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuGySlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGySlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuGySlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGySlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    imuGzSlider = lv_slider_create(imuScreen);
    lv_slider_set_range(imuGzSlider, -255, 255);
    lv_slider_set_value(imuGzSlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(imuGzSlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(imuGzSlider, 0, LV_ANIM_OFF);
    lv_obj_set_width(imuGzSlider, 150);
    lv_obj_set_height(imuGzSlider, 10);
    lv_obj_set_x(imuGzSlider, 0);
    lv_obj_set_y(imuGzSlider, 180);
    lv_obj_set_align(imuGzSlider, LV_ALIGN_TOP_MID);
    lv_obj_set_style_bg_color(imuGzSlider, lv_color_hex(0x202020), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGzSlider, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuGzSlider, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGzSlider, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(imuGzSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(imuGzSlider, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

    imuGxVal = lv_label_create(imuScreen);
    lv_obj_set_width(imuGxVal, LV_SIZE_CONTENT);
    lv_obj_set_height(imuGxVal, LV_SIZE_CONTENT);
    lv_obj_set_x(imuGxVal, 200);
    lv_obj_set_y(imuGxVal, 136);
    lv_label_set_text(imuGxVal, "%d");

    imuGyVal = lv_label_create(imuScreen);
    lv_obj_set_width(imuGyVal, LV_SIZE_CONTENT);
    lv_obj_set_height(imuGyVal, LV_SIZE_CONTENT);
    lv_obj_set_x(imuGyVal, 200);
    lv_obj_set_y(imuGyVal, 156);
    lv_label_set_text(imuGyVal, "%d");

    imuGzVal = lv_label_create(imuScreen);
    lv_obj_set_width(imuGzVal, LV_SIZE_CONTENT);
    lv_obj_set_height(imuGzVal, LV_SIZE_CONTENT);
    lv_obj_set_x(imuGzVal, 200);
    lv_obj_set_y(imuGzVal, 176);
    lv_label_set_text(imuGzVal, "%d");
}
