#include "mcu_init.h"
#include "io.h"

static inline void enable_external_interrupts(void){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

static inline void rcc_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void io_init(void){
	gpio_init(GPIOA, 5, IO_OUTPUT);
	gpio_write(GPIOA, 5, IO_OUT_HIGH);

	// init blue button
	gpio_init(GPIOC, 13, IO_INPUT);
	gpio_set_pupd(GPIOC, 13, PUP_NONE);
	interrupt_init(GPIOC, 13, FALLING_EDGE);
	NVIC_SetPriority(EXTI15_10_IRQn, 2);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// UART pins setup
	gpio_init(GPIOA, 2, IO_AF);
	gpio_init(GPIOA, 3, IO_AF);
}

void mcu_init(void){
	rcc_init();
	enable_external_interrupts();
	io_init();
}
