#include "stm32f10x.h"
#include "gp_drive.h"
#include "usart_drive.h"
#include "delay.h"

char c = 'A';
char msg[30] = "Hello, World!!!";;

char USART1_msg[250];
char USART2_msg[250];
char USART3_msg[250];

unsigned short USART1_bridge = 0;
unsigned short USART1_signal = 0;
unsigned short USART1_counter = 0;

unsigned short USART2_bridge = 0;
unsigned short USART2_signal = 0;
unsigned short USART2_counter = 0;

unsigned short USART3_bridge = 0;
unsigned short USART3_signal = 0;
unsigned short USART3_counter = 0;

int main(void)
{
	UART_Init(2,9600);
	UART_Init(2,9600);
	
	// Transmit a string
	USART_Send(2, msg);
	USART_Send(3, msg);
	
	while(1)
	{
		// Receive message
		//c = USART_RX(2);
		
		// Transmit message
		//USART_TX(2, c);
		
		if (USART2_signal == 1)
		{
			USART_Send(3, USART2_msg);
			USART2_signal = 0;
			str_empty(USART2_msg);
		}
		
		if (USART3_signal == 1)
		{
			USART_Send(2, USART3_msg);
			USART3_signal = 0;
			str_empty(USART3_msg);
		}
	}
}

void USART2_IRQHandler()
{
	USART(2, USART2_bridge, &USART2_signal, &USART2_counter, USART2_msg);
}

void USART3_IRQHandler()
{
	USART(3, USART3_bridge, &USART3_signal, &USART3_counter, USART3_msg);
}
