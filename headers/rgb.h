#ifndef RGB_H
#define RGB_H

#include <stdint.h>

#define MAX_RGB_FOR_BLINK 10000
#define MAX_RGB_FOR_PEOPLE 255

#define RGB_DEFAULT_RED 255
#define RGB_DEFAULT_GREEN 153
#define RGB_DEFAULT_BLUE 0
#define DEFAULT_FLAG_RECORDED 0

static const float ration_rgb_people_to_blink = MAX_RGB_FOR_BLINK / MAX_RGB_FOR_PEOPLE;

typedef struct{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t flag_recorded;
} RGB;

union RGB_OR_WORD{
    RGB color;
    uint32_t word;
};


#endif//RGB_H