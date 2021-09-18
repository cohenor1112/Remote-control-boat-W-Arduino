//laser on/off:

#define PIN_INPUT_LASER 22
#define PIN_OUTPUT_LASER 23

int Flag_Input_Laser;

void setup()
{
  pinMode(PIN_INPUT_LASER,INPUT);
  pinMode(PIN_OUTPUT_LASER,OUTPUT);
}

void loop() 
{
  Flag_Input_Laser = digitalRead(PIN_INPUT_LASER);
  digitalWrite(PIN_OUTPUT_LASER,Flag_Input_Laser);
}
