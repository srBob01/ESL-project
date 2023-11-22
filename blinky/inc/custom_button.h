#ifndef CUSTOM_BUTTON_H
#define  CUSTOM_BUTTON_H

#include "nrf_gpio.h"

#define MY_SW_1 NRF_GPIO_PIN_MAP(1, 6)

void set_sw();

bool is_press();

bool is_not_press();

#endif //CUSTOM_BUTTON_H