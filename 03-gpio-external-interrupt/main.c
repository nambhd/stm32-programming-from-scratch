#include <arm_compat.h>	/// Reference: https://developer.arm.com/documentation/ka004795/latest & https://github.com/ARM-software/CMSIS_5/releases/tag/5.8.0
#include "stm32f10x.h"
#include "gp_drive.h"

int signal = 0;

void delay(int delay);

int main(void)
{
	Init_GP(PA, 0, IN, I_PP);
	Init_GP(PC, 13, OUT10, O_GP_PP);
	Init_GP(PA, 12, OUT10, O_GP_PP);
	
	__disable_irq();
	AFIO->EXTICR[0] = 0x00;
	EXTI->IMR |= 1;
	EXTI->RTSR |= 1;
	NVIC_EnableIRQ(EXTI0_IRQn);
	__enable_irq();
	
	while(1)
	{
		Write_GP(PA, 12, signal);
		// Read pin PA0 and then toogle pin PC13 depend on PA0 pin state
		if (signal)
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

void EXTI0_IRQHandler()
{
	EXTI->PR |= 1;
	if (signal)
	{
		signal = 0;
	}
	else
	{
		signal = 1;
	}
}