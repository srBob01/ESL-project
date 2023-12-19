#ifndef HSV_TO_RGB_H
#define HSV_TO_RGB_H

#include "hsv.h"
#include "rgb.h"
#include "math.h"

void HSVToRGB(const HSV* current_hsv, RGB* current_rgb);

void RGBToHSV(const RGB* current_rgb, HSV* result_hsv);

#endif//HSV_TO_RGB_H
