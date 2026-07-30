#pragma once

#include "stm32g070xx.h"
#include "led/led.h"
#include "servo/servo.h"
#include "pulse_width_sensor/pulse_width_sensor.h"

LED_t* get_pwm_led(void);

LED_t* get_board_led(void);

SERVO_t* get_mg90s(void);

PULSE_WIDTH_SENSOR_t* get_pulse_width_sensor(void);
