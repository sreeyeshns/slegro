#include <stdint.h>
#include <stdio.h>

#define STACK_TOP   0x20005000 //TODO Instead get the stack end address from linker script

extern uint32_t __data_start__[];
extern uint32_t const __data_load__[];
extern uint32_t const __data_end__[];

extern uint32_t __bss_start__[];
extern uint32_t const __bss_end__[];

static void __startup(void);
void main(void);

uint32_t * vectors[76]
__attribute__ ((section(".vectors")))= {
    (uint32_t *)    STACK_TOP,    // stack pointer points to the end(stack top) of data memory
    (uint32_t *)    __startup     // code entry point
};

void __startup(void)
{
    /* Copy data belonging to the `.data` section from its
     * storage address on flash (ROM) to its load address
     * in SRAM.
     */

    for(uint32_t index = 0; __data_start__ + index < __data_end__; index++)
    {
        __data_start__[index] = __data_load__[index];
    }

    /* Clear BSS storage*/
    for(uint32_t index = 0; __bss_start__ + index < __bss_end__; index++)
    {
        __bss_start__[index] = 0;
    }

    main();
}
