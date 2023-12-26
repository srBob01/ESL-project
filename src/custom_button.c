#include "custom_button.h"

void set_sw(){
    nrf_gpio_cfg_input(MY_SW_1, NRF_GPIO_PIN_PULLUP);
}

bool is_press(){
    return !nrf_gpio_pin_read(MY_SW_1);
}

bool is_not_press(){
    return nrf_gpio_pin_read(MY_SW_1);
}