#ifndef CUSTOM_BLINK_H
#define CUSTOM_BLINK_H

#include<stdint.h>
#include "nrfx_systick.h"
#include "custom_leds.h"

#define PERIOD_US 1000

void led_single_gorenje(uint32_t led, uint32_t duration_ms, volatile bool *enable);

#endif //CUSTOM_BLINK_H