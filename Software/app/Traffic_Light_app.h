
#ifndef __TRAFIC_LIGHT_H__
#define __TRAFIC_LIGHT_H__

#include "std_macros.h"
#include "../modules/Seven_Seg/SEVEN_SEG.h"
#include "../Interrupt/INTERRUPT.h"
//#include "Timer0/TIMER0.h"

enum Traffic_Sig{
    CAR_G,
    Car_Y,
    Car_R,
    PP_G,
    PP_Y,
    PP_R
};

enum Traffic_SS {
    EN_C_1,
    EN_C_2,
    EN_PP_1,
    EN_PP_2
};

#endif