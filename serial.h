#ifndef _SERIAL_H
#define _SERIAL_H

#define U0RBR   (*(const volatile uint32_t *) 0xE000C000)
#define U0THR   (*(volatile uint32_t *) 0xE000C000)
#define U0DLL   (*(volatile uint32_t *) 0xE000C000)
#define U0DLM   (*(volatile uint32_t *) 0xE000C004)
#define U0LCR   (*(volatile uint32_t *) 0xE000C00C)
#define U0LSR   (*(const volatile uint32_t *) 0xE000C014)

void UART0_init(void);
extern uint8_t UART0_read(void);
extern void UART0_write_ch(uint8_t ch);
extern void UART0_write_str(int8_t *str);

#endif
