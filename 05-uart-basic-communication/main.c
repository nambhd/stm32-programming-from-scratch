#include "stm32f10x.h"
#include "gp_drive.h"

char letter = 'A';

int main(void)
{
	//------Init UART2
	// Alternate function I/O clock enable
	RCC->APB2ENR |= 1;
	
	// UART2 clock enable
	RCC->APB1ENR |= 0x200000;
	
	// Init the related PINs
	Init_GP(PA, 3, IN, I_PP);
	Init_GP(PA, 2, OUT50, O_AF_PP);
	
	// Set baude rate
	USART2->BRR = 0xEA6;
	
	// Transmitter enable
	USART2->CR1 |= 4;
	
	// Receiver enable
	USART2->CR1 |= 2;
	
	// USART enable
	USART2->CR1 |= 0x2000;
	
	while(1)
	{
		// Receive message
		while((USART2->SR & 0x20) == 0x00);
		letter = USART2->DR;
		
		// Transmit message
		while((USART2->SR & 0x80) == 0x80);
		USART2->DR = letter;
	}
}