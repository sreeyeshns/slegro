#include <sysclk.h>
#include <gpio.h>

static void porta_config()
{
    /* Enable APB2 clock for PORT A */
    RCC_APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* Configure pin 0 of PORT A for gpio output*/
    GPIOA_CRL |= GPIOA_CRL_MODE0;
    GPIOA_CRL &= ~(GPIOA_CRL_CNF0);
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
            GPIOA_BSRR = bits << ((BIT_SET == state) ? 0 : 16);
            break;
        default:
            //TODO Log error here
            break;
    }

}
