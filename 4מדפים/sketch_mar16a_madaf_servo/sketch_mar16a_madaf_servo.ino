//madaf_servo_ver01 = moving servo angle continuesly in angles 65(90-25):115(90+25)
#include <Servo.h>

//value defines:
#define MADAF_SERVO_INIT_ANGLE 90
#define MADAF_SERVO_MIN_ANGLE 65
#define MADAF_SERVO_MAX_ANGLE 115

//pins defines:
//input pins:
int MADAF_SERVO_PIN_INPUT_FROM_ESP = A9; //analog data from esp
int MADAF_SERVO_PIN_INPUT_FROM_SERVO = 9; //digital pin in arduino
//output pins:

//value parameters:
unsigned long madaf_servo_angle;

// Create a servo object
Servo Madaf_Servo;

void Angle_(void);

void setup()
{
  Serial.begin(9600);
  // We need to attach the servo to the used pin number
  Madaf_Servo.attach(MADAF_SERVO_PIN_INPUT_FROM_SERVO);
  madaf_servo_angle = MADAF_SERVO_INIT_ANGLE;
  Madaf_Servo.write(madaf_servo_angle);
}

void loop()
{
  Angle_();
}

void Angle_()
{
  madaf_servo_angle = pulseIn(MADAF_SERVO_PIN_INPUT_FROM_ESP, HIGH);
  if (madaf_servo_angle < MADAF_SERVO_MIN_ANGLE)
  {
    madaf_servo_angle = MADAF_SERVO_MIN_ANGLE;
  }
  if (madaf_servo_angle > MADAF_SERVO_MAX_ANGLE)
  {
    madaf_servo_angle = MADAF_SERVO_MAX_ANGLE;
  }
  Madaf_Servo.write(madaf_servo_angle);
  Serial.println(pulseIn(MADAF_SERVO_PIN_INPUT_FROM_ESP, HIGH));
  delay(100);
}
