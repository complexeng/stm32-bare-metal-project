#include <stdint.h>

#define RCC_BASE         0x40023800U
#define RCC_AHB1ENR      (*(volatile unsigned int *)(RCC_BASE + 0x30))

#define GPIOA			 0x40020000U
#define GPIOA_MODER		 (*(volatile unsigned int *)(GPIOA + 0x00))
#define GPIOA_ODR        (*(volatile unsigned int *)(GPIOA + 0x14))

typedef struct {
	volatile uint32_t STK_CTRL; 	// offset 0x00 unsigned(+ nums only)
	volatile uint32_t STK_LOAD; 	// offset 0x04
	volatile uint32_t STK_VAL;  	// offset 0x08
	volatile uint32_t STK_CALIB;	// offset 0x0C
} SYSTICK_TypeDef;

#define SYSTICK_BASE 	 0xE000E010U
#define SYSTICK   		 ((SYSTICK_TypeDef *) SYSTICK_BASE)

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
	RCC_AHB1ENR |= (1 << 0);  // enable clock
	GPIOA_MODER |= (1 << 10); // set 01 do PA5
	GPIOA_ODR |= (1 << 5);

    while(1) {
    	delay_ms(1000);
    	GPIOA_ODR |= (1 << 5);
    	delay_ms(1000);
    	GPIOA_ODR &= ~(1 << 5);
    }

}
