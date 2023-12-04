#include "change_hsv.h"

void change_h(HSV *current_hsv){
    if((*current_hsv).h == MAX_HUE){
        (*current_hsv).h = 0;
    }
    else{
        (*current_hsv).h = (*current_hsv).h + 1;
    }
}

void change_s(HSV *current_hsv, state_s* current_s){
    if((*current_hsv).s == 0){
        (*current_s).f = false;
    }
    else
         if((*current_hsv).s == MAX_SAT){
            (*current_s).f = true;
        }
    (*current_hsv).s = (*current_hsv).s + ((*current_s).f ? -1 : 1) ;
}

void change_v(HSV *current_hsv, state_v* current_v){
    if((*current_hsv).v == 0){
        (*current_v).f = false;
    }
    else
         if((*current_hsv).v == MAX_VAL){
            (*current_v).f = true;
        }
    (*current_hsv).v = (*current_hsv).v + ((*current_v).f ? -1 : 1) ;
}