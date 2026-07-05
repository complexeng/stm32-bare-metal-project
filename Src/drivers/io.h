#ifndef IO_H
#define IO_H
#include "stm32f446.h"

typedef enum {
	IO_INPUT = 0,
	IO_OUTPUT = 1,
	IO_AF = 2,
	IO_ANALOG = 3,
} IO_Mode;

typedef enum {
	PUP_NONE = 0,
	PUP_UP = 1,
	PUP_DOWN = 2
} Pupd_Mode;

typedef enum {
	IO_OUT_LOW = 0,
	IO_OUT_HIGH = 1
} IO_Out_State;

// 1. Initialization and Configuration
void gpio_init(GPIO_TypeDef *GPIOx, uint8_t pin, IO_Mode mode);
void gpio_set_pupd(GPIO_TypeDef *GPIOx, uint8_t pin, Pupd_Mode pupd); // controls the internal Pull-Up and Pull-Down resistors

// 2. Output Control (For Motors, LEDs)
void gpio_write(GPIO_TypeDef *GPIOx, uint8_t pin, IO_Out_State state);
void gpio_toggle(GPIO_TypeDef *GPIOx, uint8_t pin);

// 3. Input Reading (For IR Line Sensors, Buttons)
uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint8_t pin);

#endif
