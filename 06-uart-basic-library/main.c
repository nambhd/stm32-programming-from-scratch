#include "stm32f10x.h"
#include "gp_drive.h"
#include "usart_drive.h"
#include "delay.h"

char c = 'A';
char msg[30] = "Hello, World!!!";;

int main(void)
{
	UART_Init(2,9600);
	
	// Transmit a string
	USART_Send(2, msg);
	
	while(1)
	{
		// Receive message
		c = USART_RX(2);
		
		// Transmit message
		USART_TX(2, c);
	}
}

