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

// #include "nrf_log.h"
// #include "nrf_log_ctrl.h"
// #include "nrf_log_default_backends.h"
// #include "nrf_log_backend_usb.h"

#define DURATION_MS 1000  

void task(){
    for(int i = 0; i < LEDS_NUMBER; ){/*проходимся по всем светодиодвм*/
        if(led_many_blink(i, number_blinks[i], 1000, is_enable)){
            i++;
            nrf_delay_ms(DURATION_MS);
        }
    }
}

int main(void){
    // NRF_LOG_INIT(NULL);
    // NRF_LOG_DEFAULT_BACKENDS_INIT();

    set_leds();
    set_sw();
    turn_off_all_leds();

    lfclk_request();
    
    //инициализация systick для шим
    nrfx_systick_init();

    timers_init();

    while(true){
        task();
        // LOG_BACKEND_USB_PROCESS();
        // NRF_LOG_PROCESS();
    }
    
}