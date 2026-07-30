#include "uart_init.h"

#define FCLK 16000000
#define BAUD_RATE 115200

static UART_Config_t uart2_cfg = {
	.USARTx = USART2,
	.fclk = FCLK,
	.baud_rate = BAUD_RATE
};

void uart_init_all(void)
{
	uart_init(&uart2_cfg);
}
