#ifndef CUSTOM_BLINK_PWM_LEDRGB
#define CUSTOM_BLINK_PWM_LEDRGB

#include "nrfx_pwm.h"
#include "custom_leds.h"
#include "hsv_to_rgb.h"
#include "nrf_delay.h"
#include "change_hsv.h"

#define COUNT_STEP_1 50
#define COUNT_STEP_2 (COUNT_STEP_1 / 2)

#define SIZE_ARRAY_1 (COUNT_STEP_1 * 2)
#define SIZE_ARRAY_2 (COUNT_STEP_2 * 2)

#define LAST_I_ARRAY_1 (SIZE_ARRAY_1 - 1)
#define LAST_I_ARRAY_2 (SIZE_ARRAY_2 - 1)

void init_array_for_led_condition(int *arr, int size, int last_i);

void init_arrays_for_led_condition();

void update_i_led_condition();

void make_change_led_condition();

void make_change_ledRGB();

void pwm_individual_led_handler(nrfx_pwm_evt_type_t event_type);

void pwm_individual_init_led(void);

void pwm_play_led(void);

void update_hsv();

void pwm_change_mode_ledRGB(void);

void pwm_change_mode_led_condition(void);

#endif//CUSTOM_BLINK_PWM_LEDRGB