#include "stm32f10x.h"
#include "gp_drive.h"

unsigned long BRR_Calc(unsigned short usart, unsigned long br);
void UART_Init(unsigned short usart, unsigned long br);
char USART_RX(unsigned short usart);
void USART_TX(unsigned short usart, char c);
