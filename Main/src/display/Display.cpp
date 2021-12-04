/* 
 * Source File
 * Display.cpp
*/

#include "Display.h"

// Konstruktor
// [class]::[konstruktor](param)   lihat file.h
Display::Display(byte address, byte kolom, byte baris,
                 byte trig, byte echo)
                 //:_lcd( new LiquidCrystal_I2C(address, kolom, baris) ),
                 //_hc( new HCSR04(trig, echo) )    //ini juga bisa
{ 
  address = 0x27;
  kolom = 16;
  baris = 2;  //set default value
  
  _lcd = new LiquidCrystal_I2C(address, kolom, baris);
  _hc = new HCSR04(trig, echo);

  Display::address = address;
  Display::kolom = kolom;
  Display::baris = baris;
  Display::trig = trig;
  Display::echo = echo;
}

//TEXT METHODS
void Display::textStandby(){
  _lcd -> setCursor(0,0);
  _lcd -> print("<-RBL PROJECT!->");
  _lcd -> setCursor(0,1);
  _lcd -> print("FOOD SERVING RBT");
  Serial.println("STANDBY");
}

void Display::textAskInput(){
  _lcd -> clear();
  _lcd -> backlight();
  _lcd -> setCursor(5,0);
  _lcd -> print("SELECT");
  _lcd -> setCursor(1,1);
  _lcd -> print("TABLE NUMBER!!");
  Serial.println("SELECT TABLE NUMBER!!");
  _lcd -> blink();
  delay(100); //jeda untuk blink cursor
}

void Display::textNumTujuan(byte numTujuan){
  _lcd -> clear();
  _lcd -> backlight();
  _lcd -> setCursor(4,0);
  _lcd -> print("ANTAR KE");
  _lcd -> setCursor(4,1);
  _lcd -> print("TUJUAN:");
  _lcd -> print(numTujuan);
  Serial.print("ANTAR KE TUJUAN:"); Serial.println(numTujuan);
  _lcd -> blink();
  delay(100); //jeda untuk blink cursor
}

void Display::textServing(byte numTujuan){
  _lcd -> clear();
  _lcd -> setCursor(3,0);
  _lcd -> print("DELIVER TO");
  _lcd -> setCursor(5,1);
  _lcd -> print("TABLE ");
  _lcd -> print(numTujuan);
  _lcd -> noBlink();
  Serial.print("DELIVER TO TABLE "); Serial.println(numTujuan);
}

void Display::textMenujuBase(){
  _lcd -> clear();
  _lcd -> setCursor(3,0);
  _lcd -> print("!!SERVED!!");
  _lcd -> setCursor(1,1);
  _lcd -> print("MENUJU KE BASE");
  Serial.println("MENUJU KE BASE");
}

void Display::textReset(){
  _lcd -> clear();
  _lcd -> backlight();
  _lcd -> setCursor(5,0);
  _lcd -> print("TUJUAN");
  _lcd -> setCursor(4,1);
  _lcd -> print("DI-RESET");
  Serial.println("TUJUAN DI-RESET");
  delay(500);
}

void Display::textPerintahAmbil(byte numTujuan){
  _lcd -> clear();
  _lcd -> setCursor(3,0);
  _lcd -> print("< TABLE" + String(numTujuan) + " >");
  _lcd -> setCursor(1,1);
  _lcd -> print("ENJOY THE FOOD");
  Serial.println("<TABLE" + String(numTujuan) + "> ENJOY THE FOOD");
}

void Display::textPerintahBalik(){
  _lcd -> clear();
  _lcd -> setCursor(1,0);
  _lcd -> print("PLEASE TAKE IT");
  _lcd -> setCursor(0,1);
  _lcd -> print("THEN CLCK SUBMIT");
  Serial.println("PLEASE TAKE IT, THEN CLICK SUBMIT");
  _lcd -> blink();
  delay(100); //jeda untuk blink cursor
}

void Display::textKembali(){
  _lcd -> clear();
  _lcd -> setCursor(3,0);
  _lcd -> print("< SERVED >");
  _lcd -> setCursor(3,1);
  _lcd -> print("GO TO BASE");
  Serial.println("<SERVED> | GO TO BASE");
  _lcd -> noBlink();
}

void Display::lcdStart(){
  for(int i=0; i<2; i++){
    _lcd -> backlight();
    textStandby();
    delay(500);
    _lcd -> noBacklight();
    delay(200);
  }
}

//MAIN FUNCTIONS
void Display::displayInit(){
  _lcd -> init();
  Display::lcdStart();
}

void Display::standby(byte _tujuan){
  float jarak = _hc -> dist();  //dalam cm
  if(jarak < 50 && _tujuan == 0){
    Display::textAskInput();
  }
  else if (jarak > 50 && _tujuan == 0){
    Display::textStandby();
    Serial.print("DISTANCE: "); Serial.println(jarak);
    delay(500);  //backlight nyala sebentar
    _lcd -> noBacklight();
  }
  else if(_tujuan != 0 && _tujuan != 255){ //proses input
    Display::textNumTujuan(_tujuan);
  }
}
