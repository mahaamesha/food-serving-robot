#include "Robot.h"

const byte lineL = A0;  //sensor garis kiri
const byte lineR = A1;  //sensor garis kanan, bebas pin analog/digital

const byte btnSubmit = 12;
const byte btnReset = 11;
const byte indikatorLED = 10;
bool goFlag = 0;

bool rute[3];  //{berangkat, meja1, kembali}
char riwayatAksi[10];

Robot bot(3,2,4,5,6,7);    //objek bot(ENA, IN1, IN2, ENB, IN3, IN4)

void tukarChar(char arr[], char panjang);
void ikutLine(char aksi[]);
bool sampaiCek(char arr[], byte panjang);
void resetArray(char arr[], byte panjang);

void setup() {
  Serial.begin(9600);
  
  pinMode(lineL, INPUT);
  pinMode(lineR, INPUT);

  pinMode(btnSubmit, INPUT);
  pinMode(indikatorLED, OUTPUT);
  
  bot.aturSpeed(60);  //speed X %
}

void loop() {

  //nanti setelah robot sampai tujuan, sudah dibuat goFlag=0
  //button SUBMIT ditekan, ubah goFlag=1
  bool btnSubmitState = digitalRead(btnSubmit);
  if(btnSubmitState == 0){
    digitalWrite(indikatorLED, !goFlag);
    goFlag = !goFlag;
  }
  //Serial.print("btnSubmitState: "); Serial.println(btnSubmitState);

  //hapus meja tujuan, kalau salah input
  bool btnResetState = digitalRead(btnReset);
  if(btnResetState == 0){
    //mejaTujuan[jumlahMeja] = {0,0,0,...}
  }

  //setelah True, jalan ikuti line. goFlag diatur btnSubmit
  if(goFlag == 1){
    ikutLine(riwayatAksi);
    for(int i=0;i<10;i++){
      Serial.print(riwayatAksi[i]); Serial.print(" ");
    }
    
    bool sampaiFlag = sampaiCek(riwayatAksi,10);
    if(sampaiFlag == 1){
      digitalWrite(indikatorLED, LOW);
      goFlag = 0; //jika berhenti lama, maka sampai tujuan
      resetArray(riwayatAksi, 10);
    }
  }
  Serial.print("goFlag: "); Serial.println(goFlag);
  Serial.println(); delay(300);
}

void tukarChar(char arr[], char panjang){ //1,2,3,4 -> 4,1,2,3
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
  bool valLineL = digitalRead(lineL); // 0 -> putih
  bool valLineR = digitalRead(lineR); // 1 -> hitam

  /*Serial.print("lineL: ");
  Serial.println(valLineL);
  Serial.print("lineR: ");
  Serial.println(valLineR);*/

  tukarChar(aksi, 10);  //1,2,3,4 -> 4,1,2,3
  
  if (valLineL + valLineR == 0){
    aksi[0] = 'F';
    bot.maju(2);
  }
  else if(valLineL + valLineR == 2){
    aksi[0] = 'S';
    bot.stop(2);
  }
  else if(valLineL == 1 && valLineR == 0){
    aksi[0] = 'L';
    bot.belokKiri(2);
  }
  else if(valLineL == 0 && valLineR == 1){
    aksi[0] = 'R';
    bot.belokKanan(2);
  }
  //Serial.println(aksi[0]);
}

bool sampaiCek(char arr[], byte panjang){
  for(int i=0; i<panjang; i++){
    if(arr[i] != 'S') return 0;
  }
  return 1; //semua 'S' -> sudah sampai tujuan
}

void resetArray(char arr[], byte panjang){
  for(int i=0; i<panjang; i++){
    arr[i] = "";
  }
}
