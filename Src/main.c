#include "stm32f4xx.h"
#include "drivers/mcu_init.h"
#include "drivers/io.h"
#include "common/delay.h"
#include "common/assert.h"

int main(void) {
	mcu_init();

	gpio_init(GPIOA, 0, IO_INPUT);
	gpio_set_pupd(GPIOA, 0, PUP_DOWN);
	interrupt_init(GPIOA, 0, RISING_EDGE);
	NVIC_SetPriority(EXTI0_IRQn, 2); // Set default mid-level priority
	NVIC_EnableIRQ(EXTI0_IRQn);      // Open the gate

	gpio_init(GPIOA, 1, IO_INPUT);
	gpio_set_pupd(GPIOA, 1, PUP_DOWN);
	interrupt_init(GPIOA, 1, RISING_EDGE);
	NVIC_SetPriority(EXTI1_IRQn, 3); // Set default mid-level priority
	NVIC_EnableIRQ(EXTI1_IRQn);      // Open the gate

	gpio_init(GPIOC, 2, IO_INPUT);
	gpio_set_pupd(GPIOC, 2, PUP_DOWN);
	interrupt_init(GPIOC, 2, RISING_EDGE);
	NVIC_SetPriority(EXTI2_IRQn, 4); // Set default mid-level priority
	NVIC_EnableIRQ(EXTI2_IRQn);      // Open the gate

	gpio_init(GPIOC, 3, IO_INPUT);
	gpio_set_pupd(GPIOC, 3, PUP_DOWN);
	interrupt_init(GPIOC, 3, RISING_EDGE);
	NVIC_SetPriority(EXTI3_IRQn, 4); // Set default mid-level priority
	NVIC_EnableIRQ(EXTI3_IRQn);      // Open the gate

	gpio_init(GPIOC, 13, IO_INPUT);
	gpio_set_pupd(GPIOC, 13, PUP_NONE);
	interrupt_init(GPIOC, 13, FALLING_EDGE);
	NVIC_SetPriority(EXTI15_10_IRQn, 2); // Set default mid-level priority
	NVIC_EnableIRQ(EXTI15_10_IRQn);      // Open the gate

    while(1) {

    }

}
