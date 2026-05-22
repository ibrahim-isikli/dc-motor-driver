#ifndef DC_MOTOR_DRIVER_H
#define DC_MOTOR_DRIVER_H

#include "stm32f407xx.h"
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
}Motor_State_t;

typedef struct
{
	// hardware abstraction layer references
	TIM_HandleTypeDef*	htim;
	uint32_t			tim_channel;

	// direction gpio
	GPIO_TypeDef		dir_port;
	uint16_t			dir_pin;

	// states
	uint16_t			speed;
	uint8_t				direction;
	Motor_State_t		state;
}Motor_t;


//------------ API ------------

void motor_init(Motor_t* self, TIM_HandleTypeDef* htim, uint32_t channel, GPIO_TypeDef* dir_port, uint16_t dir_pin);
void motor_forward(Motor_t* self, uint16_t speed);



#endif
