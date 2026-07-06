#ifndef RCC_H
#define RCC_H
#include "stm32f446.h"

typedef enum {
	RCC_DMA1 = 21,
	RCC_DMA2 = 22
} Rcc_Dma;

void rcc_gpio_enable(Port port);
void rcc_dma_enable(Rcc_Dma rcc_dma);

#endif
