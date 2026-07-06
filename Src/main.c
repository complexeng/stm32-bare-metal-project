#include "drivers/stm32f446.h"
#include "drivers/rcc.h"
#include "drivers/io.h"
#include "common/delay.h"

int main(void) {
	rcc_gpio_enable(PORTA);  // enable clock
	gpio_init(GPIOA, 5, IO_OUTPUT);
	gpio_write(GPIOA, 5, IO_OUT_HIGH);

	gpio_init(GPIOA, 9, IO_INPUT);
	gpio_set_pupd(GPIOA, 9, PUP_DOWN);

    while(1) {
    	if (gpio_read(GPIOA, 9) == 1) {
    		gpio_write(GPIOA, 5, IO_OUT_HIGH); // Turn LED ON when pressed
    	} else {
    		gpio_write(GPIOA, 5, IO_OUT_LOW);  // Turn LED OFF when released
    	}
    }

}
