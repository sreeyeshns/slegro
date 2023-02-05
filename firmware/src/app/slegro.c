#include <stdio.h>
#include <stdbool.h>
#include <sysclk.h>
#include <serial.h>
#include <gpio.h>
#include <log.h>
#include <version.h>

int main()
{
    SystemInit();
    GPIO_Init();
    SerialInit();

    LOG_INFO("!!!Slegro is waking up!!!");
    LOG_INFO("Software version: %d.%d.%d", MINOR_VERSION, MINOR_VERSION, PATCH_VERSION);
    LOG_INFO("Build version: %s", BUILD_VERSION);

    uint8_t Data[5];
    SerialRecvData(SERIAL_CHANNEL1, Data, 5);
    SerialSendData(SERIAL_CHANNEL1, Data, 5);


    while(true)
    {
        GPIO_WriteBits(PORTA, BIT_0, BIT_SET);
        for(volatile int i = 0; i < 500000; i++);/*Delay*/

        GPIO_WriteBits(PORTA, BIT_0, BIT_CLEAR);
        for(volatile int i = 0; i < 500000; i++);/*Delay*/
    }

    return 0;
}
