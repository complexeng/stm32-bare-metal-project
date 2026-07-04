#include "drivers/stm32f446.h"
#include "common/delay.h"

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
