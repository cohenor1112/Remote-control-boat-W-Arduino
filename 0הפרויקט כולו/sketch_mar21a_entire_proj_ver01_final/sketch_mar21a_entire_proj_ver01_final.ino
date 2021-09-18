//entire proj ver01:

//INCLUDES:
//madaf_servo_ver02: //and for delet
#include <Servo.h>

//wires connections :
//arduino: | esp:
//engines motors:
// A11     | GP5(D1)                        //motor r slider 
// A13     | GP4(D2)                        //motor l slider       
// D12     | ------  //on motor shield      //motor r dir
// D10     | ------  //on motor shield      //motor r speed
// D13     | ------  //on motor shield      //motor l dir
// D11     | ------  //on motor shield      //motor l speed
//madaf_servo:    
// A15     | GP0(D3)                        //madaf servo slider
// D09     | ------  //on motor shield      //madaf servo input
//delet:
// D52     | GP02(D4)                        //delet servo on/off
// D02     | ------  //on motor shield      //delet servo input
//laser:
// D51     | GP12(D5)                       //laser on/off
// D25     | ------                         //laser output

//PINS DEFINES:
//engines motors_ver01
//INPUTS PINS:
int ENGINES_SLIDER_R_PIN_INPUT_FROM_ESP = A11; //analog data from esp //A14 to GP5(D1)
int MOTOR_R_DIR = 12; //motor shield
int MOTOR_R_SPEED = 10; //motor shield
int MOTOR_L_DIR = 13; //motor shield
int MOTOR_L_SPEED = 11; //motor shield
//madaf_servo_ver02:
//INPUTS PINS:
int MADAF_SERVO_PIN_INPUT_FROM_ESP = A15; //analog data from esp //A15 to GP4(D3)
int MADAF_SERVO_PIN_INPUT_FROM_SERVO = 9; //digital pin in arduino (orange wire) //D9 on motor shield
//delet_ver01:
//INPUTS PINS:
#define PIN_INPUT_SERVO_ON_OFF 52 //D52 TO GP02(D4)
#define PIN_PWM_SERVO 2 //(orange wire)
//laser on/off:
#define PIN_INPUT_LASER 51 //D53 TO GP12(D5)
#define PIN_OUTPUT_LASER 25

//VALUE FROM ESP INPUT DEFINES:
//engines motors_ver01
#define ENGINES_MOTORS_REVERSE_TRESH_HOLD 400
#define ENGINES_MOTORS_BREAK_TRESH_HOLD 550
#define ENGINES_MOTORS_FORWARD_TRESH_HOLD 950
//madaf_servo_ver02:
//ESP VALUES INPUTS DEFINES:
#define ESP_MIN_INPUT 20
#define ESP_MAX_INPUT 950

//FUNCTIONS SIGNATURES:
//engines motors_ver01
void reverse_(unsigned long engines_slider_input_from_esp_value);
void break_(unsigned long engines_slider_input_from_esp_value);
void forward_(unsigned long engines_slider_input_from_esp_value);
//madaf_servo_ver02:
void create_arr_dyn(float *arr, int arr_min_value, int arr_max_value, float hop_len);
int arr_size = 0;
void Angle_(void);

//VARIABLES:
//engines motors_ver01
#define MAX_SPEED 255
unsigned long engines_slider_input_from_esp_value = 0;
float motor_speed_unnormalized ;
float motor_speed_normalized;
//madaf_servo_ver02:
//ANGLES DEFINES:
#define MADAF_SERVO_INIT_ANGLE 90
#define MADAF_SERVO_MADAF_SERVO_MAX_ANGLE_TO_ROTATE 35
#define MADAF_SERVO_ANGLE_HOP 5
// Create a servo object
Servo Madaf_Servo;
int MADAF_SERVO_MIN_ANGLE;
int MADAF_SERVO_MAX_ANGLE;
int madaf_servo_angle_arr_len ;
float madaf_servo_angle_arr[100];
int esp_input_hops;
unsigned long esp_input;
int madaf_servo_angle_index_arr;
float madaf_servo_angle;
//delet_ver01:
#define SERVO_INIT_ANGLE 90
#define SERVO_FINAL_ANGLE 0
Servo servo_delet;
int angle = SERVO_INIT_ANGLE;
//laser on/off:
int Flag_Input_Laser;




