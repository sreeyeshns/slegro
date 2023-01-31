#include <stdio.h>
#include <stdbool.h>
#include <sysclk.h>
#include <serial.h>
#include <gpio.h>

int main()
{
    sysclk_init();
    gpio_init();
    serial_init();
    printf("Hello");
    fflush(stdout);

    uint8_t data[5];
    serial_recv_data(SERIAL_CHANNEL1, data, 5);
    serial_send_data(SERIAL_CHANNEL1, data, 5);


    while(true)
    {
        gpio_write_bits(PORTA, BIT_0, BIT_SET);
        for(volatile int i = 0; i < 500000; i++);/*Delay*/

        gpio_write_bits(PORTA, BIT_0, BIT_CLEAR);
        for(volatile int i = 0; i < 500000; i++);/*Delay*/
    }

    return 0;
}
