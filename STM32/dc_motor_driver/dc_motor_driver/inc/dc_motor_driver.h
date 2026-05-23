#ifndef DC_MOTOR_DRIVER_H
#define DC_MOTOR_DRIVER_H

#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

// motor direction macros
#define MOTOR_FORWARD	0u
#define MOTOR_BACKWARD  1u


// motor state
typedef enum
{
	MOTOR_STATE_IDLE = 0u,
	MOTOR_STATE_RUNNING,
	MOTOR_STATE_FAULT
}motor_state_t;

typedef struct
{
	// hardware abstraction layer references
	TIM_HandleTypeDef*	htim;
	uint32_t			tim_channel;

	// direction gpio
	GPIO_TypeDef*		dir_port1;
	uint16_t			dir_pin1;
	GPIO_TypeDef*		dir_port2;
	uint16_t			dir_pin2;

	// states
	uint16_t			speed;
	uint8_t				direction;
	motor_state_t		state;
}motor_t;


//------------ API ------------

void motor_init(motor_t* self, TIM_HandleTypeDef* htim, uint32_t channel, GPIO_TypeDef* dir_port1, uint16_t dir_pin1,GPIO_TypeDef* dir_port2, uint16_t dir_pin2);
void motor_set_speed(motor_t* self, uint16_t speed);
void motor_forward(motor_t* self);
void motor_backward(motor_t* self);
void motor_stop(motor_t* self);
uint16_t motor_get_speed(motor_t* self);
motor_state_t motor_get_state(motor_t* self);



#endif
