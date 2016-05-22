#ifndef _SERIAL_H
#define _SERIAL_H

#define U0RBR	(*(const volatile unsigned long *) 0xE000C000)
#define U0THR	(*(volatile unsigned long *) 0xE000C000)
#define U0DLL	(*(volatile unsigned long *) 0xE000C000)
#define U0DLM	(*(volatile unsigned long *) 0xE000C004)
#define U0LCR	(*(volatile unsigned long *) 0xE000C00C)
#define U0LSR	(*(const volatile unsigned long *) 0xE000C014)

void init_UART0(void);
extern unsigned char UART0_read(void);
extern void UART0_write_char(unsigned char ch);
extern void UART0_write_text(char *str);

#endif
