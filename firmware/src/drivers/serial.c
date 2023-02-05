#include <stdio.h>
#include <common.h>
#include <sysclk.h>
#include <serial.h>

static SerialChannel_Type sSerialChannel[SERIAL_CHANNEL_MAX];

/* Initialize USART */
static void USART_Init(const SerialChannelId_Type Channel, const uint32_t BaudRate)
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
            break;
        default:
            break;
    }

    /* Set the USART baud rate */
    USART->BRR = PCLK2 / BaudRate;

    /* Enable USART Rx */
    USART->CR1_RE = BIT_SET;

    /* Enable USART Tx */
    USART->CR1_TE = BIT_SET;

    /* Enable USART */
    USART->CR1_UE = BIT_SET;
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

void SerialInit()
{
    USART_Init(SERIAL_CHANNEL1, BAUD_RATE_115200);
}
