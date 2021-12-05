/* 
 * Header File
 * Brain.h
*/

#ifndef BRAIN_H
#define BRAIN_H

#include "Arduino.h"
#include "../interface/Interface.h"
#include "../motor/Motor.h"
#include "../display/Display.h"

struct structBrain {
  bool baseFlag;
  bool goFlag;
  bool parkingFlag;
  bool backFlag;
  bool inputFlag;

  byte tujuan;
  char riwayatAksi[10];
};

class Brain {
  public:
    Brain(byte lineLL, byte lineL, byte lineR, byte lineRR);

    structBrain idleBrain = {1,0,0,0,1,0,{'\0'}};

    void resetArray(char arr[]);
    void tukarChar(char arr[]);

    void starterGo(structBrain *brainState);
    void ikutLine(structBrain *brainState);
    void keepForward(byte *num, structBrain *brainState);
    void isPertigaanKiri(byte *num, structBrain *brainState);
    void turnRight(byte *num);
    void turnLeft(byte *num);
    bool semuaS(char arr[]);
    void cekSampai(structBrain *brainState);
    void putarBalik();

    void structInfo(structBrain brainState);

  private:
    byte lineLL, lineL, lineR, lineRR;
    Interface *_iface;
    Motor *_motor;
    Display *_mylcd;
};

#endif