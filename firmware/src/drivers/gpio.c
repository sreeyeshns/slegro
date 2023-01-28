#include <common.h>
#include <sysclk.h>
#include <gpio.h>

static void porta_config()
{
    /* Enable APB2 clock for PORT A */
    RCC.APB2ENR_IOPAEN = BIT_SET;

    /* Configure pin 0 of PORT A for gpio output*/
    GPIOA.CRL_MODE0 = CRL_MODE0_50MHZ;
    GPIOA.CRL_CNF0 = CRL_CNF0_GPPP;
}

void gpio_init()
{
    /* Configure PORT A */
    porta_config();
}

void gpio_write_bits(const gpio_port_t port, const uint16_t bits, const bit_state_t state)
{
    switch(port)
    {
        case PORTA:
            if(BIT_SET == state)
            {
                GPIOA.BSRR_BR = BIT_NONE;
                GPIOA.BSRR_BS = bits;
            }
            else
            {
                GPIOA.BSRR_BS = BIT_NONE;
                GPIOA.BSRR_BR = bits;
            }
            break;
        default:
            //TODO Log error here
            break;
    }

}
