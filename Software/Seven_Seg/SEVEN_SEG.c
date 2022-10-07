
#include "SEVEN_SEG/SEVEN_SEG.h"

const uint8_t SSValues[] = {0x3f , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x7 , 0x7f , 0x6f};

void SEVEN_SEG_init(void){
	
	SEVEN_SEG_EN_DDR = 0xff;
	SEVEN_SEG_DATA_DDR = 0xff;
}


void SEVEN_SEG_SELECT(uint8_t data)
{
	SEVEN_SEG_EN_PORT = 0x00;
	SEVEN_SEG_EN_PORT |= (1<<data);
}


void SS_Single_DISPLAY(uint8_t SevenSegOrder , uint8_t data)
{
	SEVEN_SEG_SELECT(SevenSegOrder);
	SEVEN_SEG_DATA_PORT = ~SSValues[data];
}
