#include <stdio.h>
#include <stdbool.h>
#include <sysclk.h>
#include <gpio.h>

int main()
{
    sysclk_init();
    gpio_init();

    while(true)
    {
        gpio_write_bits(PORTA, BIT_0, BIT_SET);
        for(volatile int i = 0; i < 500000; i++);/*Delay*/

        gpio_write_bits(PORTA, BIT_0, BIT_CLEAR);
        for(volatile int i = 0; i < 500000; i++);/*Delay*/
    }

    return 0;
}
