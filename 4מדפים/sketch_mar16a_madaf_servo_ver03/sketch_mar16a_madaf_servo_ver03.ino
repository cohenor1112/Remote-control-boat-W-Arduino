//madaf_servo_ver03 = moving servo angle n a discreet manner in angles 65(90-25):115(90+25)

#include <Servo.h>

//ANGLES DEFINES:
#define MADAF_SERVO_INIT_ANGLE 90
#define MADAF_SERVO_MADAF_SERVO_MAX_ANGLE_TO_ROTATE 25
#define MADAF_SERVO_ANGLE_HOP 5

//ESP INPUTS DEFINES:
#define ESP_MIN_INPUT 0
#define ESP_MAX_INPUT 10

//FUNCTIONS SIGNATURES:
void create_arr_dyn(float *arr, int arr_min_value, int arr_max_value, float hop_len);
void Angle_(void);

//PINS DEFINES:
//INPUTS PINS:
int MADAF_SERVO_PIN_INPUT_FROM_ESP = A9; //analog data from esp
int MADAF_SERVO_PIN_INPUT_FROM_SERVO = 9; //digital pin in arduino

//---------------------------

// Create a servo object
Servo Madaf_Servo;

int MADAF_SERVO_MIN_ANGLE;
int MADAF_SERVO_MAX_ANGLE;
int madaf_servo_angle_arr_len ;
float madaf_servo_angle_arr[100];
unsigned long esp_input;
int madaf_servo_angle_index_arr;
float madaf_servo_angle;

void setup()
{
  Serial.begin(9600);

  MADAF_SERVO_MIN_ANGLE = MADAF_SERVO_INIT_ANGLE - MADAF_SERVO_MADAF_SERVO_MAX_ANGLE_TO_ROTATE ;
  MADAF_SERVO_MAX_ANGLE = MADAF_SERVO_INIT_ANGLE + MADAF_SERVO_MADAF_SERVO_MAX_ANGLE_TO_ROTATE ;

  //create an arr of angles
  madaf_servo_angle_arr_len = (MADAF_SERVO_MAX_ANGLE - MADAF_SERVO_MIN_ANGLE) / MADAF_SERVO_ANGLE_HOP + 1;
  create_arr_dyn(&madaf_servo_angle_arr[0], MADAF_SERVO_MIN_ANGLE, MADAF_SERVO_MAX_ANGLE, MADAF_SERVO_ANGLE_HOP);
  //  for (int i = 0; i < madaf_servo_angle_arr_len; i++)
  //  {
  //    Serial.println(madaf_servo_angle_arr[i]);
  //  }

  // We need to attach the servo to the used pin number
  Madaf_Servo.attach(MADAF_SERVO_PIN_INPUT_FROM_SERVO);
  madaf_servo_angle = MADAF_SERVO_INIT_ANGLE;
  Madaf_Servo.write(madaf_servo_angle);
  delay(7000);
}

void loop()
{
  Angle_();
}

void Angle_()
{
  esp_input = pulseIn(MADAF_SERVO_PIN_INPUT_FROM_ESP, HIGH);
  Serial.println(esp_input);
  if (esp_input >= 0 && esp_input <= 80)
  {
    madaf_servo_angle_index_arr = 0;
  }
  else if (esp_input >= 90 && esp_input <= 140)
  {
   madaf_servo_angle_index_arr = 1;
  }
  else if (esp_input >= 150 && esp_input <= 220)
  {
   madaf_servo_angle_index_arr = 2;
  }
  else if (esp_input >= 230 && esp_input <= 350)
  {
   madaf_servo_angle_index_arr = 3;
  }
  else if (esp_input >= 360 && esp_input <= 450)
  {
   madaf_servo_angle_index_arr = 4;
  }
  else if (esp_input >= 460 && esp_input <= 540)
  {
   madaf_servo_angle_index_arr = 5;
  }
  else if (esp_input >= 550 && esp_input <= 610)
  {
   madaf_servo_angle_index_arr = 6;
  }
  else if (esp_input >= 620 && esp_input <= 700)
  {
   madaf_servo_angle_index_arr = 7;
  }  
  else if (esp_input >= 710 && esp_input <= 800)
  {
   madaf_servo_angle_index_arr = 8;
  }
  else if (esp_input >= 810 && esp_input <= 900)
  {
   madaf_servo_angle_index_arr = 9;
  }
  else if (esp_input >= 900 && esp_input <= 1000)
  {
   madaf_servo_angle_index_arr = 10;
  }

  Serial.println(madaf_servo_angle_index_arr);
  madaf_servo_angle = madaf_servo_angle_arr[madaf_servo_angle_index_arr];
  Serial.println(madaf_servo_angle);
  Madaf_Servo.write(madaf_servo_angle);

  delay(100);
}

void create_arr_dyn(float *arr, int arr_min_value, int arr_max_value, float hop_len)
{
  int arr_size = (arr_max_value - arr_min_value) / hop_len + 1;
  //Insert data off the array
  for (int i = 0; i < arr_size; i++)
  {
    arr[i] = arr_min_value + i * hop_len;
    Serial.println(arr[i]);
  }
  delay(5000);
}

//---------------------------------------------------------------------------------------------

//float madaf_servo_angle_arr_angle_hop_2_5 = {65,67.5,70,72.5,75,77.5,80,82.5,85,87.5,90,92.5,95,97.5,100,102.5,105,107.5,110,112.5,115}; //TRY TO DO IT DYNAMICLY FROM MADAF_SERVO_MIN_ANGLE TO MADAF_SERVO_MAX_ANGLE WITH MADAF_SERVO_ANGLE_HOP
//float madaf_servo_angle_arr_angle_hop_5 = {65,70,75,80,85,90,95,100,105,110,115};//TRY TO DO IT DYNAMICLY FROM MADAF_SERVO_MIN_ANGLE TO MADAF_SERVO_MAX_ANGLE WITH MADAF_SERVO_ANGLE_HOP
