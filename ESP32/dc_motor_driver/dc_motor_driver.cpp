#include "esp32-hal-ledc.h"
#include "driver/ledc.h"
#include "dc_motor_driver.h"

// constructor
motor::motor(uint8_t pwm_pin, uint8_t dir_pin1, uint8_t dir_pin2, uint32_t freq, uint8_t resolution)
{
  _pwm_pin =  pwm_pin;
  _dir_pin1 = dir_pin1;
  _dir_pin2 = dir_pin2;
  _resolution = resolution;
  _max_duty = (1<<resolution) - 1; //  convert 10 bit, resolution is uint8_t 
  _speed  = 0;
  _direction = MOTOR_FORWARD;
  _state = MOTOR_STATE_IDLE;

  // direction pins are output and low
  pinMode(_dir_pin1,OUTPUT);
  pinMode(_dir_pin2,OUTPUT);
  digitalWrite(_dir_pin1, LOW);
  digitalWrite(_dir_pin2, LOW);

  // set pwm channel and pwm start
  ledcAttach(_pwm_pin, freq, _resolution);
  ledcWrite(_pwm_pin,0);
}


void motor::set_speed(uint16_t speed)
{

}

void motor::forward()
{
  
}


void motor::backward()
{

}

void motor::stop()
{

}

uint16_t motor::get_speed()
{
  return _speed;
}

motor_state_t motor::get_state()
{
  return _state;
}