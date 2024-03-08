#include "stm32f10x.h"
#include "gp_drive.h"

void delay(int delay);

int main(void)
{
	/*// Clock enable for Port A
	RCC_APB2ENR |= 0x04;
	
	// Config PA0 as Input with pull-up/pull-down
	GPIOA->CRL &= 0xFFFFFFF0;
	GPIOA->CRL |= 0x00000008;
	
	// Clock enable for Port C
	RCC_APB2ENR |= 0x10;
	
	// Config PA13 as Output push-pull
	GPIOC->CRH &= 0xFF0FFFFF;
	GPIOC->CRH |= 0x00100000;
	*/
	Init_GP(PA, 0, IN, I_PP);
	Init_GP(PC, 13, OUT10, O_GP_PP);
	while(1)
	{
		// Read pin PA0 and then toogle pin PC13 depend on PA0 pin state
		if (Read_GP(PA, 0) == 1)
		{
			Toggle_GP(PC, 13);
		}
		else
		{
			Write_GP(PC, 13, HIGH);
		}
		delay(1000);
	}
}

void delay(int delay)
{
	for (int i=0; i<delay; i++)
		for (int j=0; j<1000; j++);
}