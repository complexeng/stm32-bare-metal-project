#include "drivers/stm32f446.h"
#include "drivers/io.h"
#include "common/delay.h"

int main(void) {
	RCC->AHB1ENR |= (1 << 0);  // enable clock
	gpio_init(GPIOA, 5, IO_OUTPUT);
	gpio_write(GPIOA, 5, IO_OUT_HIGH);

    while(1) {
    	gpio_toggle(GPIOA, 5);
    	delay_ms(500);
    }

}
