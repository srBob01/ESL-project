#include "change_hsv.h"

void change_hue(HSV *current_hsv){
    if(current_hsv->hue == MAX_HUE){
        current_hsv->hue = 0;
    }
    else{
        current_hsv->hue++;
    }
}

void change_sat(HSV *current_hsv, enum state_direction* current_sat){
    if(current_hsv->sat == 0){
        (*current_sat) = DIRECTION_FORWARD;
    }
    else
         if(current_hsv->sat == MAX_SAT){
            (*current_sat) = DIRECTION_DOWNWARD;
        }
    if((*current_sat) == DIRECTION_FORWARD){
        current_hsv->sat++;
    }
    else{
        current_hsv->sat--;
    }
}

void change_val(HSV *current_hsv, enum state_direction* current_val){
    if(current_hsv->val == 0){
        (*current_val) = DIRECTION_FORWARD;
    }
    else
         if(current_hsv->val == MAX_VAL){
            (*current_val) = DIRECTION_DOWNWARD;
        }
    if((*current_val) == DIRECTION_FORWARD){
        current_hsv->val++;
    }
    else{
        current_hsv->val--;
    }
}