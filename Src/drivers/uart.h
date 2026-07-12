#ifndef UART_H
#define UART_H
#include "stm32f4xx.h"

void uart_init(GPIO_TypeDef *GPIOx);

void uart_send_char_polling(char c);
void uart_send_string_polling(char* str);

void uart_send_str(char* str);

#endif
