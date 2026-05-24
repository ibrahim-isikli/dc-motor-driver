#ifndef DC_MOTOR_DRIVER_HPP
#define DC_MOTOR_DRIVER_HPP

#include "stm32f4xx_hal.h"
#include <stdint.h>

#define MOTOR_FORWARD   0u
#define MOTOR_BACKWARD  1u

typedef enum
{
    MOTOR_STATE_IDLE = 0u,
    MOTOR_STATE_RUNNING,
    MOTOR_STATE_FAULT
} motor_state_t;

class motor
{
  public:
    motor(TIM_HandleTypeDef* htim, uint32_t channel,
          GPIO_TypeDef* dir_port1, uint16_t dir_pin1,
          GPIO_TypeDef* dir_port2, uint16_t dir_pin2);

    void set_speed(uint16_t speed);
    void forward();
    void backward();
    void stop();
    uint16_t get_speed();
    motor_state_t get_state();

  private:
    TIM_HandleTypeDef*  _htim;
    uint32_t            _channel;
    GPIO_TypeDef*       _dir_port1;
    uint16_t            _dir_pin1;
    GPIO_TypeDef*       _dir_port2;
    uint16_t            _dir_pin2;
    uint16_t            _speed;
    uint8_t             _direction;
    motor_state_t       _state;

    void _apply_pwm();
};

#endif
