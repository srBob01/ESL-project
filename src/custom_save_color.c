#include "custom_save_color.h"

union RGB_OR_WORD save_hsv(int hue, int sat, int val){
    HSV temp_hsv;
    temp_hsv.hue = hue;
    temp_hsv.sat = sat;
    temp_hsv.val = val;
    union RGB_OR_WORD temp_rgb_or_word;
    temp_rgb_or_word.color.flag_recorded = DEFAULT_FLAG_RECORDED;
    HSVToRGB(&temp_hsv, &temp_rgb_or_word.color);
    save_data_to_nvm(&temp_rgb_or_word);
    return temp_rgb_or_word;
}

union RGB_OR_WORD save_rgb(int red, int green, int blue){
    union RGB_OR_WORD temp_rgb_or_word;
    temp_rgb_or_word.color.r = red;
    temp_rgb_or_word.color.g = green;
    temp_rgb_or_word.color.b = blue;
    temp_rgb_or_word.color.flag_recorded = DEFAULT_FLAG_RECORDED;
    save_data_to_nvm(&temp_rgb_or_word);
    return temp_rgb_or_word;
}