#include "custom_blink_pwm_led.h"

#define COUNT_STEP_1 50
#define COUNT_STEP_2 (COUNT_STEP_1 / 2)

#define SIZE_ARRAY_1 (COUNT_STEP_1 * 2)
#define SIZE_ARRAY_2 (COUNT_STEP_2 * 2)

#define LAST_I_ARRAY_1 (SIZE_ARRAY_1 - 1)
#define LAST_I_ARRAY_2 (SIZE_ARRAY_2 - 1)

static int low_seq_values_led_condition[SIZE_ARRAY_1];
static int quick_seq_values_led_condition[SIZE_ARRAY_2];

static nrf_pwm_values_individual_t seq_values[] = { {0}, {0}, {0}, {0} };
static nrfx_pwm_t m_pwm = NRFX_PWM_INSTANCE(0);

static HSV current_hsv;
static union RGB_OR_WORD current_rgb_or_word;

static enum state_direction current_sat = DIRECTION_FORWARD;
static enum state_direction current_val = DIRECTION_FORWARD;

static enum state_led_rgb current_state_change_ledRGB = STATE_RGB_NONE;
static enum state_led_rgb last_significant_state_change_ledRGB = STATE_RGB_VAL;

static enum state_led_condition current_state_change_led_condition = STATE_COND_NONE;

static state_iterator current_i_led_condition = {0, true};

void init_array_for_led_condition(int *arr, int count_step, int last_i){
    uint32_t step = MAX_RGB_FOR_BLINK / count_step;
    uint32_t value = 0;
    for(int i = 0; i < count_step; ++i){
        arr[i] = value;
        arr[last_i - i] = value; 
        value += step;
    }
}

void init_arrays_for_led_condition(){
    init_array_for_led_condition(low_seq_values_led_condition, COUNT_STEP_1, LAST_I_ARRAY_1);
    init_array_for_led_condition(quick_seq_values_led_condition, COUNT_STEP_2, LAST_I_ARRAY_2);
}

void update_i_led_condition(){
    if((current_state_change_led_condition == STATE_COND_LOW && current_i_led_condition.i == LAST_I_ARRAY_1) ||
        (current_state_change_led_condition == STATE_COND_QUICK && current_i_led_condition.i == LAST_I_ARRAY_2))
    {
        current_i_led_condition.i = 0;
    }
    else{
        current_i_led_condition.i++;
    }
}

void make_change_led_condition(){
    if(current_i_led_condition.is_new){
        switch(current_state_change_led_condition){
            case STATE_COND_LOW:
                seq_values->channel_3 = low_seq_values_led_condition[current_i_led_condition.i];
                update_i_led_condition();
                break;
            case STATE_COND_QUICK:
                seq_values->channel_3 = quick_seq_values_led_condition[current_i_led_condition.i];
                update_i_led_condition();
                break;
            case STATE_COND_FULL:
                seq_values->channel_3 = MAX_RGB_FOR_BLINK;
                current_i_led_condition.is_new = false;
                break;
            case STATE_COND_NONE:
                seq_values->channel_3 = 0;
                current_i_led_condition.is_new = false;
                break;
            default:
                break;
        }
    }
}

void make_change_ledRGB(){
    switch(current_state_change_ledRGB){
        case STATE_RGB_HUE:
            change_hue(&current_hsv);
            break;
        case STATE_RGB_SAT:
            change_sat(&current_hsv, &current_sat);
            break;
        case STATE_RGB_VAL:
            change_val(&current_hsv, &current_val);
            break;
        case STATE_RGB_NONE:
            return;
    }
    HSVToRGB(&current_hsv, &current_rgb_or_word.color);
    seq_values->channel_0 = (current_rgb_or_word.color.r * ration_rgb_people_to_blink);
    seq_values->channel_1 = (current_rgb_or_word.color.g * ration_rgb_people_to_blink);
    seq_values->channel_2 = (current_rgb_or_word.color.b * ration_rgb_people_to_blink);
    save_data_to_nvm(&current_rgb_or_word);
}

void pwm_individual_led_handler(nrfx_pwm_evt_type_t event_type){
    if (event_type == NRFX_PWM_EVT_FINISHED){
        make_change_led_condition();
        make_change_ledRGB();
    }
}

void pwm_individual_init_led(void){
    const nrfx_pwm_config_t config = {
        .output_pins = {
        MY_LED_2_R, 
        MY_LED_2_G, 
        MY_LED_2_B,
        MY_LED_1 
        },
        .irq_priority = APP_IRQ_PRIORITY_LOWEST,
        .base_clock   = NRF_PWM_CLK_1MHz,
        .count_mode   = NRF_PWM_MODE_UP,
        .top_value    = MAX_RGB_FOR_BLINK,
        .load_mode    = NRF_PWM_LOAD_INDIVIDUAL,
        .step_mode    = NRF_PWM_STEP_AUTO
    };
    APP_ERROR_CHECK(nrfx_pwm_init(&m_pwm, &config, pwm_individual_led_handler));
}

void pwm_play_led(void){
    const nrf_pwm_sequence_t seq = {
        .values  = (nrf_pwm_values_t){.p_individual = (nrf_pwm_values_individual_t *)&seq_values},
        .length           = NRF_PWM_VALUES_LENGTH(seq_values),
        .repeats          = 0,
        .end_delay        = 0
    };
    pwm_individual_init_led();
    read_data_from_nvm(&current_rgb_or_word);
    RGBToHSV(&current_rgb_or_word.color, &current_hsv);
    seq_values->channel_0 = (current_rgb_or_word.color.r * ration_rgb_people_to_blink);
    seq_values->channel_1 = (current_rgb_or_word.color.g * ration_rgb_people_to_blink);
    seq_values->channel_2 = (current_rgb_or_word.color.b * ration_rgb_people_to_blink);
    (void)nrfx_pwm_simple_playback(&m_pwm, &seq, 1, NRFX_PWM_FLAG_LOOP);
}

void pwm_change_mode_ledRGB(void){
    if(current_state_change_ledRGB != STATE_RGB_NONE){
        last_significant_state_change_ledRGB = current_state_change_ledRGB;
        current_state_change_ledRGB = STATE_RGB_NONE;
    }
    else{
        switch(last_significant_state_change_ledRGB){
            case STATE_RGB_HUE:
                current_state_change_ledRGB = STATE_RGB_SAT;
                break;
            case STATE_RGB_SAT:
                current_state_change_ledRGB = STATE_RGB_VAL;
                break;
            case STATE_RGB_VAL:
                current_state_change_ledRGB = STATE_RGB_HUE;
                break;
            default:
                break;
        }
    }
}

void pwm_change_mode_led_condition(void){
    switch(current_state_change_led_condition){
        case STATE_COND_LOW:
            current_i_led_condition.i = 0;
            current_state_change_led_condition = STATE_COND_QUICK;
            break;
        case STATE_COND_QUICK:
            current_state_change_led_condition = STATE_COND_FULL;
            break;
        case STATE_COND_FULL:
            current_state_change_led_condition = STATE_COND_NONE;
            current_i_led_condition.is_new = true;
            break;
        case STATE_COND_NONE:
            current_state_change_led_condition = STATE_COND_LOW;
            current_i_led_condition.is_new = true;
            current_i_led_condition.i = 0;
            break;
        default:
            break;
    }
}
