#ifndef HSV_H
#define HSV_H

#define MAX_VAL 100
#define MAX_SAT 100
#define MAX_HUE 360
#define DEFAULT_VAL MAX_VAL
#define DEFAULT_SAT MAX_SAT
#define DEFAULT_HUE 36

typedef struct{
    float hue;
    float sat;
    float val;
} HSV;

#endif//HSV_H