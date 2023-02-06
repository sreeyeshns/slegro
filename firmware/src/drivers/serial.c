#include <stdio.h>
#include <common.h>
#include <sysclk.h>
#include <serial.h>
#include <interrupt.h>

#define IRQ37_PRIO              0

static SerialChannel_Type sSerialChannel[SERIAL_CHANNEL_MAX];

/* Initialize USART */
static void sUSART_Init(const SerialChannelId_Type Channel, const uint32_t BaudRate, void (*Handler)(void), const uint8_t Priority)
{
    USART_Type USART = NULL;
    switch(Channel)
    {
        case SERIAL_CHANNEL1:
            /* Enable APB2 clock for USART1 */
            RCC->APB2ENR_USART1EN = BIT_SET;
            sSerialChannel[Channel].USART = USART1;
            USART = USART1;
            sSerialChannel[SERIAL_CHANNEL1].active = true;
            sSerialChannel[SERIAL_CHANNEL1].IRQn = IRQ37;
            sSerialChannel[SERIAL_CHANNEL1].IRQprio = Priority;
            sSerialChannel[SERIAL_CHANNEL1].IRQhandler = Handler;
            break;
        default:
            break;
    }

    /* Set the USART baud rate */
    USART->BRR = PCLK2 / BaudRate;

    /* Enable USART Rx */
    USART->CR1_RE = BIT_SET;

    /* Enable interrupt */
    if(NULL != Handler)
    {
        NVIC_SetPriority(sSerialChannel[Channel].IRQn, sSerialChannel[SERIAL_CHANNEL1].IRQprio);
        NVIC_EnableIRQ(sSerialChannel[Channel].IRQn);
        USART->CR1_RXNEIE = BIT_SET;
    }
    /* Enable USART Tx */
    USART->CR1_TE = BIT_SET;

    /* Enable USART */
    USART->CR1_UE = BIT_SET;
}

void __USART1_IRQHandler(void)
{
  /* Handle UART1 interrupt */
  if(NULL != sSerialChannel[SERIAL_CHANNEL1].IRQhandler)
  {
      sSerialChannel[SERIAL_CHANNEL1].IRQhandler();
  }
}

/* Send data through UART1 */
void SerialSendData(const SerialChannelId_Type Channel, uint8_t *pData, uint32_t DataLen)
{
    USART_Type USART = sSerialChannel[Channel].USART;
    for(uint32_t Offset = 0; Offset < DataLen; Offset++)
    {
        /* Wait until the transmit data register is empty */
        while (!USART->SR_TXE);

        /* Send data */
        USART->DR = pData[Offset];
    }
}

/* Receive data through UART1 */
void SerialRecvData(const SerialChannelId_Type Channel, uint8_t *pData, uint32_t DataLen)
{
    USART_Type USART = sSerialChannel[Channel].USART;
    for(uint32_t Offset = 0; Offset < DataLen; Offset++)
    {
        // Wait until data is received
        while (!USART->SR_RXNE);

        // Return received data
        pData[Offset] = USART->DR;
    }
}

void SerialLoopback(void)
{
    char ch;
    SerialRecvData(SERIAL_CHANNEL1, (uint8_t*)&ch, 1);
    SerialSendData(SERIAL_CHANNEL1, (uint8_t*)&ch, 1);
}

void SerialInit()
{
    sUSART_Init(SERIAL_CHANNEL1, BAUD_RATE_115200, SerialLoopback, IRQ37_PRIO);
}
