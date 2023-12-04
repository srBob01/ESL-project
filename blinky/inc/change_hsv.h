#ifndef CHANGE_HSV_H
#define CHANGE_HSV_H

#include "hsv.h"
#include "rgb.h"
#include "states.h"

void change_h(HSV *current_hsv);

void change_s(HSV *current_hsv, state_s* current_s);

void change_v(HSV *current_hsv, state_v* current_v);

#endif//CHANGE_HSV_H