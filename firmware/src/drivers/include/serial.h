#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>
#include <error.h>

#define U0RBR  (*(const volatile uint32_t *) 0xE000C000)
#define U0THR  (*(volatile uint32_t *) 0xE000C000)
#define U0DLL  (*(uint32_t *) 0xE000C000)
#define U0DLM  (*(uint32_t *) 0xE000C004)
#define U0LCR  (*(uint32_t *) 0xE000C00C)
#define U0LSR  (*(const volatile uint32_t *) 0xE000C014)
#define U0FDR  (*(uint32_t *) 0xE000C028)

/* ULCR register bits */
#define ULCR_BIT_WORD_LEN0       (0x01 << 0)
#define ULCR_BIT_WORD_LEN1       (0x01 << 1)
#define ULCR_BIT_STOP_BIT        (0x01 << 2)
#define ULCR_BIT_PARITY_ENABLE   (0x01 << 3)
#define ULCR_BIT_PARITY0         (0x01 << 4)
#define ULCR_BIT_PARITY1         (0x01 << 5)
#define ULCR_BIT_DLAB            (0x01 << 7)

typedef enum
{
   BAUD_RATE_1200    = 1200U,
   BAUD_RATE_2400    = 2400U,
   BAUD_RATE_4800    = 4800U,
   BAUD_RATE_9600    = 9600U,
   BAUD_RATE_19200   = 19200U,
   BAUD_RATE_38400   = 38400U,
   BAUD_RATE_57600   = 57600U,
   BAUD_RATE_115200  = 115200,
   BAUD_RATE_460800  = 460800U,
   BAUD_RATE_921600  = 921600U,
   BAUD_RATE_230400  = 230400U,

}uart_baud_rate_t;

typedef enum
{
   WORD_LENGTH_5,
   WORD_LENGTH_6,
   WORD_LENGTH_7,
   WORD_LENGTH_8
}uart_word_length_t;

typedef enum
{
   PARITY_ODD,
   PARITY_EVEN,
   PARITY_FORCED_1_STICK,
   PARITY_FORCED_0_STICK,
   PARITY_NONE
}uart_parity_t;

typedef enum
{
   STOP_BIT_1,
   STOP_BIT_2
}uart_stop_bits_t;

extern ret_code_t UART0_init(uart_baud_rate_t baud_rate, uart_word_length_t word_length, uart_parity_t parity, uart_stop_bits_t stop_bits);
extern uint8_t UART0_read(void);
extern void UART0_write_ch(uint8_t ch);
extern void UART0_write_str(int8_t *str);
extern int32_t UART0_write(uint8_t *buff, uint32_t size);
#endif
