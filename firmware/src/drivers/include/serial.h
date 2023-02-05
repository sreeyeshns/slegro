#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>
#include <stdbool.h>

#define SERIAL_CHANNEL_MAX      3
#define BAUD_RATE_9600          9600
#define BAUD_RATE_115200        115200

typedef enum
{
    SERIAL_CHANNEL1,
    SERIAL_CHANNEL2,
    SERIAL_CHANNEL3
}SerialChannelId_Type;

#define USART1                   ((USART_Type)0x40013800)

/* GPIOA Register mapping*/
typedef struct
{
    /***** Status register (USART_SR). Address offset: 0x00 *****/
    union
    {
        volatile uint32_t SR;
        struct
        {
            volatile uint32_t        :5;
            volatile uint32_t RXNE   :1;
            volatile uint32_t        :1;
            volatile uint32_t TXE    :1;
            volatile uint32_t        :24;
        }Bits;
    }_SR;
#define SR                 _SR.SR
#define SR_RXNE           _SR.Bits.RXNE
#define SR_TXE            _SR.Bits.TXE

    /***** Data register (USART_DR). Address offset: 0x04 *****/
    uint32_t DR;

    /***** Baud rate register (USART_BRR). Address offset: 0x08 *****/
    union
    {
        volatile uint32_t BRR;
        struct
        {
            volatile uint32_t DIV_FRCTN     :4;
            volatile uint32_t DIV_MNTSA     :12;
            volatile uint32_t               :16;
        }Bits;
    }_BRR;
#define BRR                 _BRR.BRR
#define BRR_DIV_FRCTN       _BRR.Bits.DIV_FRCTN
#define BRR_DIV_MNTSA       _BRR.Bits.DIV_MNTSA


    /***** Control register 1 (USART_CR1). Address offset: 0x0C *****/
    union
    {
        volatile uint32_t CR1;
        struct
        {
            volatile uint32_t        :2;
            volatile uint32_t RE     :1;
            volatile uint32_t TE     :1;
            volatile uint32_t        :9;
            volatile uint32_t UE     :1;
            volatile uint32_t        :18;
        }Bits;
    }_CR1;
#define CR1                _CR1.CR1
#define CR1_RE             _CR1.Bits.RE
#define CR1_TE             _CR1.Bits.TE
#define CR1_UE             _CR1.Bits.UE
}*USART_Type;

typedef struct
{
    bool active;
    USART_Type USART;
}SerialChannel_Type;

void SerialInit(void);
void SerialSendData(const SerialChannelId_Type Channel, uint8_t *pData, uint32_t DataLen);
void SerialRecvData(const SerialChannelId_Type Channel, uint8_t *pData, uint32_t DataLen);

#endif //_SERIAL_H
