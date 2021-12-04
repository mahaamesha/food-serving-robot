//Include the LCD Library.
//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte btnNum = A3;

byte tujuan;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
  Serial.begin(9600);
  lcd.init();
  pinMode(btnNum, INPUT);
}

void loop(){
  bool btnNumState = digitalRead(btnNum);
  if(btnNumState == 0){
    tujuan += 1;
    Serial.println(tujuan);
    delay(200);
  }
  
  lcd.setCursor(6,0);
  lcd.print("i: "); lcd.print(tujuan);
}
