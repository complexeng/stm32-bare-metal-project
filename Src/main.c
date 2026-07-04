#include "drivers/stm32f446.h"

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

int main(void) {
	RCC->AHB1ENR |= (1 << 0);  // enable clock
	GPIOA->MODER |= (1 << 10); // set 01 do PA5
	GPIOA->ODR |= (1 << 5);

    while(1) {
    	delay_ms(500);
    	GPIOA->ODR |= (1 << 5);
    	delay_ms(500);
    	GPIOA->ODR &= ~(1 << 5);
    }

}
