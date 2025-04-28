#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE  (4U * 1024U)            /* 4 kb       */
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))
#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void);
void NMI_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SVCall(void)       __attribute__ ((weak, alias("Default_Handler")));
void PendSV(void)       __attribute__ ((weak, alias("Default_Handler")));
void SysTick(void)       __attribute__ ((weak, alias("Default_Handler")));
void WWDG(void)       __attribute__ ((weak, alias("Default_Handler")));
void RTC(void)       __attribute__ ((weak, alias("Default_Handler")));
void FLASH(void)       __attribute__ ((weak, alias("Default_Handler")));
void RCC(void)       __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_1(void)       __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_3(void)       __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_15(void)       __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH1(void)       __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH2_3(void)       __attribute__ ((weak, alias("Default_Handler")));
void DMA_CH4_5(void)       __attribute__ ((weak, alias("Default_Handler")));
void ADC(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_UP_TRG_COM(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM3(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM6(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM14(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM15(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM16(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM17(void)       __attribute__ ((weak, alias("Default_Handler")));
void I2C1(void)       __attribute__ ((weak, alias("Default_Handler")));
void I2C2(void)       __attribute__ ((weak, alias("Default_Handler")));
void SPI1(void)       __attribute__ ((weak, alias("Default_Handler")));
void SPI2(void)       __attribute__ ((weak, alias("Default_Handler")));
void USART1(void)       __attribute__ ((weak, alias("Default_Handler")));
void USART2(void)       __attribute__ ((weak, alias("Default_Handler")));
void USART3_4_5_6(void)       __attribute__ ((weak, alias("Default_Handler")));
void USB(void)       __attribute__ ((weak, alias("Default_Handler")));


uint32_t vectors[] __attribute__ ((section(".arm_vector")))={
    STACK_START,
    (uint32_t) &Reset_Handler,
    (uint32_t) &NMI_Handler,
    (uint32_t) &HardFault_Handler,
    (uint32_t) &SVCall,
    (uint32_t) &PendSV,
    (uint32_t) &SysTick,
    (uint32_t) &WWDG,
    0,
    (uint32_t) &RTC,
    (uint32_t) &FLASH,
    (uint32_t) &RCC,
    (uint32_t) &EXTI0_1,
    (uint32_t) &EXTI2_3,
    (uint32_t) &EXTI4_15,
    0,
    (uint32_t) &DMA_CH1,
    (uint32_t) &DMA_CH2_3,
    (uint32_t) &DMA_CH4_5,
    (uint32_t) &ADC,
    (uint32_t) &TIM1_BRK_UP_TRG_COM,
    (uint32_t) &TIM1_CC,
    0,
    (uint32_t) &TIM3,
    (uint32_t) &TIM6,
    0,
    (uint32_t) &TIM14,
    (uint32_t) &TIM15,
    (uint32_t) &TIM16,
    (uint32_t) &TIM17,
    (uint32_t) &I2C1,
    (uint32_t) &I2C2,
    (uint32_t) &SPI1,
    (uint32_t) &SPI2,
    (uint32_t) &USART1,
    (uint32_t) &USART2,
    (uint32_t) &USART3_4_5_6,
    0,
    (uint32_t) &USB,
}; 

void Reset_Handler(void) {
	//copy .data section to SRAM
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	
	uint8_t *pDst = (uint8_t*)&_sdata; //sram
	uint8_t *pSrc = (uint8_t*)&_la_data; //flash
	
	for(uint32_t i =0 ; i < size ; i++)
	{
		*pDst++ = *pSrc++;
	}
	
	//Init. the .bss section to zero in SRAM
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	pDst = (uint8_t*)&_sbss;
	for(uint32_t i =0 ; i < size ; i++)
	{
		*pDst++ = 0;
	}

	//__libc_init_array();
	
	main();
}

void Default_Handler(void) {
    while (1);
}
