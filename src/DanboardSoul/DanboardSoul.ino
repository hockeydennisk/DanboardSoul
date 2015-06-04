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
int newAiValue = 0;
int mapAiValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(InputButton, INPUT);
  
  Serial.begin(115200);
  Serial.println("Danboard Bot ready...");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //for(int i=0; i<SERVOS_TOTAL; i++) {
    //danboardServo[i].detach();
  //}
  //int inputValue = digitalRead(InputButton);
  //Serial.println(inputValue);
  
  /*Auto Test Every Parts*/
  #if 1
  HeadPartTest();
  LeftHandTest();
  RightHandTest();
  BodyPartTest();
  #endif
  
  #if 0
  newAiValue = analogRead(servoConfig[HEAD][SV_POT]);
  if ((newAiValue - aiValue[HEAD]) < 5)
  {
    idleCount[HEAD]++;
  }
  else
  {
    //reset idle count
    idleCount[HEAD] = 0;
  }

  if (idleCount[HEAD] > IDLE_COUNT_LIMIT)
  {
    Serial.println("into Idle state...");
    danboardServo[HEAD].detach();
  }
  else
  {
    aiValue[HEAD] = newAiValue;
    Serial.println("into Working state...");

    mapAiValue = map(newAiValue, servoConfig[HEAD][SV_PMIN], servoConfig[HEAD][SV_PMAX], servoConfig[HEAD][SV_MIN], servoConfig[HEAD][SV_MAX]);
    Serial.print(newAiValue);
    Serial.print("->");
    Serial.println(mapAiValue);

    if (!danboardServo[HEAD].attached()) {
      danboardServo[HEAD].attach(servoConfig[HEAD][SV_PIN]);
    }
    danboardServo[HEAD].write(mapAiValue);
    delay(100);
    //danboardServo[HEAD].detach();

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
