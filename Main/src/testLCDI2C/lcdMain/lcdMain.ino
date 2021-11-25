//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

const byte btnNum = A3;  //jika A6 A7, khusus analog pin

byte tujuan;

LiquidCrystal_I2C lcd(0x27,16,2);
HCSR04 hc(8,9);

void setup()
{
  Serial.begin(9600);
  pinMode(btnNum, INPUT);
  
  lcd.init();                      // initialize the lcd 
  lcdStart();
}


void loop()
{
  bool btnNumState = digitalRead(btnNum);
  if(btnNumState == 0){
    tujuan += 1;
    delay(200);
  }

  float jarak = hc.dist();  //dalam cm
  if(jarak < 50 && tujuan == 0){
    textInputNum();
  }
  else if (jarak > 50 && tujuan == 0){
    textStandby();
    delay(1000);  //backlight nyala sebentar
    lcd.noBacklight();
  }
  else if(tujuan != 0){
    textNumTujuan(tujuan);
  }
  Serial.println(jarak);
}

void textStandby(){
  lcd.setCursor(2,0);
  lcd.print("RBL PROJECT!");
  lcd.setCursor(0,1);
  lcd.print("FOOD SERVING RBT");
}

void textInputNum(){
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("SELECT");
  lcd.setCursor(1,1);
  lcd.print("TABLE NUMBER!!");
  lcd.blink();
  delay(100); //jeda untuk blink cursor
}

void textNumTujuan(byte numTujuan){
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("ANTAR KE");
  lcd.setCursor(4,1);
  lcd.print("TUJUAN:");
  lcd.print(numTujuan);
  lcd.blink();
  delay(100); //jeda untuk blink cursor
}

void lcdStart(){
  for(int i=0; i<3; i++){
    lcd.backlight();
    textStandby();
    delay(500);
    lcd.noBacklight();
    delay(200);
  }
}
