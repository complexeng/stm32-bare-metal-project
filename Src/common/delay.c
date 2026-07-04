#include "delay.h"
#include "../drivers/stm32f446.h"

void delay_ms(uint32_t ms){
	// Systick init sequence: program reload value, clear current value, ctrl/status register
	(*SYSTICK).STK_LOAD = 15999;
	(*SYSTICK).STK_VAL = 0;
	(*SYSTICK).STK_CTRL |= (1 << 0) | (1 << 2);

	// 16 bit returns 1 if timer counted to 0 since last time this was read.
	for(uint32_t i = 0; i < ms; i++){
		while (((*SYSTICK).STK_CTRL & (1 << 16)) == 0) {
			// do nothing
		}
	};
}

