#include <stdint.h>
#include <stdio.h>

#define __INITIAL_SP   0x20005000

extern uint32_t __data_start__[];
extern uint32_t const __data_load__[];
extern uint32_t const __data_end__[];

extern uint32_t __bss_start__[];
extern uint32_t const __bss_end__[];

static void Reset_Handler(void);
void main(void);

uint32_t * vectors[76]
__attribute__ ((section(".vectors")))= {
    (uint32_t *)    __INITIAL_SP,    // stack pointer points to the end(stack top) of data memory
    (uint32_t *)    Reset_Handler     // code entry point
};

void Reset_Handler(void)
{
    /* Copy data belonging to the `.data` section from its
     * storage address on flash (ROM) to its load address
     * in SRAM.
     */

    for(uint32_t Index = 0; __data_start__ + Index < __data_end__; Index++)
    {
        __data_start__[Index] = __data_load__[Index];
    }

    /* Clear BSS storage*/
    for(uint32_t Index = 0; __bss_start__ + Index < __bss_end__; Index++)
    {
        __bss_start__[Index] = 0;
    }

    main();
}
