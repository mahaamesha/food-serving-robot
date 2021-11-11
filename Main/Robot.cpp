/* 
 * Source File
 * Robot.cpp
*/

#include "Robot.h"

// Konstruktor
// [class]::[fungsi](param)   lihat file.h
Robot::Robot(byte pinENA, byte pinIN1, byte pinIN2,
             byte pinENB, byte pinIN3, byte pinIN4)
{
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  // menyamakan variabel di file.h dan file.cpp
  Robot::pinENA = pinENA;
  Robot::pinIN1 = pinIN1;
  Robot::pinIN2 = pinIN2;
  Robot::pinENB = pinENB;
  Robot::pinIN3 = pinIN3;
  Robot::pinIN4 = pinIN4;

  laju = 50;     // default 50%
}

void Robot::maju(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  delay(lama);
  stop(0);
}

void Robot::mundur(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, LOW);
  analogWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, LOW);
  analogWrite(pinIN4, HIGH);
  delay(lama);
  stop(0);
}

void Robot::stop(unsigned long lama){
  analogWrite(pinENA, 0);
  analogWrite(pinENB, 0);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW);
  delay(lama);
}

void Robot::belokKanan(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, 0);
  analogWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW);
  delay(lama);
  stop(0);
}

void Robot::belokKiri(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, 0);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  delay(lama);
  stop(0);
}

void Robot::putarKanan(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
  delay(lama);
  stop(0);
}

void Robot::putarKiri(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, HIGH);
  digitalWrite(pinIN4, LOW);
  delay(lama);
  stop(0);
}

void Robot::aturSpeed(byte laju){
  if(laju <= 100){  // maksimal speed 100%
    // menyamakan variabel di file.h dan file.cpp
    Robot::laju = laju;
  }
}

byte Robot::ambilSpeed(){
  return laju;
}
