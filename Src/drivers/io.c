#include "io.h"
#include "../common/assert.h"

#define GET_PORT_INDEX(GPIOx)  (((uint32_t)(GPIOx) - GPIOA_BASE) / 0x0400UL)
/*
	GPIOA_BASE = 0x4002 0000
	GPIOB_BASE = 0x4002 0400 (0x40020000 + 0x0400)
	GPIOC_BASE = 0x4002 0800 (0x40020000 + 0x0800)
 */

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
	if(state == IO_OUT_HIGH){
		GPIOx->BSRR = (1U << pin);
	} else {
		GPIOx->BSRR = (1U << (pin + 16));
	}
}

void gpio_toggle(GPIO_TypeDef *GPIOx, uint8_t pin){
	GPIOx->ODR ^= (0x1U << pin);
}

uint8_t gpio_read(GPIO_TypeDef *GPIOx, uint8_t pin){
	if( (GPIOx->IDR & (1U << pin)) != 0 ){
		return 1;
	}
	return 0;
}

void interrupt_init(GPIO_TypeDef *GPIOx, uint8_t pin, Interrupt_Edge edge){

	// Connect PxPIN to EXTI Line pin via SYSCFG
	// EXTICR[X] controls EXTIx through EXTIx
	// Clear the 4 bits for pin X (bits x to x) and write 0xX to select Port X.
	uint8_t exticr_reg_slot = pin / 4;				// 1/4 = 0, 4/4 or 5/4 = 1, 8/4 = 2, 12/4 = 3
	uint32_t port_index = GET_PORT_INDEX(GPIOx);	//
	uint8_t exticr_bit_shift = (pin % 4) * 4;		// (0%4)*4=0, (1%4)*4=4, (2%4)*4=8, (3%4)*4=12

	SYSCFG->EXTICR[exticr_reg_slot] &= ~(0xFU << exticr_bit_shift);
	SYSCFG->EXTICR[exticr_reg_slot] |= (port_index << exticr_bit_shift);

	// 4. Configure EXTI Line 13 edge triggers
	EXTI->IMR |= (1U << pin);     // Unmask EXTI13 (Enable the line)
	switch(edge){
		case RISING_EDGE:
			EXTI->RTSR |= (1U << pin);     // Trigger on Rising Edge
			EXTI->FTSR &= ~(1U << pin);    // Disable Rising Edge trigger
			break;
		case FALLING_EDGE:
			EXTI->FTSR |= (1U << pin);    // Trigger on Falling Edge
			EXTI->RTSR &= ~(1U << pin);   // Disable Rising Edge trigger
			break;
		case BOTH_EDGES:
			EXTI->RTSR |= (1U << pin);    // Enable Rising Edge
			EXTI->FTSR |= (1U << pin);    // Enable Falling Edge
			break;
		default:
			break;
	}
	/*
	 * 	NVIC_SetPriority(EXTI15_10_IRQn, 2); // Set default mid-level priority
	 *  NVIC_EnableIRQ(EXTI15_10_IRQn);      // Open the gate!
	 */

}

void EXTI0_IRQHandler(void) {
    // Clear flag for Pin 1
    EXTI->PR = (1U << 0);

    // Your code here...
    gpio_write(GPIOA, 5, IO_OUT_HIGH);
}


void EXTI1_IRQHandler(void) {
    // Clear flag for Pin 1
    EXTI->PR = (1U << 1);

    // Your code here...
    gpio_write(GPIOA, 5, IO_OUT_HIGH);
}

void EXTI2_IRQHandler(void) {
    // Clear flag for Pin 2
    EXTI->PR = (1U << 2);

    // Your code here...
    gpio_write(GPIOA, 5, IO_OUT_HIGH);
}

void EXTI3_IRQHandler(void) {
    // Clear flag for Pin 3
    EXTI->PR = (1U << 3);

    // Your code here...
    gpio_write(GPIOA, 5, IO_OUT_HIGH);
}

void EXTI4_IRQHandler(void) {
    // Clear flag for Pin 4
    EXTI->PR = (1U << 4);

    // Your code here...
}

void EXTI9_5_IRQHandler(void) {
	if ((EXTI->PR & (1U << 5)) != 0) {
	        EXTI->PR = (1U << 5); // Clear flag for Pin 5

	        // Handle Pin 5 event here...
	    }
}

void EXTI15_10_IRQHandler(void) {
    if ((EXTI->PR & (1U << 13)) != 0) {
        EXTI->PR = (1U << 13);          // CRITICAL: Clear the flag!
        gpio_write(GPIOA, 5, IO_OUT_LOW);
    }
}
