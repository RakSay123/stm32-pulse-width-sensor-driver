#include "gpio_init.h"

static GPIO_Config_t usart2_tx_pa2 = {
	.port = GPIOA,
	.pin = 2,
	.mode = GPIO_MODE_AF,
	.otype = GPIO_PUSH_PULL,
	.speed = GPIO_SPEED_HIGH,
	.pull = GPIO_NO_PULL,
	.alternate = GPIO_AF1
};

static GPIO_Config_t usart2_rx_pa3 = {
	.port = GPIOA,
	.pin = 3,
	.mode = GPIO_MODE_AF,
	.otype = GPIO_PUSH_PULL,
	.speed = GPIO_SPEED_HIGH,
	.pull = GPIO_NO_PULL,
	.alternate = GPIO_AF1
};

void gpio_init_all(void)
{
	gpio_init(&usart2_tx_pa2);
	gpio_init(&usart2_rx_pa3);
}
