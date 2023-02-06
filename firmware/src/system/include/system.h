#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <serial.h>
#define SERIAL_CHANNEL_CONSOLE          SERIAL_CHANNEL1
#define ConsoleWrite(Data, DataLen)     SerialSendData(SERIAL_CHANNEL_CONSOLE, Data, DataLen)

#define SYS_HANDLE_REG_MAX              3


#define SCB                             ((SCB_Type)0xE000ED00)

/* SCB Register mapping*/
typedef struct
{
    uint32_t unused1[6];
    uint32_t SHP[SYS_HANDLE_REG_MAX];
}*SCB_Type;

#endif //_SYSTEM_H
