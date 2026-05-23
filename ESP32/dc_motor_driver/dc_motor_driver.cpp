#ifndef DC_MOTOR_DRIVER_H
#define DC_MOTOR_DRIVER_H

#include <Arduino.h>
#include <stdint.h>

#define MOTOR_FORWARD   0u
#define MOTOR_BACKWARD  1u

typedef enum
{
  MOTOR_STATE_IDLE = 0u,
  MOTOR_STATE_RUNNING,
  MOTOR_STATE_FAULT
}motor_state_t;

class motor
{
  public:
    motor(uint8_t pwm_pin, uint8_t ledc_ch, uint8_t dir_pin1, uint8_t dir_pin2, uint32_t freq = 1000, uint8_t resolution = 10);
    void set_speed(uint16_t speed);
    void forward();
    void backward();
    void stop();
    uint16_t get_speed();
    motor_state_t get_state();

  private:
    uint8_t _pwm_pin;
    uint8_t _ledc_ch;
    uint8_t _dir_pin1;
    uint8_t _dir_pin2;
}

#endif