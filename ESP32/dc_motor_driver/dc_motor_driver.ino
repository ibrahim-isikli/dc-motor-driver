#include "dc_motor_driver.h"

motor right_motor(04, 13, 14);
motor left_motor(25,  2, 12);

uint32_t last_tick  = 0;
bool going_forward  = true;

void setup()
{
    Serial.begin(115200);

    right_motor.set_speed(700);
    left_motor.set_speed(700);

    right_motor.forward();
    left_motor.forward();

    last_tick = millis();
    Serial.println("FORWARD");
}

void loop()
{
    if (millis() - last_tick >= 3000)
    {
        last_tick = millis();

        if (going_forward)
        {
            right_motor.backward();
            left_motor.backward();
            Serial.println("BACKWARD");
        }
        else
        {
            right_motor.forward();
            left_motor.forward();
            Serial.println("FORWARD");
        }

        going_forward = !going_forward;
    }
}