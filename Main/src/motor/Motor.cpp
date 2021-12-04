/* 
 * Source File
 * Motor.cpp
*/

#include "Motor.h"

// Konstruktor
// [class]::[konstruktor](param)   lihat file.h
Motor::Motor(byte pinENA, byte pinIN1, byte pinIN2,
             byte pinENB, byte pinIN3, byte pinIN4)
{
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENB, OUTPUT);
  pinMode(pinIN3, OUTPUT);
  pinMode(pinIN4, OUTPUT);

  // menyamakan variabel di file.h dan file.cpp
  Motor::pinENA = pinENA;
  Motor::pinIN1 = pinIN1;
  Motor::pinIN2 = pinIN2;
  Motor::pinENB = pinENB;
  Motor::pinIN3 = pinIN3;
  Motor::pinIN4 = pinIN4;

  laju = 50;     // default 50%
}

void Motor::maju(unsigned long lama){
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

void Motor::mundur(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, HIGH);
  delay(lama);
  stop(0);
}

void Motor::stop(unsigned long lama){
  analogWrite(pinENA, 0);
  analogWrite(pinENB, 0);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW);
  delay(lama);
}

void Motor::belokKiri(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, nilaiAnalog);
  analogWrite(pinENB, 0);
  digitalWrite(pinIN1, HIGH); //roda kanan
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, LOW);
  digitalWrite(pinIN4, LOW);
  delay(lama);
  stop(0);
}

void Motor::belokKanan(unsigned long lama){
  byte nilaiAnalog = laju / 100.0 * 255;
  analogWrite(pinENA, 0);
  analogWrite(pinENB, nilaiAnalog);
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, LOW);
  digitalWrite(pinIN3, HIGH); //roda kiri
  digitalWrite(pinIN4, LOW);
  delay(lama);
  stop(0);
}

void Motor::putarKiri(unsigned long lama){
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

void Motor::putarKanan(unsigned long lama){
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

void Motor::aturSpeed(byte laju){
  if(laju <= 100){  // maksimal speed 100%
    //mengatur nilai laju dari kelas Robot = laju parameter
    Motor::laju = laju;
  }
}

byte Motor::ambilSpeed(){
  //return nilai laju dari kelas Robot
  return laju;
}
