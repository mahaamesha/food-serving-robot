/* 
 * Source File
 * Brain.cpp
*/

#include "Brain.h"

// Konstruktor
// [class]::[konstruktor](param)   lihat file.h
Brain::Brain(byte lineLL, byte lineL, byte lineR, byte lineRR)
{
  _iface = new Interface(13,12,11,10);
  _motor = new Motor(3,2,4,5,6,7);
  _mylcd = new Display(0x27,16,2,8,9);

  pinMode(lineLL, INPUT);
  pinMode(lineL, INPUT);
  pinMode(lineR, INPUT);
  pinMode(lineRR, INPUT);

  Brain::lineLL = lineLL;
  Brain::lineL = lineL;
  Brain::lineR = lineR;
  Brain::lineRR = lineRR;
}

void Brain::resetArray(char arr[]){
  byte panjang = 10;
  for(int i=0; i<panjang; i++){
    arr[i] = '\0';
  }
}

void Brain::tukarChar(char arr[]){ //1,2,3,4 -> 4,1,2,3
  byte panjang = 10;
  char temp;
  panjang -= 1;
  for(int i=0; i<panjang; i++){
    temp = arr[panjang-i];
    arr[panjang-i] = arr[panjang-1-i];
    arr[panjang-1-i] = temp;
  }
}

void Brain::starterGo(structBrain *brainState){
  while((*brainState).baseFlag == 1) {  //starter, keluar dari garis stop
    Serial.print("Starter... ");
    (*brainState).riwayatAksi[0] = '*';
    
    byte laju = _motor -> ambilSpeed();
    _motor -> aturSpeed(laju*2/3);
    while(digitalRead(lineL) + digitalRead(lineR) == 2) _motor -> maju(2);
    _motor -> aturSpeed(laju);
    (*brainState).baseFlag = 0; //terminator
    Serial.println("Done");
  }
}

void Brain::ikutLine(structBrain *brainState){ //setiap gerakan disimpan di char aksi
  unsigned long lama = 14; //hold setiap aksi selama X ms | 17 agak kecepatan
  bool valLineL = digitalRead(lineL); // 0 -> putih
  bool valLineR = digitalRead(lineR); // 1 -> hitam

  Brain::tukarChar((*brainState).riwayatAksi);  //1,2,3,4 -> 4,1,2,3
  
  //ikuti garis
  
  if (valLineL + valLineR == 0){
    if((*brainState).parkingFlag == 0){
      (*brainState).riwayatAksi[0] = 'F';
      _motor -> maju(lama);
    }else{  //handle parking
      (*brainState).riwayatAksi[0] = 'B';
      _motor -> mundur(lama);
    }
  }
  else if(valLineL + valLineR == 2){
    if((*brainState).baseFlag == 1) {  //starter, keluar dari garis stop
      (*brainState).riwayatAksi[0] = '*';
      
      byte lajuStarter = _motor -> ambilSpeed();
      _motor -> aturSpeed(lajuStarter*2/3);
      while(digitalRead(lineL) + digitalRead(lineR) == 2) _motor -> maju(2);
      _motor -> aturSpeed(lajuStarter);
      
      (*brainState).baseFlag = 0; //terminator
    }
    else{
      (*brainState).riwayatAksi[0] = 'S';
      _motor -> stop(lama*2);
    }
  }
  else if(valLineL == 1 && valLineR == 0){
    (*brainState).riwayatAksi[0] = 'L';
    _motor -> putarKiri(lama);
  }
  else if(valLineL == 0 && valLineR == 1){
    (*brainState).riwayatAksi[0] = 'R';
    _motor -> putarKanan(lama);
  }

  Serial.print("Riwayat aksi... ");
  for(int i=0;i<10;i++){Serial.print((*brainState).riwayatAksi[i]); Serial.print(" ");}
  Serial.println();
}

void Brain::keepForward(byte *num, structBrain *brainState){
  //terobos pertigaan |- saat menuju tujuan
  while(digitalRead(lineRR) == 1 && (*brainState).backFlag == 0){ //hitam
    Serial.print("Lurus terus menuju meja pertama... ");
    byte laju = _motor -> ambilSpeed();
    _motor -> aturSpeed(laju*2/3);

    while(digitalRead(lineRR) == 1){
      _motor -> maju(1);
      while(digitalRead(lineL) == 1) _motor -> belokKiri(1);
    }

    _motor -> aturSpeed(laju);
    Serial.println("Done");
  }//sudah keluar dari obstacle pertigaan |- saat menuju tujuan
  
  //terobos pertigaan -| jika bukan meja tujuan
  //tujuan=2, isTujuan=0 (saat baru sampai di pertigaan meja 1) while-->TRUE
  while(digitalRead(lineLL) == 1 && *num != (*brainState).tujuan-1){
    Serial.print("Lurus terus menuju meja selanjutnya... ");
    byte laju = _motor -> ambilSpeed();
    _motor -> aturSpeed(laju*2/3);

    while(digitalRead(lineLL) == 1) {
      _motor -> maju(1);
      while(digitalRead(lineR) == 1) _motor -> putarKanan(1);
    }

    *num += 1;  //isTujuan=1, tujuan=2
    _motor -> aturSpeed(laju);
    Serial.println("Done");
  }//sudah keluar dari obstacle pertigaan -| saat menuju meja tujuan
}

