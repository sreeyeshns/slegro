#include <interrupt.h>
#include <system.h>

#define __NVIC_PRIO_BITS            4

void NVIC_EnableIRQ(IRQn_Type IRQn)
{
    NVIC->ISER[(uint32_t)(IRQn) >> 5] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

void NVIC_SetPriority(IRQn_Type IRQn, uint32_t Priority)
{
    /* Check the parameters */
    if(IRQn < 0)
    {
        /* Set the priority for Cortex-M3 system interrupts */
        SCB->SHP[((uint32_t)(IRQn) & 0xF) - 4] = (Priority << (8 - __NVIC_PRIO_BITS));
    }
    else
    {
        /* Set the priority for device specific interrupts */
        NVIC->IP[(uint32_t)(IRQn)] = (Priority << (8 - __NVIC_PRIO_BITS));
    }
}
