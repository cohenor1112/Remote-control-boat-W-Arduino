//engines motors_ver01

//VALUE FROM ESP INPUT DEFINES:
#define ENGINES_MOTORS_REVERSE_TRESH_HOLD 450
#define ENGINES_MOTORS_BREAK_TRESH_HOLD 550
#define ENGINES_MOTORS_FORWARD_TRESH_HOLD 1023

//FUNCTIONS SIGNATURES:
void reverse_(unsigned long engines_slider_input_from_esp_value);
void break_(unsigned long engines_slider_input_from_esp_value);
void forward_(unsigned long engines_slider_input_from_esp_value);

//PINS DEFINES:
//INPUTS PINS:
int ENGINES_SLIDER_PIN_INPUT_FROM_ESP = A8; //analog data from esp
int MOTOR1_DIR = 12;
int MOTOR1_SPEED = 10;
int MOTOR2_DIR = 13;
int MOTOR2_SPEED = 11;

unsigned long engines_slider_input_from_esp_value = 0;
float motor_speed_unnormalized ;
float motor_speed_normalized;

#define MAX_SPEED 100

void setup()
{
  Serial.begin(9600);
  //inputs
  pinMode(ENGINES_SLIDER_PIN_INPUT_FROM_ESP, INPUT);

  //outputs
  pinMode(MOTOR1_DIR, OUTPUT);
  pinMode(MOTOR1_SPEED, OUTPUT);
  pinMode(MOTOR2_DIR, OUTPUT);
  pinMode(MOTOR2_SPEED, OUTPUT);
}

void loop()
{
  engines_slider_input_from_esp_value = pulseIn(ENGINES_SLIDER_PIN_INPUT_FROM_ESP, HIGH);

  if (engines_slider_input_from_esp_value < ENGINES_MOTORS_REVERSE_TRESH_HOLD)
  {
    reverse_(engines_slider_input_from_esp_value);
  }
  else if (engines_slider_input_from_esp_value > ENGINES_MOTORS_REVERSE_TRESH_HOLD && engines_slider_input_from_esp_value < ENGINES_MOTORS_BREAK_TRESH_HOLD)
  {
    break_(engines_slider_input_from_esp_value);
  }
  else
  {
    forward_(engines_slider_input_from_esp_value);
  }
}

////////////////////////////////////////////////////////////////////////
void reverse_(unsigned long engines_slider_input_from_esp_value)
{
  Serial.print("reverse, input slider:");
  Serial.println(engines_slider_input_from_esp_value);

  motor_speed_unnormalized = (ENGINES_MOTORS_REVERSE_TRESH_HOLD - engines_slider_input_from_esp_value);
  Serial.print("motor_speed_unnormalized:");
  Serial.println(motor_speed_unnormalized);
  motor_speed_normalized = (motor_speed_unnormalized / ENGINES_MOTORS_REVERSE_TRESH_HOLD) * 255;
  Serial.print("motor_speed_normalized:");
  Serial.println(motor_speed_normalized);

  if (motor_speed_normalized > MAX_SPEED)
  {
    motor_speed_normalized = MAX_SPEED;
  }

  digitalWrite(MOTOR1_DIR, LOW); //reverse
  digitalWrite(MOTOR2_DIR, LOW); //reverse
  analogWrite(MOTOR1_SPEED, motor_speed_normalized);
  analogWrite(MOTOR2_SPEED, motor_speed_normalized);
  
}

void break_(unsigned long engines_slider_input_from_esp_value)
{
  Serial.print("breake, input slider:");
  Serial.println(engines_slider_input_from_esp_value);

  motor_speed_normalized = 0;
  Serial.print("motor_speed_normalized:");
  Serial.println(motor_speed_normalized);

  analogWrite(MOTOR1_SPEED, motor_speed_normalized);
  analogWrite(MOTOR2_SPEED, motor_speed_normalized);
}

void forward_(unsigned long engines_slider_input_from_esp_value)
{
  if (engines_slider_input_from_esp_value >= 1023)
  {
    engines_slider_input_from_esp_value = 1023;
  }
  Serial.print("forward, input slider:");
  Serial.println(engines_slider_input_from_esp_value);

  motor_speed_unnormalized = (engines_slider_input_from_esp_value - ENGINES_MOTORS_BREAK_TRESH_HOLD);
  Serial.print("motor_speed_unnormalized:");
  Serial.println(motor_speed_unnormalized);
  motor_speed_normalized = (motor_speed_unnormalized / (ENGINES_MOTORS_FORWARD_TRESH_HOLD - ENGINES_MOTORS_BREAK_TRESH_HOLD)) * 255;
  Serial.print("motor_speed_normalized:");
  Serial.println(motor_speed_normalized);

  if (motor_speed_normalized > MAX_SPEED)
  {
    motor_speed_normalized = MAX_SPEED;
  }

  digitalWrite(MOTOR1_DIR, HIGH); //forward
  digitalWrite(MOTOR2_DIR, HIGH); //forward
  analogWrite(MOTOR1_SPEED, motor_speed_normalized);
  analogWrite(MOTOR2_SPEED, motor_speed_normalized);
}
