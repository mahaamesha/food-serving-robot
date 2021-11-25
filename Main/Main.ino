#include "Robot.h"

const byte lineLL = A0;  //sensor garis paling kiri
const byte lineL = A1;  //sensor garis kiri
const byte lineR = A2;  //sensor garis kanan
const byte lineRR = A3;  //sensor garis paling kanan

const byte indikatorLED = 13;
const byte btnSubmit = 12;
const byte btnReset = 11;
const byte btnNum = 10;

bool baseFlag = 1;  //posisi start di garis stop
bool goFlag = 0;
bool parkingFlag = 0;

byte tujuan[2] = {0,255};  //{tujuan_i, base}
char riwayatAksi[10];

Robot bot(3,2,4,5,6,7);    //objek bot(ENA, IN1, IN2, ENB, IN3, IN4)

void resetArray(char arr[], byte panjang);
void tukarChar(char arr[], byte panjang);
void ikutLine(char aksi[]);
bool sampaiCek(char arr[], byte panjang);
void putarBalik();

void setup() {
  Serial.begin(9600);
  
  pinMode(lineLL, INPUT);
  pinMode(lineL, INPUT);
  pinMode(lineR, INPUT);
  pinMode(lineRR, INPUT);

  pinMode(indikatorLED, OUTPUT);
  pinMode(btnSubmit, INPUT);
  pinMode(btnReset, INPUT);
  pinMode(btnNum, INPUT);
  
  
  bot.aturSpeed(45);  //default speed 50%
}

void loop() {
  //handle input tujuan robot
  bool btnNumState = digitalRead(btnNum);
  if(btnNumState == 0){
    tujuan[0] = 1;  //tujuan[i] -> meja i
    Serial.print("tujuan[0]="); Serial.println(tujuan[0]);
  }
  
  //hapus meja tujuan, kalau salah input
  bool btnResetState = digitalRead(btnReset);
  if(btnResetState == 0){
    Serial.println("Tujuan direset");
    resetArray(tujuan, 2);  //func(arr[], len)
  }
  
  //button SUBMIT ditekan, ubah goFlag=1
  bool btnSubmitState = digitalRead(btnSubmit);
  if(btnSubmitState == 0){
    digitalWrite(indikatorLED, !goFlag);
    goFlag = !goFlag;
    delay(500);
  }

  //setelah True, jalan ikuti line
  if(goFlag == 1){
    if(tujuan[0] != 0){
      ikutLine(riwayatAksi);
      for(int i=0;i<10;i++){Serial.print(riwayatAksi[i]); Serial.print(" ");}
    }
    else if(tujuan[0] == 0 && tujuan[1] == 255){
      Serial.println("DI TUJUAN");
      putarBalik(); //while loop berhenti saat garis di antara lineL dan lineR
      tujuan[0] = 255; //terminasi agar tidak infinite loop
    }
    
    bool sampaiCekState = sampaiCek(riwayatAksi,10);
    if(sampaiCekState == 1){  //jika riwayatAksi[] semua 'S'
      digitalWrite(indikatorLED, LOW);
      goFlag = 0;
      resetArray(riwayatAksi, 10);
      if(tujuan[0] != 255) tujuan[0] = 0; //bukan berhenti di base
      else {
        Serial.println("DI BASE"); 
        putarBalik(); 
        tujuan[0] = 0;
        parkingFlag = 1;
        while(parkingFlag == 1) {
          ikutLine(riwayatAksi);  //mundur ke garis stop
          for(int i=0;i<10;i++){Serial.print(riwayatAksi[i]); Serial.print(" ");}
          if(sampaiCek(riwayatAksi,10)==1)parkingFlag = 0;
          Serial.println("PARKED");
        }
      }
    }
  } //end if(goFlag==1)
  Serial.print("goFlag: "); Serial.println(goFlag);
  
  Serial.println(); //delay(300);
}

void resetArray(char arr[], byte panjang){
  for(int i=0; i<panjang; i++){
    arr[i] = "";
  }
}

void tukarChar(char arr[], byte panjang){ //1,2,3,4 -> 4,1,2,3
  char temp;
  panjang -= 1;
  for(int i=0; i<panjang; i++){
    temp = arr[panjang-i];
    arr[panjang-i] = arr[panjang-1-i];
    arr[panjang-1-i] = temp;
  }
}

void ikutLine(char aksi[]){
  //setiap gerakan disimpan di char aksi
  unsigned long lama = 15; //hold setiap aksi selama X ms
  bool valLineL = digitalRead(lineL); // 0 -> putih
  bool valLineR = digitalRead(lineR); // 1 -> hitam

  /*Serial.print("lineL: ");
  Serial.println(valLineL);
  Serial.print("lineR: ");
  Serial.println(valLineR);*/

  tukarChar(aksi, 10);  //1,2,3,4 -> 4,1,2,3

  //ikuti garis
  if (valLineL + valLineR == 0){
    if(parkingFlag == 0){
      aksi[0] = 'F';
      bot.maju(lama);
    }else{
      aksi[0] = 'B';
      bot.mundur(lama);
    }
  }
  else if(valLineL + valLineR == 2){
    if(baseFlag == 0){
      aksi[0] = 'S';
      bot.stop(lama);
    }else{
      aksi[0] = '*';  //starter, keluar dari garis stop
      
      byte laju = bot.ambilSpeed();
      bot.aturSpeed(laju/2);
      while(digitalRead(lineL) + digitalRead(lineR) == 2) bot.maju(2);
      bot.aturSpeed(laju);
      
      baseFlag = 0;
    }
    if(parkingFlag == 1) parkingFlag = 0;
  }
  else if(valLineL == 1 && valLineR == 0){
    aksi[0] = 'L';
    bot.putarKiri(lama);
  }
  else if(valLineL == 0 && valLineR == 1){
    aksi[0] = 'R';
    bot.putarKanan(lama);
  }
  //Serial.println(aksi[0]);
}

bool sampaiCek(char arr[], byte panjang){
  for(int i=0; i<panjang; i++){
    if(arr[i] != 'S') return 0;
  }
  return 1; //semua 'S' -> sudah sampai tujuan
}

void putarBalik(){
  Serial.println("PUTAR BALIK");
  byte laju = bot.ambilSpeed();
  bot.aturSpeed(laju*2/3);
  
  //selama lineL masih di hitam
  while(digitalRead(lineL) == 1) bot.putarKanan(2);
  //selama lineL belum ketemu hitam
  while(digitalRead(lineL) != 1) bot.putarKanan(2);
  
  bot.aturSpeed(laju);
}
