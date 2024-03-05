#include "stm32f10x.h"

void delay(int delay);

int main(void)
{
	// Port I/O C clock enable
	RCC->APB2ENR |= 0x00000010; // 0b10000
	
	// Port configuration register high
	// Reset Value: 0x4444 4444 = 0b 0100 0100 0100 0100 0100 0100 0100 0100
	// PC13 -> Output push-pull:  0b 0000 0000 0001 0000 0000 0000 0000 0000 = 0x00100000
	GPIOC->CRH &= 0xFF0FFFFF; // 0b 1111 1111 0000 1111 ...	
	GPIOC->CRH |= 0x00100000; // 0b 0000 0000 0011 0000 ....
	
	while(1)
	{
		// Toogle PC13 using ODR (Port output data register)
		GPIOC->ODR |= 0x2000;
		delay(1000);
		
		GPIOC->ODR &= ~0x2000;
		delay(1000);
	}
}

void delay(int delay)
{
	for (int i = 0; i < delay; i++)
		for (int j = 0; j < 1000; j++);
}
