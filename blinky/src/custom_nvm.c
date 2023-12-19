#include "custom_nvm.h"

//начальный адрес, куда можно записывать
#define CUSTOM_APP_DATA_AREA_START_ADDR (0x0007f000)
//конечный адрес
#define CUSTOM_APP_DATA_AREA_END_ADDR (CUSTOM_APP_DATA_AREA_START_ADDR + CODE_PAGE_SIZE)

static state_save curent_state_save = {true, CUSTOM_APP_DATA_AREA_START_ADDR};

void save_data_to_nvm(union RGB_OR_WORD* rgb_or_word) {
    // if(curent_state_save.is_need_to_erase_page){
        
    //     curent_state_save.is_need_to_erase_page = false;
    // }
    nrfx_nvmc_word_write(curent_state_save.f_addr, rgb_or_word->word);
    curent_state_save.f_addr += 4;
    if(curent_state_save.f_addr == CUSTOM_APP_DATA_AREA_END_ADDR){
        nrfx_nvmc_page_erase(CUSTOM_APP_DATA_AREA_START_ADDR);
        nrfx_nvmc_word_write(CUSTOM_APP_DATA_AREA_START_ADDR, rgb_or_word->word);
        curent_state_save.f_addr = CUSTOM_APP_DATA_AREA_START_ADDR + 4;
    }
}

void read_data_from_nvm(union RGB_OR_WORD* rgb_or_word) {

    uint32_t f_addr = 0x0007f000;
    bool f = false;
    if(f){ nrfx_nvmc_page_erase(f_addr);}
    else{
    uint32_t *p_addr = (uint32_t *)f_addr;

    union RGB_OR_WORD default_rgb;

    default_rgb.word = *p_addr;

    if(default_rgb.word == (uint32_t)0xFFFFFFFF){
        default_rgb.color.r = RGB_DEFAULT_RED;
        default_rgb.color.g = RGB_DEFAULT_GREEN;
        default_rgb.color.b = RGB_DEFAULT_BLUE;
        default_rgb.color.flag_recorded = DEFAULT_FLAG_RECORDED;
        nrfx_nvmc_page_erase(f_addr);
        nrfx_nvmc_word_write(f_addr, default_rgb.word);
    }
    else{
        uint32_t i = 0;
        for (i = CUSTOM_APP_DATA_AREA_START_ADDR; i != CUSTOM_APP_DATA_AREA_END_ADDR; ) {
            p_addr = (uint32_t *)i;
            default_rgb.word = *p_addr;
            if(default_rgb.word == (uint32_t)0xFFFFFFFF){
                break;
            }
            else{
                i+=4;
            }
        }
        if(i == CUSTOM_APP_DATA_AREA_END_ADDR){
            nrfx_nvmc_page_erase(f_addr);
            nrfx_nvmc_word_write(f_addr, default_rgb.word);
            curent_state_save.f_addr = f_addr;
        }
        else{
            i-=4;
            curent_state_save.f_addr = i;
            p_addr = (uint32_t *)i;
            default_rgb.word = *p_addr;
        }
    }
    rgb_or_word->word = default_rgb.word;
    }
}

