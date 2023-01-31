#include <stdio.h>
#include <common.h>
#include <sysclk.h>
#include <serial.h>

extern USART_t USART1;

static serial_t serial_channel[SERIAL_CHANNEL_MAX];

/* Initialize USART */
static void usart_init(const serial_channel_t channel, const uint32_t baud_rate)
{
    USART_t *USART = NULL;
    switch(channel)
    {
        case SERIAL_CHANNEL1:
            /* Enable APB2 clock for USART1 */
            RCC.APB2ENR_USART1EN = BIT_SET;
            serial_channel[channel].USART = &USART1;
            USART = &USART1;
            serial_channel[SERIAL_CHANNEL1].active = true;
            break;
        default:
            break;
    }

    /* Set the USART baud rate */
    USART->BRR = PCLK2 / baud_rate;

    /* Enable USART Rx */
    USART->CR1_RE = BIT_SET;

    /* Enable USART Tx */
    USART->CR1_TE = BIT_SET;

    /* Enable USART */
    USART->CR1_UE = BIT_SET;
}

/* Send data through UART1 */
void serial_send_data(const serial_channel_t channel, uint8_t *data, uint32_t data_len)
{
    USART_t *USART = serial_channel[channel].USART;
    for(uint32_t offset = 0; offset < data_len; offset++)
    {
        /* Wait until the transmit data register is empty */
        while (!USART->SR_TXE);

        /* Send data */
        USART->DR = data[offset];
    }
}

/* Receive data through UART1 */
void serial_recv_data(const serial_channel_t channel, uint8_t *data, uint32_t data_len)
{
    USART_t *USART = serial_channel[channel].USART;
    for(uint32_t offset = 0; offset < data_len; offset++)
    {
        // Wait until data is received
        while (!USART->SR_RXNE);

        // Return received data
        data[offset] = USART->DR;
    }
}

void serial_init()
{
    usart_init(SERIAL_CHANNEL1, BAUD_RATE_115200);
}
