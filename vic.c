#include <defs.h>
#include <vic.h>
#include <string.h>
#include <stdio.h>

uint8_t __vicinitialized = FALSE;
/*void VIC_FIQ_handler(void)
{
	;
}*/
void VIC_init()
{
    memset((void *) VIC_VECT_ADDR_BASE, 0, IRQ_NUM_MAX);
    memset((void *) VIC_VECT_CNTL_BASE, 0, IRQ_NUM_MAX);
    __vicinitialized = TRUE;
}

int VIC_install_IRQ(unsigned char int_num, IRQ_handler handler,
        const unsigned char *irq_slot)
{
    int irq_num = -1;
    if (handler == NULL || int_num >= INT_NUM_MAX)
        return -1;
    if (irq_slot)
    {
        irq_num = *irq_slot;
        if (irq_num >= IRQ_NUM_MAX)
            return -1;
        if (*(VIC_VECT_ADDR_BASE + irq_num))
            return -1;
    }
    else
    {
        for (irq_num = 0; irq_num < IRQ_NUM_MAX; irq_num++)
        {
            if (!*(VIC_VECT_ADDR_BASE + irq_num))
                break;
        }
        if (irq_num == IRQ_NUM_MAX)
            return -1;
    }
    VICIntSelect &= ~(1 << int_num);
    VIC_IRQ_REG_SLOT(handler, irq_num);
    VIC_IRQ_INT_CONN(irq_num, int_num);
    VICIntEnable |= 1 << int_num;
    return irq_num;
}
