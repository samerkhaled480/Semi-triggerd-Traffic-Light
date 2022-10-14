
#ifndef __TRAFIC_LIGHT_H__
#define __TRAFIC_LIGHT_H__

#include "std_macros.h"
#include "../modules/Seven_Seg/SEVEN_SEG.h"
#include "../modules/Interrupt/INTERRUPT.h"
#include "../modules/Timer0/TIMER0.h"
//#include "../modules/Timer2/TIMER2.h"

#define Traffic_signs_PORT PORTC
#define Traffic_signs_DDR  DDRC


enum Traffic_Sig{
    Car_G,
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

typedef enum {
    car_go,
    car_stop,
    car_set,
    car_set_pp_set,
    car_Stop_pp_go,   

}traffic_state;


void timer0_isr(void);
void Leds_state(traffic_state state);

#endif