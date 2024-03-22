#include "delay.h"

void SysTick_Init(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
}

void SysTick_Delay(unsigned int miliseconds)
{
	SysTick->LOAD = (108000000 / 1000) * miliseconds - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	while((SysTick->CTRL & 1<<16) == 0);
}

void SysTick_Delay_us(unsigned int microseconds)
{
	SysTick->LOAD = (108000000 / 1000000) * microseconds - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 5;
	while((SysTick->CTRL & 1<<16) == 0);
}

void SysTick_Interrupt_Start(void)
{
	SysTick->CTRL = 0;
	SysTick->LOAD = 108000 - 1;
	SysTick->VAL = 0;
	SysTick->CTRL |= 7;
}

void SysTick_Interrupt(unsigned short usart1_mng[], unsigned short usart2_mng[], unsigned short usart3_mng[])
{
	if (usart1_mng[0] != 0)
	{
		if (usart1_mng[6] == 0)
		{
			usart1_mng[0] = 0;
			usart1_mng[1] = 1;
			SysTick_Init();
		}
		else 
		{
			usart1_mng[6]--;
		}
	}
	else if (usart2_mng[0] != 0)
	{
		if (usart2_mng[6] == 0)
		{
			usart2_mng[0] = 0;
			usart2_mng[1] = 1;
			SysTick_Init();
		}
		else 
		{
			usart2_mng[6]--;
		}
	}
	else if (usart3_mng[0] != 0)
	{
		if (usart3_mng[6] == 0)
		{
			usart3_mng[0] = 0;
			usart3_mng[1] = 1;
			SysTick_Init();
		}
		else 
		{
			usart3_mng[6]--;
		}
	}
}