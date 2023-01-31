#include <stdio.h>
#include <stdbool.h>
#include <sysclk.h>
#include <serial.h>
#include <gpio.h>
#include <log.h>
#include <version.h>

int main()
{
    sysclk_init();
    gpio_init();
    serial_init();

    LOG_INFO("!!!Slegro is waking up!!!");
    LOG_INFO("Software version: %d.%d.%d", MINOR_VERSION, MINOR_VERSION, PATCH_VERSION);
    LOG_INFO("Build version: %s", BUILD_VERSION);

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
