#ifndef STATES_H
#define STATES_H

#include <stdbool.h>

typedef struct{
    bool f;
} state_s;

typedef struct{
    bool f;
} state_v;

typedef struct{
    int i;
    bool is_new;
    bool is_first_ar;
} state_iteration;

enum state_led_rgb{
    HUE, 
    SATURATION, 
    VALUE, 
    NONE_RGB
};

enum state_led1{
    LOW, 
    QUICK,
    FULL,
    NONE_1
};

enum state_wait{
    WAIT_DOUBLE_CLICK, 
    WAIT_DURABLY_CLICK
};

#endif//STATES_H