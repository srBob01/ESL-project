#ifndef CUSTOM_BLINK_PWM_LEDRGB
#define CUSTOM_BLINK_PWM_LEDRGB

#include "nrfx_pwm.h"
#include "custom_leds.h"
#include "hsv_to_rgb.h"
#include "nrf_delay.h"
#include "change_hsv.h"

#define COUNT_STEP_1 50
#define COUNT_STEP_2 25

void init_array1_for_led1();

void init_array2_for_led1();

void update_i_led1();

void make_change_led1();

void make_change_ledRGB();

void pwm_individual_led_handler(nrfx_pwm_evt_type_t event_type);

void pwm_individual_init_led(void);

void pwm_play_led(void);

void update_hsv();

void pwm_change_mode_ledRGB(void);

void pwm_change_mode_led1(void);

#endif//CUSTOM_BLINK_PWM_LEDRGB