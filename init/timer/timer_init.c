#include "timer_init.h"

static TIM_Config_t tim3_cfg = {
	.TIMx = TIM3,
	.psc = 16 - 1,
	.arr = (1U << 16) - 1,
	.cnt = 0,
	.interrupt_status = TIM_INTERRUPTS_DISABLED
};

void timer_init_all(void)
{
	timer_init(&tim3_cfg);
}
