#include "mcu_init.h"
#include "io.h"

static inline void enable_external_interrupts(void){
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

static inline void rcc_init(void){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
}

void io_init(void){
	gpio_init(GPIOA, 5, IO_OUTPUT);
	gpio_write(GPIOA, 5, IO_OUT_HIGH);

	gpio_init(GPIOA, 9, IO_INPUT);
	gpio_set_pupd(GPIOA, 9, PUP_DOWN);

	gpio_init(GPIOC, 13, IO_INPUT);
	gpio_set_pupd(GPIOC, 13, PUP_NONE);

}

void mcu_init(void){
	rcc_init();
	enable_external_interrupts();
	io_init();
}
