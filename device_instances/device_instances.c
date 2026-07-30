#include "device_instances.h"

static LED_t board_led = {
    .port = GPIOA,
    .pin = 5,
    .mode = LED_MODE_GPIO,
	.alternate = GPIO_AF0
};

static TIM_Input_Capture_Config_t tim3_ch1_ic_cfg = {
	.TIMx = TIM3,
	.channel = 1,
	.input_selection = TIM_IC_INPUT_DIRECT,
	.psc = TIM_IC_FILTER_NONE,
	.mode = TIM_IC_EDGE_RISING
};

static PULSE_WIDTH_SENSOR_t pulse_width_sensor = {
	.port = GPIOA,
	.pin = 6,
	.alternate = GPIO_AF1,

	.capture_cfg = &tim3_ch1_ic_cfg,

	.state = WAITING_FOR_RISING,

	.measurement_ready = false,

	.rising_timestamp = 0U,
	.falling_timestamp = 0U,

	.high_ticks = 0U,

	.minimum_distance_mm = 0U,
	.maximum_distance_mm = 500U,

	.minimum_pulse_width_us = 1000U,
	.maximum_pulse_width_us = 1667U,
	.no_detection_pulse_width_us = 1900U,

	.distance_mm = 0U
};


LED_t* get_board_led(void)
{
	return &board_led;
}

PULSE_WIDTH_SENSOR_t* get_pulse_width_sensor(void)
{
	return &pulse_width_sensor;
}
