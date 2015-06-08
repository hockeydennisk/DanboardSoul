/**
   File: DanboardSoul.ino
  
   System:         Arduino IDE
   Component Name: Danboard Soul
   Status:         Version 0.1 
   Language: C
 
   License: MIT License 
   (c) Copyright DenDen Make Studio 2015
  
   Author: Dennis Kuo
   E-Mail: denden.robot@gmail.com
  
   Description: The boday language and soul for DenDen Make Handmake Danboard Bot.
   Change History:
   Date         Author       Description
   2015-06-04   Dennis Kuo   First commit to Github.
*/

#include <Servo.h>

#define SERVOS_TOTAL  4

#define HEAD    0
#define LEFT    1
#define RIGHT   2
#define BODY    3

#define SV_POT  0  //Potentiometer
#define SV_PIN  1  //servoPin
#define SV_MIN  2  //min
#define SV_MAX  3  //max
#define SV_INI  4  //initialAngle
#define SV_PMIN  5  //pot_min
#define SV_PMAX  6  //pot_max

#define InputButton  4
#define IDLE_COUNT_LIMIT  20

int servoConfig[SERVOS_TOTAL][7] = {
  // Potentiometer,  servoPin,   min,    max,      initialAngle,   pot_min,  pot_max
    { 0,               5,        30,    120,       90,             270,      610},       //A0 ,  Head
    { 1,               9,        40,    180,       90,             270,      610},       //A1 ,  Left
    { 2,              10,        10,    150,       90,             270,      610},       //A2 ,  Right
    { 3,              11,        45,    145,       95,             270,      610},       //A3 ,  Body
};

Servo danboardServo[SERVOS_TOTAL];
int aiValue[SERVOS_TOTAL] = {0};
int idleCount[SERVOS_TOTAL] = {0};
//int newAiValue = 0;
//int mapAiValue = 0;

int currentMode = 0;  //0:Auto Mode, 1:Mimic Mode, 2:Dancer Mode
#define MODE_AUTO   0
#define MODE_MIMIC  1
#define MODE_DANCE  2

/*Dance Song 01: Little Apple*/
#define TEMPO_MAX_01  10
int danceTempo01 = 100;  //ms
int danceAngle01[SERVOS_TOTAL][TEMPO_MAX_01] = {
    //Head
    { 90,  110,  90,  70,  50,  30,  50,  70,  90,  90},
    //Left Hand
    { 90,  110,  90,  70,  50,  30,  50,  70,  90,  90},
    //Right Had
    { 90,  110,  90,  70,  50,  30,  50,  70,  90,  90},
    //Body
    { 90,  110,  90,  70,  50,  30,  50,  70,  90,  90},
};


void setup() {
  // put your setup code here, to run once:
  pinMode(InputButton, INPUT);
  
  Serial.begin(115200);
  Serial.println("Danboard Bot ready...");
  
  //init Mode
  currentMode = MODE_AUTO; //MODE_MIMIC;  //MODE_DANCE;

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //for(int i=0; i<SERVOS_TOTAL; i++) {
    //danboardServo[i].detach();
  //}
  //int inputValue = digitalRead(InputButton);
  //Serial.println(inputValue);
  
  switch(currentMode)
  {
    case MODE_AUTO:
        /*Auto Mode: Auto Test Every Parts*/
        HeadPartTest();
        LeftHandTest();
        RightHandTest();
        BodyPartTest();
        break;

    case MODE_MIMIC:
        /*Mimic Mode: Every Parts acted according to Analog Input Potentiometer value.*/
        /*Only control Left/Right hands for Kaohsiung mini Maker Faire*/
        rotateServoWithAnalogInput(LEFT);
        rotateServoWithAnalogInput(RIGHT);
        delay(100);
        break;

    case MODE_DANCE:
        danceSong01();
        //danceSong02();
        delay(50);
        break;

    default:
        break;
  }

#if 0  
  /*Auto Mode: Auto Test Every Parts*/
  if (currentMode == MODE_AUTO)
  {
    HeadPartTest();
    LeftHandTest();
    RightHandTest();
    BodyPartTest();
  }

  /*Mimic Mode: Every Parts acted according to Analog Input Potentiometer value.*/
  /*Only control Left/Right hands for Kaohsiung mini Maker Faire*/
  if (currentMode == MODE_MIMIC)
  {
    rotateServoWithAnalogInput(LEFT);
    rotateServoWithAnalogInput(RIGHT);
    delay(100);
  }
  
  if (currentMode == MODE_DANCE)
  {
    delay(50);
  }
#endif

}

void HeadPartTest()
{
    
  /*Head*/
  #if 1
  danboardServo[HEAD].attach(servoConfig[HEAD][SV_PIN]);
  #if 1
  for(int pos = servoConfig[HEAD][SV_MIN]; pos < servoConfig[HEAD][SV_MAX]; pos += 1)
  {
      danboardServo[HEAD].write(pos);
      delay(10);
  }
  #endif
  danboardServo[HEAD].write(servoConfig[HEAD][SV_INI]);
  delay(500);
  danboardServo[HEAD].detach();
  #endif
}

