#include "dc_motor_driver.hpp"

motor::motor(TIM_HandleTypeDef* htim, uint32_t channel,
             GPIO_TypeDef* dir_port1, uint16_t dir_pin1,
             GPIO_TypeDef* dir_port2, uint16_t dir_pin2)
{
    _htim       = htim;
    _channel    = channel;
    _dir_port1  = dir_port1;
    _dir_pin1   = dir_pin1;
    _dir_port2  = dir_port2;
    _dir_pin2   = dir_pin2;
    _speed      = 0;
    _direction  = MOTOR_FORWARD;
    _state      = MOTOR_STATE_IDLE;

    HAL_GPIO_WritePin(_dir_port1, _dir_pin1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_dir_port2, _dir_pin2, GPIO_PIN_RESET);

    HAL_TIM_PWM_Start(_htim, _channel);
    _apply_pwm();
}

void motor::_apply_pwm()
{
    __HAL_TIM_SET_COMPARE(_htim, _channel, _speed);
}

void motor::set_speed(uint16_t speed)
{
    if (speed > 999)
        speed = 999;
    _speed = speed;
    _apply_pwm();
}

void motor::forward()
{
    _direction = MOTOR_FORWARD;
    _state     = MOTOR_STATE_RUNNING;
    HAL_GPIO_WritePin(_dir_port1, _dir_pin1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(_dir_port2, _dir_pin2, GPIO_PIN_RESET);
    _apply_pwm();
}

void motor::backward()
{
    _direction = MOTOR_BACKWARD;
    _state     = MOTOR_STATE_RUNNING;
    HAL_GPIO_WritePin(_dir_port1, _dir_pin1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_dir_port2, _dir_pin2, GPIO_PIN_SET);
    _apply_pwm();
}

void motor::stop()
{
    _state = MOTOR_STATE_IDLE;
    HAL_GPIO_WritePin(_dir_port1, _dir_pin1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_dir_port2, _dir_pin2, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(_htim, _channel, 0);
}

uint16_t motor::get_speed()
{
    return _speed;
}

motor_state_t motor::get_state()
{
    return _state;
}
