#include <stdint.h>

#if defined(__x86_64__) || defined(_M_X64)

#define GPIOA_BASE      0x48000000
extern  uint32_t        GPIOA_MODER;
extern  uint32_t        GPIOA_IDR;
extern  uint32_t        GPIOA_ODR;

#else

#define RCC_BASE 0x40021000UL
#define GPIOA_BASE 0x48000000UL

//Offset

#define RCC_AHBENR_OFFSET 0x14
#define GPIOA_MODER_OFFSET 0x00
#define GPIOA_IDR_OFFSET 0x10     //Offset for Input
#define GPIOA_ODR_OFFSET 0x14     //Offset for Output

//Registers RCC and GPIO (GPIO register will be used to configure our pins)

#define RCC_AHBENR (*((volatile uint32_t *)(RCC_BASE + RCC_AHBENR_OFFSET)))

#define GPIOA_MODER (*((volatile uint32_t *)(GPIOA_BASE + GPIOA_MODER_OFFSET))) //Config I/O
#define GPIOA_IDR (*((volatile uint32_t *)(GPIOA_BASE + GPIOA_IDR_OFFSET)))     //Input
#define GPIOA_ODR (*((volatile uint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET)))     //Output

#endif

//Pins

#define LED1 1

//Functions

uint32_t Init_LED();
uint32_t delay(uint32_t ms);
uint32_t LED1_on();
uint32_t LED1_off();


