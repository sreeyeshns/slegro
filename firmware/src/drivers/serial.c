#include <gpio.h>
#include <serial.h>
void UART0_init()
{
    PINSEL0 |= 0x05U;
    U0LCR = 0x83;
    U0DLM = 0x00;
    U0DLL = 0x62;
    U0LCR &= ~0x80;
}

void UART0_write_ch(uint8_t ch)
{
    while (!(U0LSR & 0x20));
    U0THR = ch;
    while (!(U0LSR & 0x40));
}
void UART0_write_str(int8_t *str)
{
    while (*str)
    {
        while (!(U0LSR & 0x20));
        U0THR = *str++;
    }
    while (!(U0LSR & 0x40));
}

uint8_t UART0_read()
{
    while (!(U0LSR & 0x01));
    return U0RBR;
}

