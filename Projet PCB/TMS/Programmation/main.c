#include <stdint.h>

#define RCC_BASE           0x40021000UL
#define GPIOA_BASE         0x48000000UL

#define RCC_AHBENR_OFFSET  0x14
#define GPIOA_MODER_OFFSET 0x00
#define GPIOA_ODR_OFFSET   0x14

#define RCC_AHBENR (*((volatile uint32_t *)(RCC_BASE + RCC_AHBENR_OFFSET)))
#define GPIOA_MODER (*((volatile uint32_t *)(GPIOA_BASE + GPIOA_MODER_OFFSET)))
#define GPIOA_ODR   (*((volatile uint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET)))

#define LED_PIN (1U << 0)

void delay(uint32_t ms) {
    // This delay function is not precise and depends on the clock frequency
    // Adjust it according to your system clock
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 2000; j++) {
            // Adding some assembly code here could make it more accurate
            asm("NOP");
        }
    }
}

int main(void) {
    // Enable GPIOA peripheral clock
    RCC_AHBENR |= (1U << 17); // Bit 17 corresponds to GPIOA

    // Configure PA0 as output
    GPIOA_MODER |= (1U << 0); // Set pin 0 to output mode

    while (1) {
        // Toggle the LED
        GPIOA_ODR ^= LED_PIN;
        // Insert some delay
        delay(100); // Delay for 1 second
    }
}
