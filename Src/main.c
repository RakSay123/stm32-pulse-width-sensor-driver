#include <stdint.h>
#include "stm32g070xx.h"
#include "device_instances.h"
#include "system/system.h"
#include "uart/uart.h"
#include "systick/systick.h"
#include "timer/timer.h"
#include "timer/timer_input_capture/timer_input_capture.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#define HEARTBEAT_INTERVAL_MS 250
#define SENSOR_PRINT_MS 100

int main(void)
{
	system_init();

	LED_t *board_led = get_board_led();
	PULSE_WIDTH_SENSOR_t *sensor = get_pulse_width_sensor();

	uint32_t last_heartbeat_time = 0;
	uint32_t last_print_time = 0;

	uint32_t distance_mm = 0;

	PULSE_WIDTH_SENSOR_Status_t measurement_status = PULSE_WIDTH_SENSOR_NO_NEW_EDGE;

	uart_write_line(USART2, "\r\nSUCCESSFUL BOOT");

	systick_delay_s(2);

	while (1)
	{
		uint32_t now = millis();

		PULSE_WIDTH_SENSOR_Status_t update_status = pulse_width_sensor_update(sensor);
		if (update_status == PULSE_WIDTH_SENSOR_MEASUREMENT_READY) measurement_status = pulse_width_sensor_compute_distance_mm(sensor, &distance_mm);


		if ((now - last_heartbeat_time) >= HEARTBEAT_INTERVAL_MS)
		{
			last_heartbeat_time = now;
			led_toggle(board_led);
		}

		if ((now - last_print_time) >= SENSOR_PRINT_MS)
		{
			last_print_time = now;

			switch (measurement_status)
			{
				case PULSE_WIDTH_SENSOR_OK:
					uart_write_str(USART2, "[PULSE_WIDTH_SENSOR] Distance (mm): ");
					uart_write_int(USART2, distance_mm);
					uart_write_line(USART2, "");
					break;

				case PULSE_WIDTH_SENSOR_NO_DETECTION:
					uart_write_line(USART2, "[PULSE_WIDTH_SENSOR] Nothing detected");
					break;

				case PULSE_WIDTH_SENSOR_INVALID_PULSE:
					uart_write_line(USART2, "[PULSE_WIDTH_SENSOR] Invalid pulse");
					uart_write_str(USART2, "[PULSE_WIDTH_SENSOR] High ticks: ");
					uart_write_int(USART2, sensor->high_ticks);
					uart_write_line(USART2, " ticks");
					break;

				case PULSE_WIDTH_SENSOR_NO_NEW_EDGE:
					uart_write_line(USART2, "[PULSE_WIDTH_SENSOR] Waiting for measurement");
					break;

				default:
					uart_write_line(USART2, "[PULSE_WIDTH_SENSOR] Error");
					break;
			}
		}
	}
}
