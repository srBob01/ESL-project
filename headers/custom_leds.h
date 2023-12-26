#ifndef CUSTOM_LEDS_H
#define CUSTOM_LEDS_H

#include "nrf_gpio.h"
#include "boards.h"

#define MY_LED_1 NRF_GPIO_PIN_MAP(0, 6)

#define MY_LED_2_R NRF_GPIO_PIN_MAP(0, 8)

#define MY_LED_2_G NRF_GPIO_PIN_MAP(1, 9)

#define MY_LED_2_B NRF_GPIO_PIN_MAP(0, 12)

#define LEDS_NUMBER 4

static const uint32_t leds[LEDS_NUMBER] = {MY_LED_1, MY_LED_2_R, MY_LED_2_G, MY_LED_2_B};/*pins in order*/

static const int number_blinks[LEDS_NUMBER] = {2, 2, 2, 2};/*device id 6610*/

void set_leds();

void turn_on_led(int i);

void turn_off_led(int i);

void turn_off_all_leds();

bool is_gorenje(int i);

#endif //CUSTOM_LEDS_H