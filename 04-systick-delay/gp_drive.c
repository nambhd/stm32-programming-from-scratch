#include "gp_drive.h"

void Init_GP(unsigned short port, unsigned short pin, unsigned dir, unsigned short opt)
{
	volatile unsigned long * CR;
	unsigned short tPin = pin;
	unsigned short offset = 0;
	
	if (pin > 7)
	{
		tPin -= 8;
		offset = 1;
	}
	
	switch (port)
	{
		case PA:
			RCC_APB2ENR |= 0x04<<0;
			CR = (volatile unsigned long *) (&GPIO_A + offset);
			break;
		
		case PB:
			RCC_APB2ENR |= 0x04<<1;
			CR = (volatile unsigned long *) (&GPIO_B + offset);
			break;
		
		case PC:
			RCC_APB2ENR |= 0x04<<2;
			CR = (volatile unsigned long *) (&GPIO_C + offset);
			break;
	}
	
	// Reset the target pin
	*CR &= ~(0xF<<(tPin)*4);
	
	// Setup the direction & option of the pin
	*CR |= (dir<<(tPin*4) | (opt<<(tPin*4+2)));
}

int Read_GP(unsigned short port, unsigned short pin)
{
	volatile unsigned long * IDR;
	unsigned short offset = 0x02;
	
	switch (port)
	{
		case PA:
			IDR = (volatile unsigned long *) (&GPIO_A + offset);
			break;
		
		case PB:
			IDR = (volatile unsigned long *) (&GPIO_B + offset);
			break;
		
		case PC:
			IDR = (volatile unsigned long *) (&GPIO_C + offset);
			break;
	}
	
	return ((*IDR & (1<<pin))>>pin);
}

void Write_GP(unsigned short port, unsigned short pin, unsigned short state)
{
	volatile unsigned long * ODR;
	unsigned short offset = 0x03;
	
	switch (port)
	{
		case PA:
			ODR = (volatile unsigned long *) (&GPIO_A + offset);
			break;
		
		case PB:
			ODR = (volatile unsigned long *) (&GPIO_B + offset);
			break;
		
		case PC:
			ODR = (volatile unsigned long *) (&GPIO_C + offset);
			break;
	}
	
	state ? (*ODR |= (state<<pin)) : (*ODR &= ~(1<<pin));
}

void Toggle_GP(unsigned short port, unsigned short pin)
{
	if (Read_GP(port, pin))
	{
		Write_GP(port, pin, LOW);
	}
	else
	{
		Write_GP(port, pin, HIGH);
	}
}