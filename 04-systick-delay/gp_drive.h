#define RCC_APB2ENR			(*((volatile unsigned long *) 0x40021018))

// GPIO Ports
#define GPIO_A					(*((volatile unsigned long *) 0x40010800))
#define GPIO_B					(*((volatile unsigned long *) 0x40010C00))
#define GPIO_C					(*((volatile unsigned long *) 0x40011000))
#define GPIO_D					(*((volatile unsigned long *) 0x40011400))
#define GPIO_E					(*((volatile unsigned long *) 0x40011800))
#define GPIO_F					(*((volatile unsigned long *) 0x40011C00))
#define GPIO_G					(*((volatile unsigned long *) 0x40012000))

#define PA							1
#define PB							2
#define PC							3

// Directoins (Port mode)
#define IN							0
#define OUT10						1
#define OUT02						2
#define OUT50						3

// Options for Input mode
#define I_AN						0
#define I_FL						1
#define I_PP						2

// Options for Output mode
#define O_GP_PP					0
#define O_GP_OD					1
#define O_AF_PP					2
#define O_AF_OD					3

// State
#define LOW							0
#define HIGH						1

void Init_GP(unsigned short port, unsigned short pin, unsigned dir, unsigned short opt);

int Read_GP(unsigned short port, unsigned short pin);

void Write_GP(unsigned short port, unsigned short pin, unsigned short state);

void Toggle_GP(unsigned short port, unsigned short pin);
