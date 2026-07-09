#include "assert.h"
#include "delay.h"
#include "stm32f4xx.h"

void assert_handler(void){
	while(1){
		GPIOA->ODR ^= (0x1U << 5);
		delay_ms(150);
	}
}
