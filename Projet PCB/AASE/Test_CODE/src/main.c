#include <stdint.h>
#include "functions.h"


int main(void)
{
  RCC_AHBENR |= (1 << 17); //Enable clock
  Init_LED(); // Set LEDs pins on output
  while(1) //LED1 and LED2 blink
    {
      LED1_on();
      delay(1000);
      LED1_off();
      delay(1000);
    }
  return 0;
}
