#include "functions.h"

#if defined(__x86_64__) || defined(_M_X64)
//Pour differencier la mémoire du PC et celle de la board

uint32_t GPIOA_MODER = (GPIOA_BASE + 0x00);
uint32_t GPIOA_IDR = (GPIOA_BASE + 0x10);
uint32_t GPIOA_ODR = (GPIOA_BASE + 0x14);

#endif

uint32_t Init_LED()
{
  GPIOA_MODER |= ( 1 << ( LED1 * 2 ));
  return GPIOA_MODER;
}

uint32_t delay(uint32_t ms)
{
  for (uint32_t i = 0; i < ms; i++) {
    for (uint32_t j = 0; j < 2000; j++) {
      asm("NOP");
    }
  }
  return ms;
}

uint32_t LED1_on()
{
  GPIOA_ODR |= ( 1UL << LED1 );  //Set LED1 bit to 1 on GPIO
  return GPIOA_ODR;
}

uint32_t LED1_off()
{
  GPIOA_ODR &= ~( 1UL << LED1 ); //Set LED1 bit to 0 on GPIO
  return GPIOA_ODR;
}
