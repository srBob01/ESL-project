#ifndef CUSTOM_NVM_H
#define CUSTOM_NVM_H

#include "nrfx_nvmc.h"
#include "nrf_dfu_types.h"
#include "app_util.h"
#include "rgb.h"
#include "custom_leds.h"
#include "states.h"

void save_data_to_nvm(union RGB_OR_WORD* rgb_or_word);

void read_data_from_nvm(union RGB_OR_WORD* rgb_or_word);

#endif // CUSTOM_NVM_H