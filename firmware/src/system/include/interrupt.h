#ifndef _INTERRUPT_H
#define _INTERRUPT_H
#include <stdint.h>

#define INT_REG_MAX         3

#define __enable_irq() __asm volatile ("cpsie i")
#define __disable_irq() __asm volatile ("cpsid i")

#define NVIC                    ((NVIC_Type)0xE000E100)

typedef enum
{
    IRQ0,
    IRQ1,
    IRQ2,
    IRQ3,
    IRQ4,
    IRQ5,
    IRQ6,
    IRQ7,
    IRQ8,
    IRQ9,
    IRQ10,
    IRQ11,
    IRQ12,
    IRQ13,
    IRQ14,
    IRQ15,
    IRQ16,
    IRQ17,
    IRQ18,
    IRQ19,
    IRQ20,
    IRQ21,
    IRQ22,
    IRQ23,
    IRQ24,
    IRQ25,
    IRQ26,
    IRQ27,
    IRQ28,
    IRQ29,
    IRQ30,
    IRQ31,
    IRQ32,
    IRQ33,
    IRQ34,
    IRQ35,
    IRQ36,
    IRQ37,
    IRQ38,
    IRQ39,
    IRQ40,
    IRQ41,
    IRQ42,
    IRQ43,
    IRQ44,
    IRQ45,
    IRQ46,
    IRQ47,
    IRQ48,
    IRQ49,
    IRQ50,
    IRQ51,
    IRQ52,
    IRQ53,
    IRQ54,
    IRQ55,
    IRQ56,
    IRQ57,
    IRQ58,
    IRQ59,
    IRQ60,
    IRQ61,
    IRQ62,
    IRQ63,
    IRQ64,
    IRQ65,
    IRQ66,
    IRQ67,
    IRQ_MAX
}IRQn_Type;

/* NVIC Register mapping*/
typedef struct
{
    uint32_t ISER[INT_REG_MAX];
    uint32_t ICER[INT_REG_MAX];
    uint32_t ISPR[INT_REG_MAX];
    uint32_t ICPR[INT_REG_MAX];
    uint32_t IABR[INT_REG_MAX];
    uint8_t IP[IRQ_MAX];
}*NVIC_Type;

void NVIC_EnableIRQ(IRQn_Type IRQn);
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t Priority);

#endif //_INTERRUPT_H
