/* 
 * Header File
 * Display.h
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include <HCSR04.h>

class Display{
  public:
    Display(byte address, byte kolom, byte baris,
            byte trig, byte echo);
    void textStandby();
    void textAskInput();
    void textNumTujuan(byte numTujuan);
    void textServing(byte numTujuan);
    void textMenujuBase();
    void textReset();
    void textPerintahAmbil(byte numTujuan);
    void textPerintahBalik();
    void textKembali();
    void lcdStart();
    void displayInit();
    void standby(byte _tujuan);

  private:
    byte address, kolom, baris, trig, echo;
    LiquidCrystal_I2C *_lcd;
    HCSR04 *_hc;
};

#endif
