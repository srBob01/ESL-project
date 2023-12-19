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
#include "nrfx_nvmc.h"

#include "nordic_common.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"
#include "nrf_log_backend_usb.h"
#include "app_usbd.h"
#include "app_usbd_serial_num.h"

#include "custom_leds.h"
#include "custom_button.h"
#include "custom_click.h"
#include "custom_blink_pwm_led.h"
#include "states.h"
#include "hsv.h"
#include "rgb.h"
#include "hsv_and_rgb.h"
#include "change_hsv.h"
#include "custom_nvm.h"

#endif