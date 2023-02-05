#ifndef _SYSCLK_H
#define _SYSCLK_H
#include <stdint.h>

#define PCLK1       36000000 /* APB1 clock frequency 36Mhz */
#define PCLK2       72000000 /* APB2 clock frequency 72Mhz */

#define RCC         ((RCC_Type)0x40021000)

/* RCC Register mapping*/
typedef struct
{
    /***** Clock control register (RCC_CR). Address offset: 0x00 *****/
    union
    {
        volatile uint32_t CR;
        struct
        {
            volatile uint32_t        :16;
            volatile uint32_t HSEON  :1;
            volatile uint32_t HSERDY :1;
            volatile uint32_t        :6;
            volatile uint32_t PLLON  :1;
            volatile uint32_t PLLRDY :1;
            volatile uint32_t        :6;
        }bits;
    }_CR;
#define CR              _CR.CR
#define CR_HSEON        _CR.bits.HSEON
#define CR_HSERDY       _CR.bits.HSERDY
#define CR_PLLON        _CR.bits.PLLON
#define CR_PLLRDY       _CR.bits.PLLRDY

    /***** Clock configuration register (RCC_CFGR). Address offset: 0x04 *****/
    union
    {
        volatile uint32_t CFGR;
        struct
        {
            volatile uint32_t SW     :2;
            volatile uint32_t SWS    :2;
            volatile uint32_t        :4;
            volatile uint32_t PPRE1  :3;
            volatile uint32_t        :5;
            volatile uint32_t PLLSRC :1;
            volatile uint32_t        :1;
            volatile uint32_t PLLMUL :4;
            volatile uint32_t        :10;
        }bits;
    }_CFGR;
#define CFGR                _CFGR.CFGR
#define CFGR_SW             _CFGR.bits.SW
#define RCC_CFGR_SW_PLL     2
#define CFGR_SWS            _CFGR.bits.SWS
#define CFGR_PPRE1          _CFGR.bits.PPRE1
#define RCC_CFGR_PPRE1_2    4
#define CFGR_PLLSRC         _CFGR.bits.PLLSRC
#define RCC_CFGR_PLLSRC_HSE 1
#define CFGR_PLLMUL         _CFGR.bits.PLLMUL
#define RCC_CFGR_PLLMUL_9   7

    uint32_t unused1[4];   /* Skip the unused registers */

    /***** APB2 peripheral clock enable register (RCC_APB2ENR). Address offset: 0x18 *****/
    union
    {
        volatile uint32_t APB2ENR;
        struct
        {
            volatile uint32_t           :2;
            volatile uint32_t IOPAEN    :1;
            volatile uint32_t           :11;
            volatile uint32_t USART1EN  :1;
            volatile uint32_t           :17;
        }bits;
    }_APB2ENR;
#define APB2ENR                _APB2ENR.APB2ENR
#define APB2ENR_IOPAEN         _APB2ENR.bits.IOPAEN
#define APB2ENR_USART1EN       _APB2ENR.bits.USART1EN
}*RCC_Type;

/*
 * Initializes the PLL module and multiplies the clock frequency so that
 * the CPU runs at 72Mhz
 */
void SystemInit(void);

#endif /* _SYSCLK_H */
