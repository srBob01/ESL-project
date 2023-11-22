#include <stdint.h>

#include "sdk_config.h"
#include "nrf_delay.h"
#include "nrfx_gpiote.h"
#include "nrfx_systick.h"
#include "app_timer.h"
#include "drv_rtc.h"

#include "custom_button.h"
#include "custom_leds.h"
#include "custom_blink.h"

#define DURATION_MS 1000
#define DEBOUNCE_TIME_MS 10
#define DOUBLE_CLICK_TIME_MS 500

static volatile bool is_enable = true;
static volatile int count_click = 0;

APP_TIMER_DEF(double_click_timer);
APP_TIMER_DEF(debounce_timer);    

void custom_debounce_timer_handler(void *context){
    count_click++;
    if(count_click == 1){
        //заводим таймер на ограничение по времени для второго нажатия
        APP_ERROR_CHECK(app_timer_start(double_click_timer, APP_TIMER_TICKS(DOUBLE_CLICK_TIME_MS), NULL));
    }
    else{
        APP_ERROR_CHECK(app_timer_stop(double_click_timer));
        is_enable = !is_enable;
        count_click = 0;
    }
}

void custom_double_click_timer_handler(void *context){
    count_click = 0;
}

void custom_button_event_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action){
    APP_ERROR_CHECK(app_timer_stop(debounce_timer));
    //заводим таймер на дребезжание, если это последний скачок, то stop не сработает
    APP_ERROR_CHECK(app_timer_start(debounce_timer, APP_TIMER_TICKS(DEBOUNCE_TIME_MS), NULL));
}

void task(){
    for(int i = 0; i < LEDS_NUMBER; ++i){/*проходимся по всем светодиодвм*/
        for(int j = 0; j < number_blinks[i]; ++j){/*сколько раз должен прогореть каждый светодиод*/
            led_single_gorenje(i, DURATION_MS, &is_enable);
            nrf_delay_ms(DURATION_MS);
        }
    }
}

int main(void){
    set_leds();
    set_sw();
    turn_off_all_leds();
    ret_code_t err_code = 0;
    //инициализация systick для шим
    nrfx_systick_init();

    //инициализация rtc для обработки кликов и борьбы с дребезжанием
    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    //создание таймера для обработки двойного клика(ограничение на время второго клика)
    err_code = app_timer_create(&double_click_timer, APP_TIMER_MODE_SINGLE_SHOT, custom_double_click_timer_handler);
    APP_ERROR_CHECK(err_code);

    //создание таймера для debounce
    err_code = app_timer_create(&debounce_timer, APP_TIMER_MODE_SINGLE_SHOT, custom_debounce_timer_handler);
    APP_ERROR_CHECK(err_code);

    //инициализация модуля gpiote
    err_code = nrfx_gpiote_init();
    APP_ERROR_CHECK(err_code);

    nrfx_gpiote_in_config_t my_config = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    my_config.pull = NRF_GPIO_PIN_PULLUP;
    err_code = nrfx_gpiote_in_init(MY_SW_1, &my_config, custom_button_event_handler);
    APP_ERROR_CHECK(err_code);

    nrfx_gpiote_in_event_enable(MY_SW_1, true);

    while(true){
        task();
    }
    
}