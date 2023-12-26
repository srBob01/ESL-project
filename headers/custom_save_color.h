#ifndef CUSTOM_SAVE_COLOR_H
#define CUSTOM_SAVE_COLOR_H
#include "custom_nvm.h"
#include "hsv_and_rgb.h"
#include "custom_blink_pwm_led.h"

union RGB_OR_WORD save_hsv(int hue, int sat, int val);

union RGB_OR_WORD save_rgb(int red, int green, int blue);

#endif