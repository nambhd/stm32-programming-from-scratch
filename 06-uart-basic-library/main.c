#include "stm32f10x.h"
#include "gp_drive.h"
#include "usart_drive.h"
#include "delay.h"

char USART1_msg[250];
char USART2_msg[250];
char USART3_msg[250];

/*
UART Manager
0 - count
1 - signal
2 - bridge
3 - terminator or interrupt: 1-Terminator/0-Interrupt
4 - terminator char
5 -  time cst
6 - timer counter
*/
/*
unsigned short USART1_bridge = 0;
unsigned short USART1_signal = 0;
unsigned short USART1_counter = 0;*/

unsigned short usart1_mng[7] = {0,0,0,0,0,0,0};

unsigned short USART2_bridge = 0;
unsigned short USART2_signal = 0;
unsigned short USART2_counter = 0;
unsigned short usart2_mng[7] = {0,0,0,0,'0',0,0};

unsigned short USART3_bridge = 0;
unsigned short USART3_signal = 0;
unsigned short USART3_counter = 0;
unsigned short usart3_mng[7] = {0,0,0,0,'0',0,0};

int main(void)
{
	UART_Init(2,9600);
	UART_Init(2,9600);
	
	// Transmit a string
	USART_Send(2, "This is UART 2");
	USART_Send(3, "This is UART 3");
	
	while(1)
	{
		// Receive message
		//c = USART_RX(2);
		
		// Transmit message
		//USART_TX(2, c);
		
		if (usart2_mng[1] == 1)
		{
			USART_Send(3, USART2_msg);
			usart2_mng[1] = 0;
			str_empty(USART2_msg);
		}
		
		if (usart3_mng[1] == 1)
		{
			USART_Send(2, USART3_msg);
			usart3_mng[1] = 0;
			str_empty(USART3_msg);
		}
	}
}

void USART2_IRQHandler()
{
	USART_ISR(2, usart2_mng, USART2_msg);
}

void USART3_IRQHandler()
{
	USART_ISR(3, usart3_mng, USART3_msg);
}

void SysTick_Handler(void)
{
	SysTick_Interrupt(usart1_mng, usart2_mng, usart3_mng);
}
