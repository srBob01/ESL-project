#ifndef CHANGE_HSV_H
#define CHANGE_HSV_H

#include "hsv.h"
#include "rgb.h"
#include "states.h"

void change_hue(HSV *current_hsv);

void change_sat(HSV *current_hsv, enum state_direction* current_sat);

void change_val(HSV *current_hsv, enum state_direction* current_val);

#endif//CHANGE_HSV_H