
/*
Slave Mode: Disable
Clock Source: Internal Clock
Channel 1: PWM Generation CH1
Prescaler: 89
Counter Period (ARR): 999
Pulse (CCR1): 500
PB4: TIM3_CH1 alternate function
PWM frequency: 1 kHz, assuming a 90 MHz TIM3 clock
           */

#include "main.h"

extern TIM_HandleTypeDef htim3;

static uint32_t brightness = 0;

/* Increase brightness */
void increase_brightness(void)
{
    if (brightness < 1000U)
        brightness += 10U;

    if (brightness > 1000U)
        brightness = 1000U;

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, brightness);
}

/* Decrease brightness */
void decrease_brightness(void)
{
    if (brightness >= 10U)
        brightness -= 10U;
    else
        brightness = 0U;

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, brightness);
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM3_Init();

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    for (int count = 0; count < 100; count++)
    {
        /* Fade in: 0% to 100% */
        while (brightness < 1000U)
        {
            increase_brightness();
            HAL_Delay(20);
        }

        /* Fade out: 100% to 0% */
        while (brightness > 0U)
        {
            decrease_brightness();
            HAL_Delay(20);
        }
    }

    /* Stop PWM after 100 complete cycles */
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);

    while (1)
    {
        /* Finished */
    }
}
