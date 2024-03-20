#include "stm32f10x.h"
#include "gp_drive.h"
#include "usart_drive.h"

char c = 'A';

int main(void)
{
	UART_Init(2,9600);
	
	
	while(1)
	{
		// Receive message
		c = USART_RX(2);
		
		// Transmit message
		USART_TX(2, c);
	}
}
