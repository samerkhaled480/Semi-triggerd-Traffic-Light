

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include "../std_macros.h"

#define SEVEN_SEG_DATA_DDR DDRC
#define SEVEN_SEG_EN_DDR DDRD

#define SEVEN_SEG_DATA_PORT PORTC
#define SEVEN_SEG_EN_PORT PORTD


void SEVEN_SEG_init(void);
void SEVEN_SEG_SELECT(uint8_t data);
void SS_Single_DISPLAY(uint8_t SevenSegOrder , uint8_t data);



#endif 