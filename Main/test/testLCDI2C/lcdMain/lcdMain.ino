//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

const byte btnNum = 10;  //jika A6 A7, khusus analog pin
const byte btnReset = 11;
const byte btnSubmit = 12;
const byte indikatorLED = 13;

bool goFlag = 0;

byte tujuan = 0;

int timer = 0;

LiquidCrystal_I2C lcd(0x27,16,2);
HCSR04 hc(8,9);

void setup()
{
  Serial.begin(9600);
  pinMode(btnNum, INPUT);
  pinMode(btnReset, INPUT);
  pinMode(btnSubmit, INPUT);
  pinMode(indikatorLED, OUTPUT);

  //setupTimer();

  displayInit();
  //lcd.init();
  //lcdStart();
}


void loop()
{
  bool btnNumState = digitalRead(btnNum);
  bool btnSubmitState = digitalRead(btnSubmit);
  bool btnResetState = digitalRead(btnReset);
  if(btnNumState == 0){
    tujuan += 1;
    delay(200);
  }
  else if(btnSubmitState == 0){
    digitalWrite(indikatorLED, !goFlag);
    goFlag = !goFlag;
    delay(200);
  }
  else if(btnResetState == 0){
    tujuan = 0;
    textReset();
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
  else if(tujuan != 0 && goFlag == 0){ //proses input
    textNumTujuan(tujuan);
  }
  Serial.println(jarak);
  
  if(goFlag == 1){
    //robot jalan + menampilkan tujuannya
    textServing(tujuan);
  }
  else{
    lcd.clear();
  }
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

void textServing(byte numTujuan){
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(4,0);
  lcd.print("HIDANGAN");
  lcd.setCursor(5,1);
  lcd.print("MEJA ");
  lcd.print(numTujuan);
}

void textReset(){
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("TUJUAN");
  lcd.setCursor(4,1);
  lcd.print("DI-RESET");
  delay(500);
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

void displayInit(){
  lcd.init();
  lcdStart();
}

void setupTimer(){
  TCCR0A = (1<<WGM01); //Set the CTC mode
  OCR0A = 0xF9; //Value for ORC0A for 1ms 
  
  TIMSK0 |= (1<<OCIE0A); //Set the interrupt request
  sei(); //Enable interrupt
  
  TCCR0B |= (1<<CS01);  //Set the prescale 1/64 clock
  TCCR0B |= (1<<CS00);  //011 -> CS02 CS01 CS00
}

ISR(TIMER0_COMPA_vect){    //This is the interrupt request
  timer++;
}

void delayTimer(int t){
  if(timer >= t){  //hitung selama t*1ms
    timer = 0;  //clear
    Serial.print("DELAY TIMER "); Serial.print(t); Serial.println(" ms");
  }
}
