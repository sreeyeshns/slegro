#ifndef _GPIO_H
#define _GPIO_H
#include <stdint.h>

#define GPIOA_BASE                  0x40010800UL
#define GPIOA_CRL                   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_CRL_MODE0             0x00000003
#define GPIOA_CRL_CNF0              0x0000000C

#define GPIOA_BSRR                  (*(volatile uint32_t *)(GPIOA_BASE + 0x10))
#define GPIOA_BSRR_BS0              0x00000001
#define GPIOA_BSRR_BR0              0x00010000

#define BIT_0                       0x00000001UL
#define BIT_1                       (BIT_0 << 1)
#define BIT_2                       (BIT_1 << 1)
#define BIT_3                       (BIT_2 << 1)
#define BIT_4                       (BIT_3 << 1)
#define BIT_5                       (BIT_4 << 1)
#define BIT_6                       (BIT_5 << 1)
#define BIT_7                       (BIT_6 << 1)
#define BIT_8                       (BIT_7 << 1)
#define BIT_9                       (BIT_8 << 1)
#define BIT_10                      (BIT_9 << 1)
#define BIT_11                      (BIT_10 << 1)
#define BIT_12                      (BIT_11 << 1)
#define BIT_13                      (BIT_12 << 1)
#define BIT_14                      (BIT_13 << 1)
#define BIT_15                      (BIT_14 << 1)

typedef enum
{
    BIT_CLEAR,
    BIT_SET
}bit_state_t;

typedef enum
{
    PORTA,
    PORTB
}gpio_port_t;

void gpio_init(void);
void gpio_write_bits(const gpio_port_t port, const uint16_t bits, const bit_state_t state);

#endif //_GPIO_H
