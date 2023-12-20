#include "custom_nvm.h"

//начальный адрес, куда можно записывать
#define CUSTOM_APP_DATA_AREA_START_ADDR (0x0007f000)
//конечный адрес
#define CUSTOM_APP_DATA_AREA_END_ADDR (CUSTOM_APP_DATA_AREA_START_ADDR + CODE_PAGE_SIZE)

#define CELL_EMPTY (uint32_t)0xFFFFFFFF

static uint32_t curent_empty_f_addr = CUSTOM_APP_DATA_AREA_START_ADDR;

void save_data_to_nvm(union RGB_OR_WORD* rgb_or_word) {
    nrfx_nvmc_word_write(curent_empty_f_addr, rgb_or_word->word);
    curent_empty_f_addr += 4;
    if(curent_empty_f_addr == CUSTOM_APP_DATA_AREA_END_ADDR){
        nrfx_nvmc_page_erase(CUSTOM_APP_DATA_AREA_START_ADDR);
        nrfx_nvmc_word_write(CUSTOM_APP_DATA_AREA_START_ADDR, rgb_or_word->word);
        curent_empty_f_addr = CUSTOM_APP_DATA_AREA_START_ADDR + 4;
    }
}

void read_data_from_nvm(union RGB_OR_WORD* rgb_or_word) {

    uint32_t f_addr = (uint32_t)CUSTOM_APP_DATA_AREA_START_ADDR;
    uint32_t *p_addr = (uint32_t *)f_addr;

    union RGB_OR_WORD current_rgb_or_word;

    current_rgb_or_word.word = *p_addr;

    if(current_rgb_or_word.word == CELL_EMPTY){
        current_rgb_or_word.color.r = RGB_DEFAULT_RED;
        current_rgb_or_word.color.g = RGB_DEFAULT_GREEN;
        current_rgb_or_word.color.b = RGB_DEFAULT_BLUE;
        current_rgb_or_word.color.flag_recorded = DEFAULT_FLAG_RECORDED;
        nrfx_nvmc_word_write(f_addr, current_rgb_or_word.word);
    }
    else{
        uint32_t i = 0;
        for (i = CUSTOM_APP_DATA_AREA_START_ADDR; i != CUSTOM_APP_DATA_AREA_END_ADDR; i += 4) {
            p_addr = (uint32_t *)i;
            current_rgb_or_word.word = *p_addr;
            if(current_rgb_or_word.word == CELL_EMPTY){
                break;
            }
        }
        if(i == CUSTOM_APP_DATA_AREA_END_ADDR){
            nrfx_nvmc_page_erase(CUSTOM_APP_DATA_AREA_START_ADDR);
            nrfx_nvmc_word_write(CUSTOM_APP_DATA_AREA_START_ADDR, current_rgb_or_word.word);
            curent_empty_f_addr = CUSTOM_APP_DATA_AREA_START_ADDR + 4;
        }
        else{
            curent_empty_f_addr = i;
            i -= 4;
            p_addr = (uint32_t *)i;
            current_rgb_or_word.word = *p_addr;
        }
    }
    rgb_or_word->word = current_rgb_or_word.word;
}

