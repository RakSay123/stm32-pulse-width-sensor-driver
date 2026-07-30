#include "led_init.h"

void led_init_all()
{
	led_init(get_board_led());
}
