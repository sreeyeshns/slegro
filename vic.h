#ifndef _VIC_H
#define _VIC_H
#include <stdint.h>

#define VIC_VECT_ADDR_BASE  ((volatile uint32_t *)0xFFFFF100)
#define VIC_VECT_CNTL_BASE  ((volatile uint32_t *)0xFFFFF200)

#define VICIntSelect        (*(volatile uint32_t *)0xFFFFF00C)
#define VICIntEnable        (*(volatile uint32_t *)0xFFFFF010)
#define VICVectAddr         (*(volatile uint32_t *)0xFFFFF030)

#define INT_NUM_I2C0    9
#define INT_NUM_MAX     23

#define IRQ_NUM_MAX     16

/* Stores the IRQ handler address to the desired IRQ slot */
#define VIC_IRQ_REG_SLOT(handler, irq_num) do{ *(VIC_VECT_ADDR_BASE + irq_num) = (uint32_t)handler;} while(0)

/* Assigns the interrupt source to the desired IRQ slot */
#define VIC_IRQ_INT_CONN(irq_num, int_num) do{ *(VIC_VECT_CNTL_BASE + irq_num) = 0x20 | int_num;} while(0)

typedef void (*IRQ_handler)(void);

//extern void VIC_FIQ_handler(void) __attribute__ ((interrupt("FIQ")));
extern void VIC_init(void);
extern int VIC_install_IRQ(uint8_t int_num, IRQ_handler handler, const uint8_t *irq_slot);

#endif
