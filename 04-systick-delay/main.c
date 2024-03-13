#include "stm32f10x.h"
#include "gp_drive.h"

const int HCLK = 108000000;
volatile uint32_t time_delay;

void delay(int delay);
void SysTick_Init(void);
void SysTick_Delay_ms(uint32_t miliseconds);

int main(void)
{
	Init_GP(PC, 13, OUT10, O_GP_PP);
	SysTick_Init();
	
	while(1)
	{
		Toggle_GP(PC, 13);
		SysTick_Delay_ms(1000);
	}
}

void delay(int delay)
{
	for (int i=0; i<delay; i++)
		for (int j=0; j<1000; j++);
}

// Interrupt period 1ms = HCLK / 1000 (T)
void SysTick_Init(void)
{
	
	SysTick->LOAD = (HCLK / 1000) - 1; // Maximum value is 0x00FF.FFFF
	SysTick->VAL = 0;
	SysTick->CTRL = 7; //0101 -> Set CTRL_CLKSOURCE = processor clock; CTRL_TICKINT = 1; CTRL_ENABLE = 1
}

void SysTick_Handler(void)
{
	if (time_delay > 0)
	{
		time_delay--;
	}
}

void SysTick_Delay_ms(uint32_t miliseconds)
{
	time_delay = miliseconds;
	while(time_delay != 0);
}