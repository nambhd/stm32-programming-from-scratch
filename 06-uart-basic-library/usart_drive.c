#include "usart_drive.h"

unsigned long BRR_Calc(unsigned short usart, unsigned long br)
{
	unsigned long div = 54000000;
	unsigned long dec;
	unsigned long final;
	
	double frac = 54000000.00;
	double frac2 = 1.0;
	
	if (usart == 1)
	{
		div = 108000000;
		frac = 108000000.00;
	}
	
	div = div / (br * 16);
	frac = 16*((frac / (br * 16)) - div);
	dec = frac;
	
	frac2 = 100*(frac - dec);
	
	if (frac2 > 50)
	{
		dec++;
		if (dec == 16)
		{
			dec = 0;
			div++;
		}
	}
	
	final = (div<<4);
	final += dec;
	
	return final;
	/*
	unsigned long fPclk = 36000000;
	unsigned long divMantissa;
	unsigned long divFractionDec;
	double fPclkDouble = 36000000.00;
	double divFraction;
	
	if (usart == 1)
	{
		fPclk = 72000000;
		fPclkDouble = 72000000.00;
	}
	
	divMantissa = fPclk / (br * 16);
	divFraction = (fPclkDouble / (br * 16) - divMantissa) * 16;
	
	divFractionDec = (unsigned long)divFraction;
	if ((divFraction - divFractionDec)*100 > 50)
	{
		divFractionDec += 1;
		if (divFractionDec == 16)
		{
			divFractionDec = 0;
			divMantissa +=1;
		}
	}
	
	return (divMantissa<<4) + divFractionDec;
	*/
}

void UART_Init(unsigned short usart, unsigned long br)
{
	//------Init USART
	// Alternate function I/O clock enable
	RCC->APB2ENR |= 1;
	
	unsigned long brrCalc = BRR_Calc(usart, br);
	
	if (usart == 1)
	{
		// USART1 clock enable
		RCC->APB2ENR |= 0x4000;
		
		// Init the related PINs
		Init_GP(PA, 10, IN, I_PP);
		Init_GP(PA, 9, OUT50, O_AF_PP);
		
		// Set baude rate
		USART1->BRR = brrCalc;
		
		// Transmitter enable
		USART1->CR1 |= 4;
		
		// Receiver enable
		USART1->CR1 |= 2;
		
		// USSART enable
		USART1->CR1 |= 0x2000;
		
		// RXNE interrupt enable
		USART1->CR1 |= 0x20;
		NVIC_EnableIRQ(USART1_IRQn);
	}
	else if (usart == 2)
	{
		// USART2 clock enable
		RCC->APB1ENR |= 0x20000;
		
		// Init the related PINs
		Init_GP(PA, 3, IN, I_PP);
		Init_GP(PA, 2, OUT50, O_AF_PP);
		
		// Set baude rate
		USART2->BRR = BRR_Calc(usart, br);
		
		// Transmitter enable
		USART2->CR1 |= 8;
		
		// Receiver enable
		USART2->CR1 |= 4;
		
		// USSART enable
		USART2->CR1 |= 0x2000;
		
		// RXNE interrupt enable
		USART1->CR1 |= 0x20;
		NVIC_EnableIRQ(USART1_IRQn);
	}
	else if (usart == 3)
	{
		// USART3 clock enable
		RCC->APB1ENR |= 0x40000;
		
		// Init the related PINs
		Init_GP(PB, 11, IN, I_PP);
		Init_GP(PB, 10, OUT50, O_AF_PP);
		
		// Set baude rate
		USART3->BRR = BRR_Calc(usart, br);
		
		// Transmitter enable
		USART3->CR1 |= 8;
		
		// Receiver enable
		USART3->CR1 |= 4;
		
		// USSART enable
		USART3->CR1 |= 0x2000;
		
		// RXNE interrupt enable
		USART1->CR1 |= 0x20;
		NVIC_EnableIRQ(USART1_IRQn);
	}
}

char USART_RX(unsigned short usart)
{
	char c;
	if (usart == 1)
	{
		while((USART1->SR & 0x20) == 0x00);
		c = USART1->DR;
	}
	else if (usart == 2)
	{
		while((USART2->SR & 0x20) == 0x00);
		c = USART2->DR;
	}
	else if (usart == 3)
	{
		while((USART3->SR & 0x20) == 0x00);
		c = USART3->DR;
	}
	
	return c;
}

void USART_TX(unsigned short usart, char c)
{
	if (usart == 1)
	{
		while((USART1->SR & 0x80) == 0x00);
		USART1->DR = c;
	}
	else if (usart == 2)
	{
		while((USART2->SR & 0x80) == 0x00);
		USART2->DR = c;
	}
	else if (usart == 3)
	{
		while((USART3->SR & 0x80) == 0x00);
		USART3->DR = c;
	}
}

void USART_Send(unsigned short usart, char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		USART_TX(usart, str[i]);
		i++;
	}
}

void USART(unsigned short usart, unsigned short bridge, unsigned short * signal, unsigned short * counter, char str[])
{
	if (bridge == 0)
	{
		str[*counter] = USART_RX(usart);
		if (str[*counter] == '\n')
		{
			*counter = 0;
			*signal = 1;
		}
		else
		{
			*counter = *counter + 1;
		}
	}
	else
	{
		USART_TX(usart, USART_RX(usart));
	}
}

void str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
}