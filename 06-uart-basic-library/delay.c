#include "delay.h"

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
