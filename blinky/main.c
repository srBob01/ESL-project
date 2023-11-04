#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define LONG_WAIT_TIME_MS 1000

#define CHEC_WAIT_TIME_MS 10

#define COUNT_CHECK LONG_WAIT_TIME_MS / CHEC_WAIT_TIME_MS

#define MY_LED_1 NRF_GPIO_PIN_MAP(0, 6)

#define MY_LED_2_R NRF_GPIO_PIN_MAP(0, 8)

#define MY_LED_2_G NRF_GPIO_PIN_MAP(1, 9)

#define MY_LED_2_B NRF_GPIO_PIN_MAP(0, 12)

#define MY_SW_1 NRF_GPIO_PIN_MAP(1, 6)

static const int number_blinks[LEDS_NUMBER] = {1, 1, 1, 1};/*device id 6610, last 1 for clarity.*/

static const uint32_t leds[LEDS_NUMBER] = {MY_LED_1, MY_LED_2_R, MY_LED_2_G, MY_LED_2_B};/*pins in order*/

void set_leds(){
    for(int i = 0;i < LEDS_NUMBER; ++i){
        nrf_gpio_cfg_output(leds[i]);
    }
}

void set_sw(){
    nrf_gpio_cfg_input(MY_SW_1, NRF_GPIO_PIN_PULLUP);
}

void turn_on_led(int i){
    nrf_gpio_pin_write(leds[i], 0);
}

void turn_off_led(int i){
    nrf_gpio_pin_write(leds[i], 1);
}

bool is_press(){
    return !nrf_gpio_pin_read(MY_SW_1);
}

bool is_not_press(){
    return !is_press();
}

void task(){
    int count_glow = 0;
    for(int i = 0; i < LEDS_NUMBER; ++i){/*проходимся по всем светодиодвм*/
        for(int j = 0; j < number_blinks[i]; ++j){/*сколько раз должна прогореть каждый светодиод*/
            if(is_not_press()){/*если кнопка не нажата*/
                --j;/*этот раз не считаем*/
            }
            else{/*если нажата*/
                turn_on_led(i);/*включаем светодиод*/
                int k = count_glow;/*по умлочанию 0, если было прервано нажатие, то другое*/
                for( ; k < COUNT_CHECK; ++k){/*проверяем каждые CHEC_WAIT_TIME_MS миллисекунд*/
                    if(is_not_press()){/*если кнопка стала отжата*/
                        count_glow = --k;/*запомиинаем где остановилась проверка*/
                        --j;/*попытку не засчитываем*/
                        break;/*выходим из цикла*/
                    }
                    nrf_delay_ms(CHEC_WAIT_TIME_MS);/*ждем время между проверкмаи*/
                }
                turn_off_led(i);/*выключаем светодиод*/
                if(k == COUNT_CHECK){/*если цикл был завершен*/
                    nrf_delay_ms(LONG_WAIT_TIME_MS);/*ждем время между попытками*/
                    count_glow = 0;/*устанавливаем в значение по усолчанию*/
                }
            }
        }
    }
}

/**
 * @brief Function for application main entry.
 */
int main(void){
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);
    bsp_board_leds_off();
    set_leds();
    set_sw();
    /* Toggle LEDs. */
    while (true){
        task();
    }
}

/**
 *@}
 **/
