#include "stm32f4xx.h"
#include "drivers/mcu_init.h"
#include "drivers/io.h"
#include "common/delay.h"
#include "common/assert.h"

int main(void) {
	mcu_init();
	interrupt_init(GPIOC, 13, FALLING_EDGE);
	NVIC_SetPriority(EXTI15_10_IRQn, 2); // Set default mid-level priority
	NVIC_EnableIRQ(EXTI15_10_IRQn);      // Open the gate!

    while(1) {
    	if (gpio_read(GPIOA, 9) == 1) {
    		gpio_write(GPIOA, 5, IO_OUT_HIGH); // Turn LED ON when pressed
    	} else {
    		gpio_write(GPIOA, 5, IO_OUT_LOW);  // Turn LED OFF when released
    	}
    }

}
