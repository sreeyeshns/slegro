#include <stdio.h>
#include <string.h>
#include <serial.h>
#include <pll.h>
#include <gpio.h>
#include <log.h>
#include <version.h>

extern int32_t (*__console_write)(uint8_t *, uint32_t);

void Delay(unsigned long val)
{
   while(val > 0)
   {
      val--;
   }
}

static int32_t system_init()
{
    /* Initialize the PLL to set 25 MHZ clock */
    PLL_init();

    /* Initialize UART0 for console access */
    UART0_init();

    /* Set the console write API */
    __console_write = UART0_write;

    return 0;
}

int main()
{
   system_init();
   LOG_INFO("!!! Slegro waking up !!!");
   LOG_INFO("Software version: %d.%d.%d", MINOR_VERSION, MINOR_VERSION, PATCH_VERSION);
   LOG_INFO("Build version: %s", BUILD_VERSION);

   IO0DIR = 0XFFFFFFFF; /* Set Port0 as output */
   while(1)
   {
      IO0SET = 0X000E0000; /* Set P0.17,P0.18,P0.19 at logic high state */
      Delay(1000000);
      IO0CLR = 0X000E0000; /* Set P0.17,P0.18,P0.19 at logic low state  */
      Delay(1000000);
   }

   return 0;
}

