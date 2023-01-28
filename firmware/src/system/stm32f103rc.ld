/* Stack and heap are equal in size by default.
 *
 * A positive value for STACK_HEAP_BOUNDARY_OFFSET increase the size
 * of the stack(Decrease size of heap).
 *
 * A negetive value for STACK_HEAP_BOUNDARY_OFFSET decrease the size
 * of the stack(increase size of heap).
 */
STACK_HEAP_BOUNDARY_OFFSET = 0;
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 64K
    SRAM  (rw) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .  = 0x00000000;         /* From 0x00000000 */
    
    .text :
    {
        *(.vectors)          /* Vector table */
        *(.text .txt.*)      /* Program code */
        . = ALIGN(4);
    } > FLASH

    .rodata :
    {
        *(.rodata .rodata.*) /* Read only data */
        . = ALIGN(4);
    } > FLASH

    .data :
    {
        __data_load__ = LOADADDR (.data);
        __data_start__ = .;
        *(.data .data.*)     /* Data memory */
        . = ALIGN(4);
        __data_end__ = .;
    } > SRAM AT > FLASH

    .bss :
    {
        __bss_start__ = .;
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > SRAM

    .heap :
    {
        __heap_start__ = .;
        . = . + ((LENGTH(SRAM) - (. - (ORIGIN(SRAM)))) / 2);
        . += STACK_HEAP_BOUNDARY_OFFSET;
        . = ALIGN(4);
        __heap_end__ = .;
    } > SRAM

    .stack :
    {
        __stack_start__ = .;
        . = . + (LENGTH(SRAM) - (. - (ORIGIN(SRAM))));
        . = ALIGN(4);
        __stack_end__ = .;
        __stack_size__ = __stack_end__ - __stack_start__;
    } > SRAM

    RCC = 0x40021000;
    GPIOA = 0x40010800;
}
