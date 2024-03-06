#include "stm32f10x.h"

void delay(int delay);

int main(void)
{
	// Clock enable for Port A
	RCC->APB2ENR |= 0x04;
	
	// Config PA0 as Input with pull-up/pull-down
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x00000008;
	
	// Clock enable for Port C
	RCC->APB2ENR |= 0x10;
	
	// Config PA13 as Output push-pull
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00100000;
	
	while(1)
	{
		// Read pin PA0 and then toogle pin PC13 depend on PA0 pin state
		if ((GPIOA->IDR & 0x00000001) == 0)
		{
			GPIOC->ODR |= 0x00002000;
		}
		else
		{
			GPIOC->ODR &= ~0x00002000;
		}
		delay(1000);
	}
}

void delay(int delay)
{
	for (int i=0; i<delay; i++)
		for (int j=0; j<1000; j++);
}