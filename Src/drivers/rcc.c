#include "rcc.h"

void rcc_gpio_enable(Port port){
	RCC->AHB1ENR |= (1U << (uint8_t)port);
}

void rcc_dma_enable(Rcc_Dma rcc_dma){
	RCC->AHB1ENR |= (1U << (uint8_t)rcc_dma);
}
