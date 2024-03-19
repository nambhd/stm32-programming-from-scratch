#include "stm32f10x.h"
#include "gp_drive.h"
#include "usart_drive.h"

char letter = 'A';

int main(void)
{
	UART_Init(2,9600);
	
	
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
