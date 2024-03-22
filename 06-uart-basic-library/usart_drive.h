#include "stm32f10x.h"
#include "gp_drive.h"
#include "delay.h"

unsigned long BRR_Calc(unsigned short usart, unsigned long br);
void UART_Init(unsigned short usart, unsigned long br);
char USART_RX(unsigned short usart);
void USART_TX(unsigned short usart, char c);
void USART_Send(unsigned short usart, char str[]);
void USART_ISR(unsigned short usart, unsigned short usart_mng[], char str[]);
void str_empty(char str[]);
