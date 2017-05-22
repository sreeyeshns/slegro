#include <gpio.h>
#include <serial.h>
void init_UART0()
{
	PINSEL0 |= 0x05U;
	U0LCR	= 0x83;
	U0DLM	= 0x00;
	U0DLL	= 0x62;
	U0LCR	&= ~0x80;
}

void UART0_write_char(unsigned char ch)
{
	while(!(U0LSR & 0x20));
	U0THR	= ch;
	while(!(U0LSR & 0x20));
}
void UART0_write_text(char *str)
{
	while(*str)
	{
		UART0_write_char(*str++);
	}
}

unsigned char UART0_read()
{
	while(!(U0LSR & 0x01));
	return U0RBR;
}

