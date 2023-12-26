#include "hsv_and_rgb.h"

#define MIN3(x,y,z)  ((y) <= (z) ? \
                         ((x) <= (y) ? (x) : (y)) \
                     : \
                         ((x) <= (z) ? (x) : (z)))
#define MAX3(x,y,z)  ((y) >= (z) ? \
                         ((x) >= (y) ? (x) : (y)) \
                     : \
                         ((x) >= (z) ? (x) : (z)))

void HSVToRGB(const HSV* current_hsv, RGB* result_rgb) {
    float H = current_hsv->hue, S = current_hsv->sat, V = current_hsv->val;
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        return;
    }
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-fabs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r,g,b;
    if(H >= 0 && H < 60){
        r = C,g = X,b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X,g = C,b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0,g = C,b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0,g = X,b = C;
    }
    else if(H >= 240 && H < 300){
        r = X,g = 0,b = C;
    }
    else{
        r = C,g = 0,b = X;
    }
    result_rgb->r = (float)(r+m) * MAX_RGB_FOR_PEOPLE;
    result_rgb->g = (float)(g+m) * MAX_RGB_FOR_PEOPLE;
    result_rgb->b = (float)(b+m) * MAX_RGB_FOR_PEOPLE;
}

void RGBToHSV(const RGB* current_rgb, HSV* result_hsv){
    float red = (current_rgb->r / 255.0), green = (current_rgb->g / 255.0), blue = (current_rgb->b / 255.0);
    float hue = 0, sat = 0;
    float maxval = MAX3(red, green, blue),
          minval = MIN3(red, green, blue);
    
    float difference = maxval - minval;

    if(difference == 0){
        hue=0;
    }
    else if(red == maxval){
        hue = fmod(((60*((green - blue) / difference)) + 360), 360.0);
    }
    else if(green == maxval){
        hue = fmod(((60*((blue - red) / difference)) + 120), 360.0);
    }
    else if(blue == maxval){
        hue = fmod(((60*((red - green) / difference)) + 240), 360.0);
    }
    result_hsv->hue = (hue);
    
    
    if(maxval == 0){
        sat = 0;
    }
    else{
        sat = 100 * (difference / maxval);
    }
    result_hsv->sat = (sat);
    
    result_hsv->val = (maxval*100);
}
