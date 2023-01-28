#ifndef _GPIO_H
#define _GPIO_H
#include <stdint.h>
#include <common.h>

#define BIT_0                       0x0001UL
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
#define BIT_NONE                    0x0000UL
#define BIT_ALL                     0xFFFFUL

/* GPIOA Register mapping*/
struct
{
    /***** Port A configuration register low (GPIOA_CRL). Address offset: 0x00 *****/
    union
    {
        volatile uint32_t CRL;
        struct
        {
            volatile uint32_t MODE0  :2;
            volatile uint32_t CNF0   :2;
            volatile uint32_t        :28;
        }bits;
    }_CRL;
#define CRL                 _CRL.CRL
#define CRL_MODE0           _CRL.bits.MODE0
#define CRL_MODE0_50MHZ     3
#define CRL_CNF0            _CRL.bits.CNF0
#define CRL_CNF0_GPPP       0

    uint32_t unused1[3];   /* Skip the unused registers */

    /***** Port A bit set/reset register (GPIOA_BSRR). Address offset: 0x10 *****/
    union
    {
        volatile uint32_t BSRR;
        struct
        {
            volatile uint32_t BS     :16;
            volatile uint32_t BR     :16;
        }bits;
    }_BSRR;
#define BSRR                _BSRR.BSRR
#define BSRR_BS             _BSRR.bits.BS
#define BSRR_BR             _BSRR.bits.BR
}extern GPIOA;

typedef enum
{
    PORTA,
    PORTB
}gpio_port_t;

void gpio_init(void);
void gpio_write_bits(const gpio_port_t port, const uint16_t bits, const bit_state_t state);

#endif //_GPIO_H