void LeftHandTest()
{
  /*Left Hand*/
  #if 1
  danboardServo[LEFT].attach(servoConfig[LEFT][SV_PIN]);
  #if 1
  for(int pos = servoConfig[LEFT][SV_MIN]; pos < servoConfig[LEFT][SV_MAX]; pos += 1)
  {
      danboardServo[LEFT].write(pos);
      delay(10);
  }
  #endif
  danboardServo[LEFT].write(servoConfig[LEFT][SV_INI]);
  delay(500);
  danboardServo[LEFT].detach();
  #endif

}

void RightHandTest()
{
      /*Right Hand*/
  #if 0
  danboardServo[RIGHT].attach(servoConfig[RIGHT][SV_PIN]);
  #if 1
  for(int pos = servoConfig[RIGHT][SV_MIN]; pos < servoConfig[RIGHT][SV_MAX]; pos += 1)
  {
      danboardServo[RIGHT].write(pos);
      delay(10);
  }
  #endif
  danboardServo[RIGHT].write(servoConfig[RIGHT][SV_INI]);
  delay(500);
  danboardServo[RIGHT].detach();
  #endif

  delay(500);

  /*Right Hand Reverse*/
  #if 1
  danboardServo[RIGHT].attach(servoConfig[RIGHT][SV_PIN]);
  #if 1
  for(int pos = servoConfig[RIGHT][SV_MAX]; pos > servoConfig[RIGHT][SV_MIN]; pos -= 1)
  {
      danboardServo[RIGHT].write(pos);
      delay(10);
  }
  #endif
  danboardServo[RIGHT].write(servoConfig[RIGHT][SV_INI]);
  delay(500);
  danboardServo[RIGHT].detach();
  #endif

}

void BodyPartTest()
{
    /*Body*/
  #if 1
  danboardServo[BODY].attach(servoConfig[BODY][SV_PIN]);
  #if 1
  for(int pos = servoConfig[BODY][SV_MIN]; pos < servoConfig[BODY][SV_MAX]; pos += 1)
  {
      danboardServo[BODY].write(pos);
      delay(10);
  }
  #endif
  //danboardServo[BODY].write(servoConfig[BODY][SV_INI]);
  delay(500);
  danboardServo[BODY].detach();
  #endif

  /*BODY Reverse*/
  #if 1
  danboardServo[BODY].attach(servoConfig[BODY][SV_PIN]);
  #if 1
  for(int pos = servoConfig[BODY][SV_MAX]; pos > servoConfig[BODY][SV_MIN]; pos -= 1)
  {
      danboardServo[BODY].write(pos);
      delay(10);
  }
  #endif
  danboardServo[BODY].write(servoConfig[BODY][SV_INI]);
  delay(500);
  danboardServo[BODY].detach();
  #endif
}

void rotateServoWithAnalogInput(int component)
{
  int newAiValue;
  int mapAiValue;
  
  newAiValue = analogRead(servoConfig[component][SV_POT]);
  if ((newAiValue - aiValue[component]) < 5)
  {
    idleCount[component]++;
  }
  else
  {
    //reset idle count
    idleCount[component] = 0;
  }

  if (idleCount[component] > IDLE_COUNT_LIMIT)
  {
    Serial.println("into Idle state...");
    danboardServo[component].detach();
  }
  else
  {
    aiValue[component] = newAiValue;
    //Serial.println("into Working state...");

    mapAiValue = map(newAiValue, servoConfig[component][SV_PMIN], servoConfig[component][SV_PMAX], servoConfig[component][SV_MIN], servoConfig[component][SV_MAX]);
    Serial.print("Component:");
    Serial.print(component);
    Serial.print(":  ");
    Serial.print(newAiValue);
    Serial.print("->");
    Serial.println(mapAiValue);

    if (!danboardServo[component].attached()) {
      danboardServo[component].attach(servoConfig[component][SV_PIN]);
    }
    danboardServo[component].write(mapAiValue);
    //delay(100);
    //danboardServo[component].detach();
  }
}

void danceSong01()
{
  //Dancing Begin
  for(int i=0; i<SERVOS_TOTAL; i++) {
    danboardServo[i].attach(servoConfig[i][SV_PIN]);
  }

  for(int i=0;  i<TEMPO_MAX_01;  i++)
  {
    danboardServo[HEAD].write(danceAngle01[HEAD][i]);
    danboardServo[LEFT].write(danceAngle01[LEFT][i]);
    danboardServo[RIGHT].write(danceAngle01[RIGHT][i]);
    danboardServo[BODY].write(danceAngle01[BODY][i]);
    delay(danceTempo01);
  }

  //Dancing End
  for(int i=0; i<SERVOS_TOTAL; i++) {
    danboardServo[i].detach();
  }

}


