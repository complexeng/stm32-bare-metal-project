#include "io.h"

void gpio_init(GPIO_TypeDef *GPIOx, uint8_t pin, IO_Mode mode){
	// 1. Clear the two current mode bits for this specific pin.
	GPIOx->MODER &= ~(0x3U << pin * 2);
	// 2. Set the new mode bits
	GPIOx->MODER |= ((uint32_t)mode << (pin * 2));
}

void gpio_set_pupd(GPIO_TypeDef *GPIOx, uint8_t pin, Pupd_Mode pupd){
	// Clear the two current pull bits for this pin
	GPIOx->PUPDR &= ~(0x3U << (pin * 2));

	// Set the new pull bits
	GPIOx->PUPDR |= ((uint32_t)pupd << (pin * 2));
}

void gpio_write(GPIO_TypeDef *GPIOx, uint8_t pin, IO_Out_State state){
	GPIOx->ODR &= ~(0x1U << pin);
	GPIOx->ODR |= ((uint8_t)state << pin);
}

void gpio_toggle(GPIO_TypeDef *GPIOx, uint8_t pin){
	GPIOx->ODR ^= (0x1U << pin);
}

uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint8_t pin){
	return 0;
}
