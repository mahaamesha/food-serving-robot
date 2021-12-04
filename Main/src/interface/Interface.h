/* 
 * Header File
 * Interface.h
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include "Arduino.h"
#include "../display/Display.h"

class Interface {
  public:
    Interface(byte indikatorLED, byte btnSubmit, byte btnReset, byte btnNum);
    void inputDiBase(struct structBrain *brainState);
    void inputDiTujuan(struct structBrain *brainState);
  private:
    byte indikatorLED, btnSubmit, btnReset, btnNum;
    Display *_mylcd;
};

#endif