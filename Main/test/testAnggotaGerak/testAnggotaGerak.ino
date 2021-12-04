#include "Robot1.h"

Robot bot(3,2,4,5,6,7);    //objek bot(ENA, IN1, IN2, ENB, IN3, IN4)

void setup(){
  Serial.begin(9600);

  bot.aturSpeed(60);
}
void loop(){
  //Serial.println("MAJU");
  //bot.maju(20);

  //Serial.println("STOP");
  //bot.stop(3000);

  Serial.println("PUTAR KANAN");
  bot.putarKanan(10);
  
}
