#include "custom_blink.h"
bool led_single_blink(uint32_t led, uint32_t duration_ms, bool enable){

    int count_periods = (duration_ms) * 1000  / PERIOD_US; //кол-во периодов в времени горения

    int duty_cycle_step_us = duration_ms / count_periods; //шаг для прибавления, то есть на каждом следующем шаге
                                                        //увеличиваем текущее значение скважности на это значение

    static int32_t current_duty_cycle_us = 0;//текущее значение скважности
                                        //в начале 0, max = PERIOD_US, когда наступил max значит надо идти обратно так как достигли 100%
    
    static int32_t time_to_wait_us = 0;//часть без горения

    static nrfx_systick_state_t state = { .time = 0 };

    static bool is_forward_direction = true;//1 - возрастание, 0 - убывание

    static bool is_blink = false;//1 - нужно гореть, 0 - не нужно гореть

    static bool first_get = true;

    if(first_get){
        nrfx_systick_get(&state);//засекаем
        first_get = false;
    }
    
    if(current_duty_cycle_us >= 0){//пока скважность положительная
        if(nrfx_systick_test(&state, time_to_wait_us)){//если прошло заданное время

            if(is_blink){//если нужно гореть(до этого не горела)
                turn_on_led(led);//включаем
                time_to_wait_us = current_duty_cycle_us;//время для ожидания это сколько должна гореть
                is_blink = false;//теперь не надо гореть
            }  
            else{//если не нужно гореть(до этого горела)
                turn_off_led(led);//выключаем светодиод
                time_to_wait_us = PERIOD_US - current_duty_cycle_us;//время это ожидание до следующего периода
                if(enable){//если нужно менять состояние лампы
                    //в зависимости от напрвления прибавляем или убавляем шаг
                    current_duty_cycle_us += is_forward_direction ? duty_cycle_step_us : -duty_cycle_step_us;
                    if(current_duty_cycle_us >= PERIOD_US){//если возрастание и достигли максимальной скважности
                        is_forward_direction = false;//значит надо сменить направление
                    }
                }
                is_blink = true;//теперь надо гореть
            }
            nrfx_systick_get(&state);
        }
        return false;
    }
    else{
        is_forward_direction = true;
        is_blink = false;
        first_get = true;
        state.time = 0;
        time_to_wait_us = 0;
        current_duty_cycle_us = 0;
        return true;
    }
}

bool led_many_blink(uint32_t led, uint32_t num, uint32_t duration_ms, bool enable){

    static uint32_t current_num = 0;

    if(led_single_blink(led, duration_ms, enable)){
        current_num++;
        if(current_num == num){
            current_num = 0;
            return true;
        }
    }
    return false;
}