void setup()
{
  
/////////////////////////////////////////////////
  //engines motors_ver01
  Serial.begin(9600);
  //inputs
  pinMode(ENGINES_SLIDER_PIN_INPUT_FROM_ESP, INPUT);

  //outputs
  pinMode(MOTOR_R_DIR, OUTPUT);
  pinMode(MOTOR_R_SPEED, OUTPUT);
  pinMode(MOTOR_L_DIR, OUTPUT);
  pinMode(MOTOR_L_SPEED, OUTPUT);
  
/////////////////////////////////////////////////

//madaf_servo_ver02:
//  Serial.begin(9600);

  MADAF_SERVO_MIN_ANGLE = MADAF_SERVO_INIT_ANGLE - MADAF_SERVO_MADAF_SERVO_MAX_ANGLE_TO_ROTATE ;
  MADAF_SERVO_MAX_ANGLE = MADAF_SERVO_INIT_ANGLE + MADAF_SERVO_MADAF_SERVO_MAX_ANGLE_TO_ROTATE ;

  //create an arr of angles
  madaf_servo_angle_arr_len = (MADAF_SERVO_MAX_ANGLE - MADAF_SERVO_MIN_ANGLE) / MADAF_SERVO_ANGLE_HOP + 1;
  create_arr_dyn(&madaf_servo_angle_arr[0], MADAF_SERVO_MIN_ANGLE, MADAF_SERVO_MAX_ANGLE, MADAF_SERVO_ANGLE_HOP);
  //  for (int i = 0; i < madaf_servo_angle_arr_len; i++)
  //  {
  //    Serial.println(madaf_servo_angle_arr[i]);
  //  }

  esp_input_hops = (ESP_MAX_INPUT - ESP_MIN_INPUT) / madaf_servo_angle_arr_len;
  
  //Serial.println(esp_input_hops);
  
  // We need to attach the servo to the used pin number
  Madaf_Servo.attach(MADAF_SERVO_PIN_INPUT_FROM_SERVO);
//  madaf_servo_angle = MADAF_SERVO_INIT_ANGLE;
  Madaf_Servo.write(MADAF_SERVO_INIT_ANGLE);
  
/////////////////////////////////////////////////

//delet_ver01:
  pinMode(PIN_INPUT_SERVO_ON_OFF, INPUT);
  
  servo_delet.attach(PIN_PWM_SERVO);
  servo_delet.write(angle);
  
/////////////////////////////////////////////////

//laser on/off:
  pinMode(PIN_INPUT_LASER,INPUT);
  pinMode(PIN_OUTPUT_LASER,OUTPUT);

/////////////////////////////////////////////////  
}

