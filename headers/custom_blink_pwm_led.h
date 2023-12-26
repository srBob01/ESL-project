#ifndef CUSTOM_BLINK_PWM_LEDRGB
#define CUSTOM_BLINK_PWM_LEDRGB

#include "nrfx_pwm.h"
#include "custom_leds.h"
#include "hsv_and_rgb.h"
#include "nrf_delay.h"
#include "change_hsv.h"
#include "custom_nvm.h"
#include "custom_leds.h"

void init_array_for_led_condition(int *arr, int size, int last_i);

void init_arrays_for_led_condition();

void update_i_led_condition();

void make_change_led_condition();

void set_channel(union RGB_OR_WORD tmp_rgb_or_word);

void change_ledRGB(union RGB_OR_WORD tmp_rgb_or_word);

void make_change_ledRGB();

void pwm_individual_led_handler(nrfx_pwm_evt_type_t event_type);

void pwm_individual_init_led(void);

void pwm_play_led(void);

void update_hsv();

void pwm_change_mode_ledRGB(void);

void pwm_change_mode_led_condition(void);

#endif//CUSTOM_BLINK_PWM_LEDRGB