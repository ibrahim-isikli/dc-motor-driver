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

void motor::_apply_pwm()
{
  ledcWrite(_pwm_pin,_speed);
}

void motor::set_speed(uint16_t speed)
{
  if(speed>_max_duty)
    speed = _max_duty;
  _speed = speed;
  _apply_pwm();

}

void motor::forward()
{
  _direction = MOTOR_FORWARD;
  _state = MOTOR_STATE_RUNNING;
  digitalWrite(_dir_pin1,HIGH);
  digitalWrite(_dir_pin2,LOW);
  _apply_pwm();
}


void motor::backward()
{
  _direction = MOTOR_BACKWARD;
  _state = MOTOR_STATE_RUNNING;
  digitalWrite(_dir_pin1,LOW);
  digitalWrite(_dir_pin2,HIGH);
  _apply_pwm();
}

void motor::stop()
{
  _state = MOTOR_STATE_IDLE;
  digitalWrite(_dir_pin1,LOW);
  digitalWrite(_dir_pin2,LOW);
  ledcWrite(_pwm_pin,0);
}

uint16_t motor::get_speed()
{
  return _speed;
}

motor_state_t motor::get_state()
{
  return _state;
}