#ifndef INC_H
#define INC_H

#include <stdbool.h>
#include <stdint.h>

#include "boards.h"
#include "nrf_delay.h"
#include "nrf_gpio.h"
#include "nrfx_systick.h"
#include "nrfx_gpiote.h"
#include "app_timer.h"
#include "nrfx_pwm.h"
#include "nrf_drv_clock.h"
#include "nrfx_glue.h"

#include "custom_leds.h"
#include "custom_button.h"
#include "custom_blink.h"
#include "custom_click.h"
#include "custom_blink_pwm_led.h"
#include "states.h"
#include "hsv.h"
#include "rgb.h"
#include "hsv_to_rgb.h"
#include "change_hsv.h"

#endif