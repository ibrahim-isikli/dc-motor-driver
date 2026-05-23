#include "dc_motor_driver.h"


static void _motor_apply_pwm(motor_t* self)
{
	__HAL_TIM_SET_COMPARE(self->htim,self->tim_channel,self->speed);
}

// Public API

void motor_init(motor_t* self, TIM_HandleTypeDef* htim, uint32_t channel, GPIO_TypeDef* dir_port, uint16_t dir_pin)
{
	self->htim 			= htim;
	self->tim_channel 	= channel;
	self->dir_port 		= dir_port;
	self->dir_pin 		= dir_pin;
	self->speed			= 0;
	self->direction 	= MOTOR_FORWARD;
	self->state 		= MOTOR_STATE_IDLE;
	// start pwm
	HAL_TIM_PWM_Start(self->htim, self->tim_channel);
	// start motor
	_motor_apply_pwm(self);
	HAL_GPIO_WritePin(self->dir_port, self->dir_pin, GPIO_PIN_RESET);
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
	HAL_GPIO_WritePin(self->dir_port, self->dir_pin, GPIO_PIN_RESET);
	_motor_apply_pwm(self);
}


void motor_backward(motor_t* self)
{
	self->direction = MOTOR_BACKWARD;
	self->state		= MOTOR_STATE_RUNNING;
	HAL_GPIO_WritePin(self->dir_port, self->dir_pin, GPIO_PIN_SET);
	_motor_apply_pwm(self);
}


void motor_stop(motor_t* self)
{
	self->state = MOTOR_STATE_IDLE;
	self->speed = 0u;
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
