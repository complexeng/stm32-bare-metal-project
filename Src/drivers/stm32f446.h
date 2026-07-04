#ifndef STM32F446_H
#define STM32F446_H
#include <stdint.h>

// --------- RCC ---------- //
typedef struct {
    volatile uint32_t CR;         // 0x00: Clock control register
    volatile uint32_t PLLCFGR;    // 0x04: PLL configuration register
    volatile uint32_t CFGR;       // 0x08: Clock configuration register
    volatile uint32_t CIR;        // 0x0C: Clock interrupt register
    volatile uint32_t AHB1RSTR;   // 0x10: AHB1 peripheral reset register
    volatile uint32_t AHB2RSTR;   // 0x14: AHB2 peripheral reset register
    volatile uint32_t AHB3RSTR;   // 0x18: AHB3 peripheral reset register
    uint32_t RESERVED0;           // 0x1C: Reserved memory space
    volatile uint32_t APB1RSTR;   // 0x20: APB1 peripheral reset register
    volatile uint32_t APB2RSTR;   // 0x24: APB2 peripheral reset register
    uint32_t RESERVED1[2];        // 0x28 - 0x2C: Reserved memory space
    volatile uint32_t AHB1ENR;    // 0x30: AHB1 peripheral clock enable register
    volatile uint32_t AHB2ENR;    // 0x34: AHB2 peripheral clock enable register
    volatile uint32_t AHB3ENR;    // 0x38: AHB3 peripheral clock enable register
    uint32_t RESERVED2;           // 0x3C: Reserved memory space
    volatile uint32_t APB1ENR;    // 0x40: APB1 peripheral clock enable register
    volatile uint32_t APB2ENR;    // 0x44: APB2 peripheral clock enable register
} RCC_TypeDef;

#define RCC_BASE        0x40023800U
#define RCC             ((RCC_TypeDef *) RCC_BASE)

// ------ GPIO -------- //
typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIO_TypeDef;

#define GPIOA_BASE 		0x40020000U
#define GPIOA			((GPIO_TypeDef *) GPIOA_BASE)

// --- System Timer (SysTick) ---
typedef struct {
    volatile uint32_t STK_CTRL;   // Offset 0x00: Control and Status Register
    volatile uint32_t STK_LOAD;   // Offset 0x04: Reload Value Register
    volatile uint32_t STK_VAL;    // Offset 0x08: Current Value Register
    volatile uint32_t STK_CALIB;  // Offset 0x0C: Calibration Value Register
} SysTick_TypeDef;

#define SYSTICK_BASE     0xE000E010U
#define SYSTICK          ((SysTick_TypeDef *) SYSTICK_BASE)

#endif // STM32F446_H