void Brain::isPertigaanKiri(byte *num, structBrain *brainState){
  while(digitalRead(lineLL) == 1){ //jika ketemu pertigaan -| yg menuju meja x
    *num += 1;

    if(*num == (*brainState).tujuan){
      Serial.print("Pertigaan yang benar, belok kiri... ");
      byte laju = _motor -> ambilSpeed();
      _motor -> aturSpeed(laju*2/3);
      while(digitalRead(lineLL) == 1) {
        _motor -> maju(2);  //1: hitam
        if((*brainState).tujuan != 255){  //handle saat menuju meja saja
          while(digitalRead(lineR) == 1) _motor -> putarKanan(1);
        }
      }
      while(digitalRead(lineLL) == 0) _motor -> belokKiri(1);
      while(digitalRead(lineLL) == 1) _motor -> belokKiri(1);
      while(digitalRead(lineL) == 1) _motor -> putarKiri(1);
      
      if((*brainState).backFlag == 0){  //handle belok kiri menuju meja
        *num = 254;  //terminasi saat menuju tujuan
      }
      else { //handle belok kiri ke jalur utama, menuju base (STEP4)
        *num = 0;  //terminasi saat menuju base
      }

      _motor -> aturSpeed(laju);
      Serial.println("Done");
    }//sudah belok kiri
  }
}

void Brain::turnRight(byte *num){
  //obstacle belokan L kanan saat menuju base
  while(digitalRead(lineRR) == 1){ //hitam
    Serial.print("Belok kanan... ");
    byte laju = _motor -> ambilSpeed();
    _motor -> aturSpeed(laju*2/3);

    while(digitalRead(lineRR) == 1) {
      _motor -> maju(1);
      while(digitalRead(lineL) == 1) _motor -> putarKiri(1);
    }
    while(digitalRead(lineRR) == 0) _motor -> belokKanan(1);
    while(digitalRead(lineRR) == 1) _motor -> belokKanan(1);
    while(digitalRead(lineR) == 1) _motor -> belokKanan(1);

    _motor -> aturSpeed(laju);
    Serial.println("Done");

    *num = 1;  //obstacle dilewati
  }
}

void Brain::turnLeft(byte *num){
  //obstacle belokan T kiri saat menuju base
  while(digitalRead(lineLL) + digitalRead(lineRR) == 2){
    Serial.print("Belok kiri... ");
    byte laju = _motor -> ambilSpeed();
    _motor -> aturSpeed(laju*2/3);

    while(digitalRead(lineLL) == 1) _motor -> maju(1);
    while(digitalRead(lineLL) == 0) _motor -> belokKiri(1);
    while(digitalRead(lineLL) == 1) _motor -> belokKiri(1);
    while(digitalRead(lineL) == 1) _motor -> putarKiri(1);

    _motor -> aturSpeed(laju);
    Serial.println("Done");

    *num = 0; //semua obstacle menuju base telah dilewati
  }
}

bool Brain::semuaS(char arr[]){
  byte panjang = 10;
  for(int i=0; i<panjang; i++){
    if(arr[i] != 'S') return 0;
  }
  return 1; //semua 'S' -> sudah sampai tujuan
}

void Brain::cekSampai(structBrain *brainState){
  bool sampaiCekState = Brain::semuaS((*brainState).riwayatAksi);
  if(sampaiCekState == 1){  //jika riwayatAksi[] semua 'S'
    Brain::resetArray((*brainState).riwayatAksi);
    (*brainState).goFlag = 0;  //terminasi
    
    if((*brainState).parkingFlag == 0){
      //handle sampai tujuan
      if ((*brainState).backFlag == 0) digitalWrite(13, LOW);
      //handle sampai base
      else if ((*brainState).backFlag == 1) (*brainState).backFlag = 0; //terminasi
    }
    else {  //handle parking
      (*brainState).parkingFlag = 0; //terminasi
      digitalWrite(13, LOW);
    }

    Serial.println("Cek sampai... True");
  }
}

void Brain::putarBalik(){
  Serial.print("Putar balik... ");
  byte laju = _motor -> ambilSpeed();
  _motor -> aturSpeed(laju*2/3);
  
  while(digitalRead(lineR) == 1) _motor -> maju(1); //1: hitam
  while(digitalRead(lineRR) == 0) _motor -> putarKanan(1);
  while(digitalRead(lineRR) == 1) _motor -> putarKanan(1);

  _motor -> aturSpeed(laju);
  Serial.println("Done");
}

void Brain::structInfo(structBrain brainState){
  Serial.println("\n======= INFO =======");
  Serial.println("baseFlag\t:" + String(brainState.baseFlag));
  Serial.println("goFlag\t\t:" + String(brainState.goFlag));
  Serial.println("parkingFlag\t:" + String(brainState.parkingFlag));
  Serial.println("backFlag\t:" + String(brainState.backFlag));
  Serial.println("inputFlag\t:" + String(brainState.inputFlag));
  Serial.println("tujuan\t\t:" + String(brainState.tujuan));
  Serial.println("====== ENDINFO =====\n");
}