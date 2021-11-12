#include "Robot.h"

const byte lineL = 12;  //sensor garis kiri
const byte lineR = 11;  //sensor garis kanan

Robot bot(3,2,4,5,6,7);    // objek bot(ENA, IN1, IN2, ENB, IN3, IN4)
void ikutLine();

void setup() {
  Serial.begin(9600);
  
  pinMode(lineL, INPUT);
  pinMode(lineR, INPUT);
  
  bot.aturSpeed(60);  // speed X %
}

void loop() {
  ikutLine();
}

void ikutLine(){
  byte valLineL = digitalRead(lineL); // 0 -> putih
  byte valLineR = digitalRead(lineR); // 1 -> hitam

  Serial.print("L: ");
  Serial.println(valLineL);
  Serial.print("R: ");
  Serial.println(valLineR);
  
  if (valLineL + valLineR == 0){
    Serial.println("MAJU");
    bot.maju(2);
  }
  else if(valLineL + valLineR == 2){
    Serial.println("STOP");
    bot.stop(2);
  }
  else if(valLineL == 1 && valLineR == 0){
    Serial.println("BELOK KIRI");
    bot.belokKiri(2);
  }
  else if(valLineL == 0 && valLineR == 1){
    Serial.println("BELOK KANAN");
    bot.belokKanan(2);
  }
  
  Serial.println(); delay(1000);
}
