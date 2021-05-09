#include <stdio.h>
#include <string.h>
#include <system.h>
#include <gpio.h>
#include <log.h>
#include <version.h>

void Delay(unsigned long val)
{
   while(val > 0)
   {
      val--;
   }
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

