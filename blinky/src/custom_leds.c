#include "custom_leds.h"

void set_leds(){
    for(int i = 0; i < LEDS_NUMBER; ++i){
        nrf_gpio_cfg_output(leds[i]);
    }
}

void turn_on_led(int i){
    nrf_gpio_pin_write(leds[i], 0);
}

void turn_off_led(int i){
    nrf_gpio_pin_write(leds[i], 1);
}

void turn_off_all_leds(){
    for(int i = 0; i < LEDS_NUMBER; ++i){
        turn_off_led(i);
    }
}

bool is_gorenje(int i){
    return !nrf_gpio_pin_read(leds[i]);
}