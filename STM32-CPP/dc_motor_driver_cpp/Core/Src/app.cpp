#include "main.h"
#include "app.hpp"
#include "dc_motor_driver.hpp"
extern TIM_HandleTypeDef htim3;

// CubeMX'in ürettiği handle isimlerini kullan
motor right_motor(&htim3, TIM_CHANNEL_1,
		GPIOB, RIGHT_MOTOR_DIRECTION_Pin,
		GPIOB, RIGHT_MOTOR_DIRECTION2_Pin);

motor left_motor(&htim3, TIM_CHANNEL_2,
		GPIOC, LEFT_MOTOR_DIRECTION_Pin,
		GPIOC, LEFT_MOTOR_DIRECTION2_Pin);

void app_init(void)
{
    right_motor.set_speed(700);
    left_motor.set_speed(700);
    right_motor.forward();
    left_motor.forward();
}

void app_run(void)
{
    static uint32_t last_tick  = 0;
    static bool going_forward  = true;

    if (HAL_GetTick() - last_tick >= 3000)
    {
        last_tick = HAL_GetTick();

        if (going_forward)
        {
            right_motor.backward();
            left_motor.backward();
        }
        else
        {
            right_motor.forward();
            left_motor.forward();
        }

        going_forward = !going_forward;
    }
}


