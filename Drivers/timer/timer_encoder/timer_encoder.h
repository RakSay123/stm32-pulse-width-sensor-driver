#pragma once

#include "timer/timer.h"
#include "gpio/gpio.h"

typedef enum {
	TIM_ENCODER_MODE_TI1,
	TIM_ENCODER_MODE_TI2,
	TIM_ENCODER_MODE_TI1_TI2
} TIM_ENCODER_Mode_t;

typedef enum {
    TIM_ENCODER_PSC_NONE = 0,
    TIM_ENCODER_PSC_TWO = 1,
    TIM_ENCODER_PSC_FOUR = 2,
    TIM_ENCODER_PSC_EIGHT = 3
} TIM_ENCODER_Psc_t;

typedef enum {
    TIM_ENCODER_FILTER_NONE = 0,

    TIM_ENCODER_FILTER_FCK_INT_N2 = 1,
    TIM_ENCODER_FILTER_FCK_INT_N4 = 2,
    TIM_ENCODER_FILTER_FCK_INT_N8 = 3,

    TIM_ENCODER_FILTER_FDTS_DIV2_N6 = 4,
    TIM_ENCODER_FILTER_FDTS_DIV2_N8 = 5,

    TIM_ENCODER_FILTER_FDTS_DIV4_N6 = 6,
    TIM_ENCODER_FILTER_FDTS_DIV4_N8 = 7,

    TIM_ENCODER_FILTER_FDTS_DIV8_N6 = 8,
    TIM_ENCODER_FILTER_FDTS_DIV8_N8 = 9,

    TIM_ENCODER_FILTER_FDTS_DIV16_N5 = 10,
    TIM_ENCODER_FILTER_FDTS_DIV16_N6 = 11,
    TIM_ENCODER_FILTER_FDTS_DIV16_N8 = 12,

    TIM_ENCODER_FILTER_FDTS_DIV32_N5 = 13,
    TIM_ENCODER_FILTER_FDTS_DIV32_N6 = 14,
    TIM_ENCODER_FILTER_FDTS_DIV32_N8 = 15
} TIM_ENCODER_Filter_t;

typedef struct {
	TIM_TypeDef *TIMx;

	GPIO_TypeDef *channel_a_port;
	uint8_t channel_a_pin;
	GPIO_AF_t channel_a_AF;

	GPIO_TypeDef *channel_b_port;
	uint8_t channel_b_pin;
	GPIO_AF_t channel_b_AF;

	TIM_ENCODER_Mode_t mode;
	TIM_ENCODER_Psc_t psc;

	uint8_t channel_a_filter;
	uint8_t channel_b_fillter;

} TIM_ENCODER_Config_t;

TIM_Status_t timer_encoder_init(TIM_ENCODER_Config_t *cfg);
