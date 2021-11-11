#include "Robot.h"

Robot bot(3,2,4,5,6,7);    // objek bot(ENA, IN1, IN2, ENB, IN3, IN4)

void setup() {
  Serial.begin(9600);
  bot.aturSpeed(60);  // speed X %
}

void loop() {
  bot.maju(1000);
  delay(1000);
  bot.putarKiri(1000);
  delay(1000);
}
