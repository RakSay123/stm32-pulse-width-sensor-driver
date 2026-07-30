#include "system.h"

#include "gpio/gpio_init.h"
#include "systick/systick_init.h"
#include "timer/timer_init.h"
#include "uart/uart_init.h"
//#include "i2c/i2c_init.h"

#include "led/led_init.h"
//#include "bno055/bno055_init.h"
//#include "servo/servo_init.h"
#include "pulse_width_sensor/pulse_width_sensor_init.h"

void system_init(void)
{
	/*** Peripherals ***/
	gpio_init_all();
	systick_init_all();
	timer_init_all();
	uart_init_all();
//	i2c_init_all();

	/*** Devices ***/
	led_init_all();
//	bno055_init_all();
//	servo_init_all();
	pulse_width_sensor_init_all();
}
