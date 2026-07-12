#include "uart.h"
#include <stddef.h>

#define BUS_CLK     16000000U
#define BAUD_RATE   9600U

const char *tx_buffer = NULL;

void uart_init(GPIO_TypeDef *GPIOx){
	// hooks up the physical copper pins PA2 and PA3 on MCU to
	// internal hardware engine of USART2 using Alternate Function 7 (AF7)
	GPIOx->AFR[0] &= ~((0xFU << (4 * 2)) | (0xFU << (4 * 3))); // Clear 4-bit slots
	GPIOx->AFR[0] |=  ((7U  << (4 * 2)) | (7U  << (4 * 3)));   // Set both slots to AF7

	// Program the M bit in USART_CR1 to define the word length
	USART2->CR1 &= ~USART_CR1_M;

	// Program the number of stop bits in USART_CR2.
	USART2->CR2 &= ~USART_CR2_STOP; // or USART2->CR2 &= ~(3U << 12)

	// Select the desired baud rate using the USART_BRR
	USART2->BRR = ((BUS_CLK + (BAUD_RATE / 2U)) / BAUD_RATE); // USART2->BRR = 0x0683;

	// --- NEW TRANSMIT INTERRUPT CONFIGURATION ---
	// 1. Configure the CPU Core NVIC to accept USART2 interrupts
	NVIC_SetPriority(USART2_IRQn, 3);
	NVIC_EnableIRQ(USART2_IRQn);

	// 2. Clear TXEIE for now (We only turn it on when we actually have a message to send)
	USART2->CR1 &= ~USART_CR1_TXEIE;

	// Enable USART by writing UE bit in USART_CR1 register to 1
	// Set the TE bit in USART_CR1 to send an idle frame as first transmission
	USART2->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

	// At this exact moment, setting TE will automatically trigger the hardware
	// to output an "Idle Frame" (a stream of 1s) to sit at resting voltage.
}

void uart_send_char_polling(char c) {
    // Wait until the Transmit Data Register Empty flag (TXE) is set to 1
    while (!(USART2->SR & USART_SR_TXE)); // while TXE is 0 (while DR is full)

    // Write the character to the Data Register
    USART2->DR = (c & 0xFF);
}

void uart_send_string_polling(char* str){

	for (int i = 0; str[i] != '\0'; i++) {
		uart_send_char_polling(str[i]);
	}

}

// TXE (transmit empty flag)
// TXE = 1 = DR is empty -------> The interrupt is generated when DR is empty (hardware is ready for data)
// TXE = 0 = DR is full
void uart_send_str(char *str) {
	tx_buffer = str;               // Save the string pointer
	USART2->CR1 |= USART_CR1_TXEIE; // Turn on the interrupt to jumpstart the process
}

void USART2_IRQHandler(void) {
	// 1. Verify that the TXE (Transmit Empty) flag caused the interrupt
	if (USART2->SR & USART_SR_TXE) { // if TXE == 1 ( if DR is empty )

		// 2. Check if we have data left to send
		if (tx_buffer != NULL && *tx_buffer != '\0') {
			// Write the current character to DR (This automatically clears the TXE flag)
			USART2->DR = (*tx_buffer & 0xFF);
			tx_buffer++; // Move pointer to next character
		} else {
			// 3. No more data left! Turn off TXEIE so the interrupt stops firing
			USART2->CR1 &= ~USART_CR1_TXEIE;
			tx_buffer = NULL;
		}
	}
}
