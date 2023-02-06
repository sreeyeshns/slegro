#include <common.h>
#include <sysclk.h>
#include <gpio.h>

static void PORTA_Config()
{
    /* Enable APB2 clock for PORT A */
    RCC->APB2ENR_IOPAEN = BIT_SET;

    /* Configure pin 0 of PORT A for gpio output*/
    GPIOA->CRL_MODE0 = GPIO_MODE_50MHZ;
    GPIOA->CRL_CNF0 = GPIO_CNF_GPOPP;

    /* Enable pin 9 and 10 for USART Tx and Rx function */
    GPIOA->CRH_MODE9 = GPIO_MODE_50MHZ;
    GPIOA->CRH_CNF9 = GPIO_CNF_AFOPP;
    GPIOA->CRH_MODE10 = GPIO_MODE_INPUT;
    GPIOA->CRH_CNF10 = GPIO_CNF_AFIPP;
}

void GPIO_Init()
{
    /* Configure PORT A */
    PORTA_Config();
}

void GPIO_WriteBits(const GPIO_Port_Type Port, const uint16_t Bits, const BitState_Type State)
{
    switch(Port)
    {
        case PORTA:
            if(BIT_SET == State)
            {
                GPIOA->BSRR_BR = BIT_NONE;
                GPIOA->BSRR_BS = Bits;
            }
            else
            {
                GPIOA->BSRR_BS = BIT_NONE;
                GPIOA->BSRR_BR = Bits;
            }
            break;
        case PORTB:
            break;
    }

}
