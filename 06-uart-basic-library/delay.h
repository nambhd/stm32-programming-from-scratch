#include "stm32f10x.h"

void SysTick_Init(void);

void SysTick_Delay(unsigned int miliseconds);

void SysTick_Delay_us(unsigned int microseconds);

void SysTick_Interrupt_Start(void);

void SysTick_Interrupt(unsigned short usart1_mng[], unsigned short usart2_mng[], unsigned short usart3_mng[]);
