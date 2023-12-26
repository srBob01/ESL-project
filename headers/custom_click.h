#ifndef CUSTOM_CKICK_H
#define CUSTOM_CKICK_H

#include "app_timer.h"
#include "nrf_drv_clock.h"
#include "nrfx_glue.h"
#include "nrfx_gpiote.h"
#include "custom_button.h"
#include "custom_blink_pwm_led.h"
#include "custom_leds.h"
#include "states.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_backend_usb.h"
#include "app_usbd.h"
#include "app_usbd_serial_num.h"

#define DEBOUNCE_TIME_MS 10
#define DOUBLE_CLICK_TIME_MS 1000

void custom_double_click_timer_handler(void *context);
void custom_debounce_timer_handler(void *context);
void custom_debounce_timer_handler(void *context);
void custom_button_event_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action);
void timers_init(void);

#endif //CUSTOM_CKICK_H