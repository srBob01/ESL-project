#include "inc.h"

void logs_init()
{
    ret_code_t ret = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(ret);

    NRF_LOG_DEFAULT_BACKENDS_INIT();
}

int main(void){

    logs_init();

    set_leds();
    set_sw();
    turn_off_all_leds();
    
    // //инициализация systick для шим
    nrfx_systick_init();

    timers_init();

    init_arrays_for_led_condition();

    pwm_play_led();

    NRF_LOG_INFO("Starting up the test project with USB logging");

    while(true){
        LOG_BACKEND_USB_PROCESS();
        NRF_LOG_PROCESS();
    }
    
}