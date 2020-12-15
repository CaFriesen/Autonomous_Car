#include <Arduino.h>
/*  M1C3 project 2, 3 & 4
 *  Rick Jooren, Malik Tujeehut, Clarence Felten, Camiel Friesen, Jasper van Kol
 *  
 *  Sensor analoog / digitaal data:
 *  0    / 0    is wit
 *  1023 / 1    is zwart
 *  
 *  Motor data:
 *  A = linker motoren
 *  B = rechter motoren
 */ 

//Motor controller
#define DirA 12
#define DirB 13
#define PwmA 3
#define PwmB 11
#define BrkA 9
#define BrkB 8
#define CurA A0
#define CurB A1

//Sensoren digitaal
#define Sen1D 22
#define Sen2D 23
#define Sen3D 24
#define Sen4D 25
#define Sen5D 26
#define Sen6D 27
#define Sen7D 28
#define Sen8D 29

//Sensoren analoog
#define Sen1A A2
#define Sen2A A3
#define Sen3A A4
#define Sen4A A5
#define Sen5A A8
#define Sen6A A9
#define Sen7A A10
#define Sen8A A11

//Sensoren activeren
#define Sen1P 30
#define Sen2P 31
#define Sen3P 32
#define Sen4P 33
#define Sen5P 34
#define Sen6P 35
#define Sen7P 36
#define Sen8P 37

//LED
#define Led1R 49
#define Led1G 48
#define Led1B 47

#define Led2R 46
#define Led2G 45
#define Led2B 44

#define Led3R 43
#define Led3G 42
#define Led3B 41

#define Led4R 40
#define Led4G 39
#define Led4B 38

//Knopje
#define But1S = 21
#define But1L = 20

struct RGBColor
{
  int Red;
  int Green;
  int Blue;
  int Alpha;
};

class Led
{
private:
  int Red, 
      Green, 
      Blue;
public:
  Led(int red, int green, int blue);

  void Color(RGBColor color)
  {
    Red = color.Red;
    Green = color.Green;
    Blue = color.Blue;
  }

  ~Led();
};

Led::Led(int red, int green, int blue)
{
  Red = red;
  Green = green;
  Blue = blue;
}

Led::~Led()
{
}

class Motor
{
private:
  uint8_t MotorSpeed,
          PinMotorSpeed,
          PinMotorDirection,
          PinMotorAmpereMesurement,
          PinMotorBreak;
  bool    MotorDirection;

public:
  Motor(uint8_t pinMotorSpeed, uint8_t pinMotorDirection, uint8_t pinMotorAmpereMesurement, uint8_t pinMotorBreak, bool motorDirection);
  
  void setSpeed(uint8_t motorSpeed)
  {
    MotorSpeed = motorSpeed;
    analogWrite(PinMotorSpeed, MotorSpeed);
    digitalWrite(PinMotorDirection, MotorDirection);
  }

  void setSpeed(uint8_t motorSpeed, bool reverse)
  {    
    MotorSpeed = motorSpeed;
    if (reverse)
    {
      digitalWrite(PinMotorDirection, !MotorDirection);
    }
    else
    {
      digitalWrite(PinMotorDirection, MotorDirection);
    }
    analogWrite(PinMotorSpeed, MotorSpeed);
  }
  
  void setMotorDirection(bool direction)
  {
    MotorDirection = direction;
  }

  void flipDirection()
  {
    MotorDirection = !MotorDirection;
  }

  void brake()
  {
    digitalWrite(PinMotorBreak, HIGH);
  }

  void letBrakeLose()
  {
    digitalWrite(PinMotorBreak, LOW);
  }

  ~Motor();
};

Motor::Motor(uint8_t pinMotorSpeed, uint8_t pinMotorDirection, uint8_t pinMotorAmpereMesurement, uint8_t pinMotorBreak, bool motorDirection)
{
  PinMotorSpeed = pinMotorSpeed;
  PinMotorDirection = pinMotorDirection;
  PinMotorAmpereMesurement = pinMotorAmpereMesurement;
  PinMotorBreak = pinMotorBreak;
  MotorDirection = motorDirection;
  MotorSpeed = 0;

  pinMode(PinMotorSpeed, OUTPUT);
  pinMode(PinMotorDirection, OUTPUT);
  pinMode(PinMotorAmpereMesurement, OUTPUT);
  pinMode(PinMotorBreak, OUTPUT);

}

Motor::~Motor()
{
}


Motor motorA(PwmA, DirA, CurA, BrkA, true);
Motor motorB(PwmB, DirB, CurB, BrkB, false);

enum state
{
  LINE,
  PAUSE,
  START,
  STOP
};

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  motorA.setSpeed(100);
  motorB.setSpeed(100);

  delay(1000);
  
  motorA.setSpeed(100, true);
  motorB.setSpeed(100, true);
  delay(1000);
  
  motorA.setSpeed(0);
  motorB.setSpeed(0);
  delay(1000);

}