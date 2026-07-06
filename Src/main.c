#include "drivers/stm32f446.h"
#include "drivers/io.h"
#include "common/delay.h"

int main(void) {
	RCC->AHB1ENR |= (1 << 0);  // enable clock
	gpio_init(GPIOA, 5, IO_OUTPUT);
	gpio_write(GPIOA, 5, IO_OUT_HIGH);

	gpio_init(GPIOA, 9, IO_INPUT);
	gpio_set_pupd(GPIOA, 9, PUP_DOWN);

    while(1) {
    	if (gpio_read(GPIOA, 9) == 0){
    		gpio_write(GPIOA, 5, IO_OUT_LOW);
    	}else{
    		gpio_write(GPIOA, 5, IO_OUT_HIGH);
    	}
    }

}
