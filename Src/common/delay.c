#include "delay.h"
#include "stm32f4xx.h"

void delay_ms(uint32_t ms) {
    // 1. Program reload value (Assuming a 16 MHz internal HSI clock to get 1ms)
    // 16,000,000 Hz / 1000 = 16,000 clock cycles. LOAD is N-1, so 15999.
    SysTick->LOAD = 15999;

    // 2. Clear current value register
    SysTick->VAL = 0;

    // 3. Configure Control/Status register
    // Bit 2 (CLKSOURCE): 1 = Processor clock (AHB)
    // Bit 0 (ENABLE):    1 = Counter enabled
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    // 4. Loop for the specified number of milliseconds
    for (uint32_t i = 0; i < ms; i++) {
        // Wait until the COUNTFLAG (bit 16) is set to 1
        while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) {
            // Do nothing, just block
        }
    }

    // Optional: Disable SysTick when done to save power
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
