#ifndef STATES_H
#define STATES_H

#include <stdbool.h>
#include <stdint.h>

enum state_direction{
    DIRECTION_FORWARD,
    DIRECTION_DOWNWARD
};

typedef struct{
    int i;
    bool is_new;
} state_iterator;

typedef struct{
    bool is_need_to_erase_page;
    uint32_t f_addr;
} state_save;

enum state_led_rgb{
    STATE_RGB_HUE, 
    STATE_RGB_SAT, 
    STATE_RGB_VAL, 
    STATE_RGB_NONE
};

enum state_led_condition{
    STATE_COND_LOW, 
    STATE_COND_QUICK,
    STATE_COND_FULL,
    STATE_COND_NONE
};

enum state_wait{
    WAIT_DOUBLE_CLICK, 
    WAIT_DURABLY_CLICK
};

#endif//STATES_H