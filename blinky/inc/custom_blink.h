#ifndef CUSTOM_BLINK_H
#define CUSTOM_BLINK_H

#include<stdint.h>
#include "nrfx_systick.h"
#include "custom_leds.h"

#define PERIOD_US 1000

bool led_single_blink(uint32_t led, uint32_t duration_ms, bool enable);

bool led_many_blink(uint32_t led, uint32_t num, uint32_t duration_ms, bool enable);

#endif //CUSTOM_BLINK_H