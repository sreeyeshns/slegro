#include <stdio.h>
#include <system.h>
#include <gpio.h>
#include <serial.h>
#include <error.h>

/* The baud rate calulations are based on the the following assumptions
 * CCLK = 60 MHZ and PCLK = 15 MHZ
 * DIVADDRVAL = 0 and MULVAL = 1
 */

ret_code_t UART0_init(uart_baud_rate_t baud_rate, uart_word_length_t word_length, uart_parity_t parity, uart_stop_bits_t stop_bits)
{
   uint32_t reg_value = 0;

   /* P0.0 = UART0 TX, P0.1 = UART0 RX*/
   PINSEL0 |= 0x05U;

   /* Set word length */
   switch(word_length)
   {
      case WORD_LENGTH_5:
         /* reg_val = 0 by default selects word length 5*/
         break;
      case WORD_LENGTH_6:
         reg_value = ULCR_BIT_WORD_LEN0;
         break;
      case WORD_LENGTH_7:
         reg_value = ULCR_BIT_WORD_LEN1;
         break;
      case WORD_LENGTH_8:
         reg_value = ULCR_BIT_WORD_LEN1 | ULCR_BIT_WORD_LEN0;
         break;
      default:
         return ERROR_UART_INIT;
   }

   /* Set parity */
   reg_value |= ULCR_BIT_PARITY_ENABLE;
   switch(parity)
   {
      case PARITY_ODD:
         break;
      case PARITY_EVEN:
         reg_value |= ULCR_BIT_PARITY0;
         break;
      case PARITY_FORCED_1_STICK:
         reg_value |= ULCR_BIT_PARITY1;
         break;
      case PARITY_FORCED_0_STICK:
         reg_value |= (ULCR_BIT_PARITY1 | ULCR_BIT_PARITY0);
         break;
      case PARITY_NONE:
         reg_value &= ~ULCR_BIT_PARITY_ENABLE;
         break;
      default:
         return ERROR_UART_INIT;
   }

   /* Set number of stop bits */
   switch(stop_bits)
   {
      case STOP_BIT_1:
         break;
      case STOP_BIT_2:
         reg_value |= ULCR_BIT_STOP_BIT;
         break;
      default:
         return ERROR_UART_INIT;
   }

   /* DLAB = 1 */
   reg_value |= ULCR_BIT_DLAB;


   U0LCR = reg_value;


   /* Set the baud rate.
    * Note: The fractional divider is not available for LPC2138
    */
   switch(baud_rate)
   {
      case BAUD_RATE_1200:
      case BAUD_RATE_2400:
      case BAUD_RATE_4800:
      case BAUD_RATE_9600:
      case BAUD_RATE_19200:
      case BAUD_RATE_38400:
      case BAUD_RATE_57600:
      case BAUD_RATE_115200:
      case BAUD_RATE_460800:
      case BAUD_RATE_921600:
      case BAUD_RATE_230400:
         reg_value = (SYS_PCLK_MHZ * 1000000) / 16 /  baud_rate;
         U0DLM = (reg_value & 0xFFFF) >> 8;
         U0DLL = (reg_value & 0x00FF);
         break;
      default:
         return ERROR_UART_INIT;
   }

   /* DLAB = 0 */
   U0LCR &= ~ULCR_BIT_DLAB;

   return ERROR_NONE;
}

int32_t UART0_write(uint8_t *buff, uint32_t size)
{
    int32_t byte_count;

    if(NULL == buff)
    {
        return -1;
    }

    for(byte_count = 0; byte_count < size; byte_count++)
    {
        while (!(U0LSR & 0x20));
        U0THR = buff[byte_count];
    }
    while (!(U0LSR & 0x40));
    return byte_count;
}

uint8_t UART0_read()
{
    while (!(U0LSR & 0x01));
    return U0RBR;
}

