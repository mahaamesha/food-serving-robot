/* 
 * Source File
 * Interface.cpp
*/

#include "Interface.h"

struct structBrain {
  bool baseFlag;
  bool goFlag;
  bool parkingFlag;
  bool backFlag;
  bool inputFlag;

  byte tujuan;
  char riwayatAksi[10];
};

// Konstruktor
// [class]::[konstruktor](param)   lihat file.h
Interface::Interface(byte indikatorLED, byte btnSubmit, byte btnReset, byte btnNum)
{
  _mylcd = new Display(0x27,16,2,8,9);

  pinMode(indikatorLED, OUTPUT);
  pinMode(btnSubmit, INPUT);
  pinMode(btnReset, INPUT);
  pinMode(btnNum, INPUT);

  Interface::indikatorLED = indikatorLED;
  Interface::btnSubmit = btnSubmit;
  Interface::btnReset = btnReset;
  Interface::btnNum = btnNum;
}

void Interface::inputDiBase(structBrain *brainState){
  bool btnNumState = digitalRead(btnNum);
  bool btnResetState = digitalRead(btnReset);
  bool btnSubmitState = digitalRead(btnSubmit);
  if(btnNumState == 0){   //handle input tujuan
    (*brainState).tujuan += 1;  //tujuan ke meja i
    Serial.print("MEJA TUJUAN: "); Serial.println((*brainState).tujuan);
    delay(500);
  }
  else if(btnResetState == 0){  //hapus meja tujuan, jika salah input
    (*brainState).tujuan = 0;
    _mylcd -> textReset();
  }
  else if(btnSubmitState == 0){ //ubah goFlag ^= 1
    digitalWrite(indikatorLED, !(*brainState).goFlag);
    (*brainState).goFlag = !(*brainState).goFlag;
    delay(500);
    (*brainState).inputFlag = 0;  //terminasi infinite loop
  }
}

void Interface::inputDiTujuan(structBrain *brainState){
  bool btnSubmitState = digitalRead(btnSubmit);
  if (btnSubmitState == 0){
    digitalWrite(indikatorLED, HIGH);
    (*brainState).goFlag = 1;
    (*brainState).inputFlag = 0;  //terminasi 1
    (*brainState).backFlag = 1;   //terminasi 2
  }
}