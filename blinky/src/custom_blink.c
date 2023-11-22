#include "custom_blink.h"
void led_single_gorenje(uint32_t led, uint32_t duration_ms, volatile bool *enable){
    int32_t count_periods = duration_ms * 1000  / PERIOD_US; //кол-во периодов в времени горения

    int32_t duty_cycle_step_us = duration_ms / count_periods; //шаг для прибавления, то есть на каждом следующем шаге
                                                        //увеличиваем текущее значение скважности на это значение

    int32_t current_duty_cycle_us = 0;//текущее значение скважности
                                        //в начале 0, max = PERIOD_US, когда наступил max значит надо идти обратно так как достигли 100%
    
    int32_t time_to_wait_us = 0;//часть без горения

    nrfx_systick_state_t state = { .time = 0 };

    bool is_forward_direction = true;//1 - возрастание, 0 - убывание

    bool is_gorenje = false;//1 - нужно гореть, 0 - не нужно гореть

    nrfx_systick_get(&state);//засекаем
    
    while(current_duty_cycle_us >= 0){//пока скважность положительная
        if(nrfx_systick_test(&state, time_to_wait_us)){//если прошло заданное время
            if(is_gorenje){//если нужно гореть(до этого не горела)
                turn_on_led(led);//включаем
                time_to_wait_us = current_duty_cycle_us;//время для ожидания это сколько должна гореть
                is_gorenje = false;//теперь не надо гореть
            }  
            else{//если не нужно гореть(до этого горела)
                turn_off_led(led);//выключаем светодиод
                time_to_wait_us = PERIOD_US - current_duty_cycle_us;//время это ожидание до следующего периода
                if(*enable){//если нужно менять состояние лампы
                    //в зависимости от напрвления прибавляем или убавляем шаг
                    current_duty_cycle_us += is_forward_direction ? duty_cycle_step_us : -duty_cycle_step_us;
                    if(current_duty_cycle_us >= PERIOD_US){//если возрастание и достигли максимальной скважности
                        is_forward_direction = false;//значит надо сменить направление
                    }
                }
                is_gorenje = true;//теперь надо гореть
            }
            nrfx_systick_get(&state);//засекаем
        }
    }

}