#include "custom_blink_pwm_led.h"

static const int size_array_1 = COUNT_STEP_1 * 2;
static const int size_array_2 = COUNT_STEP_2 * 2;

static const int last_i_array_1 = size_array_1 - 1;
static const int last_i_array_2 = size_array_2 - 1;

static int seq_values1_led1[COUNT_STEP_1 * 2];
static int seq_values2_led1[COUNT_STEP_2 * 2];

static nrf_pwm_values_individual_t seq_values[] = { {0}, {0}, {0}, {0} };
static nrfx_pwm_t m_pwm = NRFX_PWM_INSTANCE(0);

static HSV current_hsv = {36, 100, 100};
static RGB current_rgb = {0, 0, 0};

static state_s current_s = {true};
static state_v current_v = {true};

static enum state_led_rgb current_state_change_ledRGB = NONE_RGB;
static enum state_led_rgb last_significant_state_change_ledRGB = VALUE;

static enum state_led1 current_state_change_led1 = NONE_1;

static state_iteration current_i_led1 = {0, true, true};

void init_array1_for_led1(){
    uint32_t step = MAX_RGB / COUNT_STEP_1;
    uint32_t value = 0;
    for(int i = 0; i < COUNT_STEP_1; ++i){
        seq_values1_led1[i] = value;
        seq_values1_led1[last_i_array_1 - i] = value; 
        value += step;
    }
}

void init_array2_for_led1(){
    uint32_t step = MAX_RGB / COUNT_STEP_2;
    uint32_t value = 0;
    for(int i = 0; i < COUNT_STEP_2; ++i){
        seq_values2_led1[i] = value;
        seq_values2_led1[last_i_array_2 - i] = value;
        value += step;
    }
}

void update_i_led1(){
    if((current_i_led1.is_first_ar && current_i_led1.i == last_i_array_1) ||
        (!current_i_led1.is_first_ar && current_i_led1.i == last_i_array_2))
    {
        current_i_led1.i = 0;
    }
    current_i_led1.i = current_i_led1.i + 1;
}

void make_change_led1(){
    if(current_i_led1.is_new){
        switch(current_state_change_led1){
            case LOW:
                seq_values->channel_3 = seq_values1_led1[current_i_led1.i];
                update_i_led1();
                break;
            case QUICK:
                seq_values->channel_3 = seq_values2_led1[current_i_led1.i];
                update_i_led1();
                break;
            case FULL:
                seq_values->channel_3 = MAX_RGB;
                current_i_led1.is_new = false;
                break;
            case NONE_1:
                seq_values->channel_3 = 0;
                current_i_led1.is_new = false;
                break;
            default:
                break;
        }
    }
}

void make_change_ledRGB(){
    HSVToRGB(current_hsv, &current_rgb);
    seq_values->channel_0 = current_rgb.r;
    seq_values->channel_1 = current_rgb.g;
    seq_values->channel_2 = current_rgb.b;
}

void pwm_individual_led_handler(nrfx_pwm_evt_type_t event_type){
    if (event_type == NRFX_PWM_EVT_FINISHED){
        make_change_led1();
        switch(current_state_change_ledRGB){
            case HUE:
                change_h(&current_hsv);
                break;
            case SATURATION:
                change_s(&current_hsv, &current_s);
                break;
            case VALUE:
                change_v(&current_hsv, &current_v);
                break;
            case NONE_RGB:
                return;
        }
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
        .top_value    = MAX_RGB,
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
    make_change_ledRGB();
    make_change_led1();
    (void)nrfx_pwm_simple_playback(&m_pwm, &seq, 1, NRFX_PWM_FLAG_LOOP);
}

void update_hsv(){
    current_hsv.h = 36;
    current_hsv.s = 100;
    current_hsv.v = 100;
    make_change_ledRGB();
}

void pwm_change_mode_ledRGB(void){
    if(current_state_change_ledRGB != NONE_RGB){
        last_significant_state_change_ledRGB = current_state_change_ledRGB;
        current_state_change_ledRGB = NONE_RGB;
    }
    else{
        switch(last_significant_state_change_ledRGB){
            case HUE:
                current_state_change_ledRGB = SATURATION;
                break;
            case SATURATION:
                current_state_change_ledRGB = VALUE;
                break;
            case VALUE:
                current_state_change_ledRGB = HUE;
                break;
            default:
                break;
        }
    }
}

void pwm_change_mode_led1(void){
    switch(current_state_change_led1){
        case LOW:
            current_i_led1.is_first_ar = false;
            current_i_led1.i = 0;
            current_state_change_led1 = QUICK;
            break;
        case QUICK:
            current_state_change_led1 = FULL;
            break;
        case FULL:
            current_state_change_led1 = NONE_1;
            current_i_led1.is_new = true;
            break;
        case NONE_1:
            current_state_change_led1 = LOW;
            current_i_led1.is_new = true;
            current_i_led1.is_first_ar = true;
            current_i_led1.i = 0;
            update_hsv();
            break;
        default:
            break;
    }
}
