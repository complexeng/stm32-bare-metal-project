#include "stm32f4xx.h"
#include "common/assert.h"
#include "drivers/mcu_init.h"
#include "drivers/io.h"
#include "drivers/uart.h"

int main(void) {
	mcu_init();
	uart_init(GPIOA);

    while(1) {
    	// Trigger the interrupt-driven string transmission
		uart_send_str("Terence M\n\r");

		// Delay loop so your terminal isn't overwhelmed
		for (volatile int i = 0; i < 100000; i++);
    }

}
