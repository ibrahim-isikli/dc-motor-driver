#include "dc_motor_driver.h"


static void _motor_apply_pwm(motor_t* self)
{
	__HAL_TIM_SET_COMPARE(self->htim,self->tim_channel,self->speed);
}

// Public API

void motor_init(motor_t* self, TIM_HandleTypeDef* htim, uint32_t channel, GPIO_TypeDef* dir_port1, uint16_t dir_pin1,GPIO_TypeDef* dir_port2, uint16_t dir_pin2)
{
	self->htim 			= htim;
	self->tim_channel 	= channel;
	self->dir_port1 	= dir_port1;
	self->dir_pin1 		= dir_pin1;
	self->dir_port2 	= dir_port2;
	self->dir_pin2 		= dir_pin2;
	self->speed			= 0;
	self->direction 	= MOTOR_FORWARD;
	self->state 		= MOTOR_STATE_IDLE;
	HAL_GPIO_WritePin(self->dir_port1, self->dir_pin1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(self->dir_port2, self->dir_pin2, GPIO_PIN_RESET);
	// start pwm
	HAL_TIM_PWM_Start(self->htim, self->tim_channel);
	// start motor
	_motor_apply_pwm(self);
}


void motor_set_speed(motor_t* self, uint16_t speed)
{
	if(speed > 999)
		speed = 999;
	self->speed = speed;
	_motor_apply_pwm(self);
}


void motor_forward(motor_t* self)
{
	self->direction = MOTOR_FORWARD;
	self->state		= MOTOR_STATE_RUNNING;
	HAL_GPIO_WritePin(self->dir_port1, self->dir_pin1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(self->dir_port2, self->dir_pin2, GPIO_PIN_RESET);
	_motor_apply_pwm(self);
}


void motor_backward(motor_t* self)
{
	self->direction = MOTOR_BACKWARD;
	self->state		= MOTOR_STATE_RUNNING;
	HAL_GPIO_WritePin(self->dir_port1, self->dir_pin1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(self->dir_port2, self->dir_pin2, GPIO_PIN_SET);
	_motor_apply_pwm(self);
}


void motor_stop(motor_t* self)
{
	self->state = MOTOR_STATE_IDLE;
	__HAL_TIM_SET_COMPARE(self->htim, self->tim_channel, 0);
	HAL_GPIO_WritePin(self->dir_port1, self->dir_pin1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(self->dir_port2, self->dir_pin2, GPIO_PIN_RESET);
	_motor_apply_pwm(self);
}


uint16_t motor_get_speed(motor_t* self)
{
	return self->speed;
}

motor_state_t motor_get_state(motor_t* self)
{
	return self->state;
}
