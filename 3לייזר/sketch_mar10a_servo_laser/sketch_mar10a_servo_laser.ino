#include <Servo.h>

#define PIN_INPUT_SERVO_ON_OFF 22

#define PIN_PWM_SERVO 8

#define SERVO_INIT_ANGLE 0
#define SERVO_FINAL_ANGLE 350

Servo servo;
int angle = SERVO_INIT_ANGLE;

void setup() {

  pinMode(PIN_INPUT_SERVO_ON_OFF, INPUT);

  pinMode(39, OUTPUT);
  digitalWrite(39, HIGH);

  servo.attach(PIN_PWM_SERVO);
  servo.write(angle);
}


void loop()
{
  // scan from SERVO_INIT_ANGLE to SERVO_FINAL_ANGLE degrees
  if (digitalRead(PIN_INPUT_SERVO_ON_OFF) == 1)
  {
    for (; angle < SERVO_FINAL_ANGLE; angle++)
    {
      servo.write(angle);
      delay(15);
    }
    angle = SERVO_FINAL_ANGLE;
    servo.write(angle);
  }
  // now scan back from SERVO_FINAL_ANGLE to SERVO_INIT_ANGLE degrees
  else
  {
    for (; angle > SERVO_INIT_ANGLE; angle--)
    {
      servo.write(angle);
      delay(15);
    }
    angle = SERVO_INIT_ANGLE;
    servo.write(angle);
  }
}
