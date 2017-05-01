#ifndef _VIC_H
#define _VIC_H

#define VIC_VECT_ADDR_BASE  ((volatile unsigned long *)0xFFFFF100)
#define VIC_VECT_CNTL_BASE  ((volatile unsigned long *)0xFFFFF200)

#define VICIntSelect        (*(volatile unsigned long *)0xFFFFF00C)
#define VICIntEnable        (*(volatile unsigned long *)0xFFFFF010)
#define VICVectAddr         (*(volatile unsigned long *)0xFFFFF030)

#define INT_NUM_I2C0    9
#define INT_NUM_MAX     23

#define IRQ_NUM_MAX     16

/* Stores the IRQ handler address to the desired IRQ slot */
#define VIC_IRQ_REG_SLOT(handler, irq_num) do{ *(VIC_VECT_ADDR_BASE + irq_num) = (unsigned long)handler;} while(0)

/* Assigns the interrupt source to the desired IRQ slot */
#define VIC_IRQ_INT_CONN(irq_num, int_num) do{ *(VIC_VECT_CNTL_BASE + irq_num) = 0x20 | int_num;} while(0)

typedef void (*IRQ_handler)(void);

//extern void VIC_FIQ_handler(void) __attribute__ ((interrupt("FIQ")));
extern void VIC_init(void);
extern int VIC_install_IRQ(unsigned char int_num, IRQ_handler handler, const unsigned char *irq_slot);

#endif
