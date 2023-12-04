#include "inc.h"

#define DURATION_MS 1000  

int main(void){

    set_leds();
    set_sw();
    turn_off_all_leds();

    // Play the sequence values by calling the play function
    lfclk_request();
    
    // //инициализация systick для шим
    nrfx_systick_init();

    timers_init();

    init_array1_for_led1();

    init_array2_for_led1();

    pwm_play_led();

    while(true){

    }
    
}