void loop()
{
  
/////////////////////////////////////////////////
  //engines motors_ver01:
  engines_slider_input_from_esp_value = pulseIn(ENGINES_SLIDER_PIN_INPUT_FROM_ESP, HIGH);
    if (engines_slider_input_from_esp_value<=ESP_MIN_INPUT)
  {
    engines_slider_input_from_esp_value = ESP_MIN_INPUT;
  }
  if (engines_slider_input_from_esp_value>=ESP_MAX_INPUT)
  {
    engines_slider_input_from_esp_value = ESP_MAX_INPUT;
  }  
  
  if (engines_slider_input_from_esp_value <= ENGINES_MOTORS_REVERSE_TRESH_HOLD)
  {
    reverse_(engines_slider_input_from_esp_value);
  }
  else if (engines_slider_input_from_esp_value >= ENGINES_MOTORS_REVERSE_TRESH_HOLD && engines_slider_input_from_esp_value < ENGINES_MOTORS_BREAK_TRESH_HOLD)
  {
    break_(engines_slider_input_from_esp_value);
  }
  else
  {
    forward_(engines_slider_input_from_esp_value);
  }
  
/////////////////////////////////////////////////

//madaf_servo_ver02:
  Angle_();
  
/////////////////////////////////////////////////

//delet_ver01:
  // scan from SERVO_INIT_ANGLE to SERVO_FINAL_ANGLE degrees
  if (digitalRead(PIN_INPUT_SERVO_ON_OFF) == HIGH)
  {
    Serial.println("delet servo is on");
    servo_delet.write(SERVO_FINAL_ANGLE);
  }
  else
  {
    Serial.println("delet servo is off");
    servo_delet.write(SERVO_INIT_ANGLE);
  }
  
/////////////////////////////////////////////////

//laser on/off:
  Flag_Input_Laser = digitalRead(PIN_INPUT_LASER);
  if(Flag_Input_Laser == LOW)
  {
    Serial.println("laser is off");
    digitalWrite(PIN_OUTPUT_LASER,LOW);
  }
    if(Flag_Input_Laser == HIGH)
  {
    Serial.println("laser servo is on");
    digitalWrite(PIN_OUTPUT_LASER,HIGH);
  }

/////////////////////////////////////////////////  
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FUNCTIONS:

////////////////////////////////////////////////////////////////////////
//engines motors_ver01:
void reverse_(unsigned long engines_slider_input_from_esp_value)
{
  Serial.print("reverse, speed input slider:");
  Serial.println(engines_slider_input_from_esp_value);

  motor_speed_unnormalized = (ENGINES_MOTORS_REVERSE_TRESH_HOLD - engines_slider_input_from_esp_value);
  Serial.print("motor_speed_unnormalized:");
  Serial.println(motor_speed_unnormalized);
  motor_speed_normalized = (motor_speed_unnormalized / ENGINES_MOTORS_REVERSE_TRESH_HOLD) * 255;
  Serial.print("motor_speed_normalized:");
  Serial.println(motor_speed_normalized);

  if (motor_speed_normalized >= MAX_SPEED)
  {
    motor_speed_normalized = MAX_SPEED;
  }

  digitalWrite(MOTOR_R_DIR, LOW); //reverse
  digitalWrite(MOTOR_L_DIR, LOW); //reverse
  analogWrite(MOTOR_R_SPEED, motor_speed_normalized);
  analogWrite(MOTOR_L_SPEED, motor_speed_normalized);

  Serial.println();
  
}

void break_(unsigned long engines_slider_input_from_esp_value)
{
  Serial.print("breake, speed input slider:");
  Serial.println(engines_slider_input_from_esp_value);

  motor_speed_normalized = 0;
  Serial.print("motor_speed_normalized:");
  Serial.println(motor_speed_normalized);

  analogWrite(MOTOR_R_SPEED, motor_speed_normalized);
  analogWrite(MOTOR_L_SPEED, motor_speed_normalized);

  Serial.println();
}

void forward_(unsigned long engines_slider_input_from_esp_value)
{
  if (engines_slider_input_from_esp_value >= 1023)
  {
    engines_slider_input_from_esp_value = 1023;
  }
  Serial.print("forward, speed input slider:");
  Serial.println(engines_slider_input_from_esp_value);

  motor_speed_unnormalized = (engines_slider_input_from_esp_value - ENGINES_MOTORS_BREAK_TRESH_HOLD);
  Serial.print("motor_speed_unnormalized:");
  Serial.println(motor_speed_unnormalized);
  motor_speed_normalized = (motor_speed_unnormalized / (ENGINES_MOTORS_FORWARD_TRESH_HOLD - ENGINES_MOTORS_BREAK_TRESH_HOLD)) * 255;
  Serial.print("motor_speed_normalized:");
  Serial.println(motor_speed_normalized);

  if (motor_speed_normalized >= MAX_SPEED)
  {
    motor_speed_normalized = MAX_SPEED;
  }

  digitalWrite(MOTOR_R_DIR, HIGH); //forward
  digitalWrite(MOTOR_L_DIR, HIGH); //forward
  analogWrite(MOTOR_R_SPEED, motor_speed_normalized);
  analogWrite(MOTOR_L_SPEED, motor_speed_normalized);
  Serial.println();
}

////////////////////////////////////////////////////////////////////////
//madaf_servo_ver02:
void Angle_()
{  
  esp_input = pulseIn(MADAF_SERVO_PIN_INPUT_FROM_ESP, HIGH);
  Serial.print("angle esp_input ");
  Serial.println(esp_input);
  if (esp_input<ESP_MIN_INPUT)
  {
    esp_input = ESP_MIN_INPUT;
  }
  if (esp_input>ESP_MAX_INPUT)
  {
    esp_input = ESP_MAX_INPUT;
  }  
  madaf_servo_angle_index_arr = (esp_input / esp_input_hops);
  Serial.print("madaf_servo_angle_index_arr ");
  Serial.println(madaf_servo_angle_index_arr);
 if(madaf_servo_angle_index_arr < 0)
  {
    madaf_servo_angle_index_arr=0;
  }
    if(madaf_servo_angle_index_arr >= arr_size)
  {
    madaf_servo_angle_index_arr = arr_size-1;
  }
  madaf_servo_angle = madaf_servo_angle_arr[madaf_servo_angle_index_arr];
  Serial.print("madaf_servo_angle ");
  Serial.println(madaf_servo_angle);
  Madaf_Servo.write(madaf_servo_angle);

  delay(100);

  Serial.println();
}

void create_arr_dyn(float *arr, int arr_min_value, int arr_max_value, float hop_len)
{
  Serial.print("arr_min_value ");
  Serial.println(arr_min_value);
  Serial.print("arr_max_value ");
  Serial.println(arr_max_value);
  Serial.print("hop_len ");
  Serial.println(hop_len);
  int arr_size = (arr_max_value - arr_min_value) / hop_len + 1;
  Serial.print("arr_size ");
  Serial.println(arr_size);
  //Insert data off the array
  for (int i = 0; i < arr_size ; i++)
  {
    arr[i] = arr_min_value + (arr_size-1-i) * hop_len;
    Serial.print("arr[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(arr[i]);
  }
  Serial.println();
  delay(3000);
}

////////////////////////////////////////////////////////////////////////
