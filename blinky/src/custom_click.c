#include "custom_click.h"
#include "custom_button.h"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

volatile bool is_enable = true;
static volatile int count_click = 0;

APP_TIMER_DEF(double_click_timer);
APP_TIMER_DEF(debounce_timer);  

void custom_debounce_timer_handler(void *context){
    if(!nrfx_gpiote_in_is_set(MY_SW_1)) {//если на момент прохождения времени кнопка была нажата
        count_click++;
    }
    if(count_click == 2){
        is_enable = !is_enable;
        count_click = 0;
        NRF_LOG_INFO("%s", is_enable ? "Run" : "Stop");
    }
}

void custom_double_click_timer_handler(void *context){
    count_click = 0;
}

void custom_button_event_handler(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action){
    APP_ERROR_CHECK(app_timer_stop(debounce_timer));
    //заводим таймер на дребезжание, если это последний скачок, то stop не сработает
    APP_ERROR_CHECK(app_timer_start(debounce_timer, APP_TIMER_TICKS(DEBOUNCE_TIME_MS), NULL));
    APP_ERROR_CHECK(app_timer_start(double_click_timer, APP_TIMER_TICKS(DOUBLE_CLICK_TIME_MS), NULL));
}

void lfclk_request(void)
{
    APP_ERROR_CHECK(nrf_drv_clock_init());
    nrf_drv_clock_lfclk_request(NULL);

    while (!nrf_drv_clock_lfclk_is_running())
    {
        /* Just waiting until the lf clock starts up */
    }
}

void timers_init(void){
    ret_code_t err_code = 0;
    //инициализация модуля gpiote
    err_code = nrfx_gpiote_init();
    APP_ERROR_CHECK(err_code);

    //инициализация rtc для обработки кликов и борьбы с дребезжанием
    err_code = app_timer_init();
    APP_ERROR_CHECK(err_code);

    //создание таймера для обработки двойного клика(ограничение на время второго клика)
    err_code = app_timer_create(&double_click_timer, APP_TIMER_MODE_SINGLE_SHOT, custom_double_click_timer_handler);
    APP_ERROR_CHECK(err_code);

    //создание таймера для debounce
    err_code = app_timer_create(&debounce_timer, APP_TIMER_MODE_SINGLE_SHOT, custom_debounce_timer_handler);
    APP_ERROR_CHECK(err_code);

    nrfx_gpiote_in_config_t my_config = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    my_config.pull = NRF_GPIO_PIN_PULLUP;
    err_code = nrfx_gpiote_in_init(MY_SW_1, &my_config, custom_button_event_handler);
    APP_ERROR_CHECK(err_code);
    nrfx_gpiote_in_event_enable(MY_SW_1, true);
}