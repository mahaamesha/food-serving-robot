/* 
 * Header File
 * Robot.h
*/

#ifndef ROBOT_H
#define ROBOT_H

#include "Arduino.h"

class Robot{
  public:
    Robot(byte pinENA, byte pinIN1, byte pinIN2,
          byte pinENB, byte pinIN3, byte pinIN4);
    void maju(unsigned long lama);
    void mundur(unsigned long lama);
    void stop(unsigned long lama);
    void belokKanan(unsigned long lama);
    void belokKiri(unsigned long lama);
    void putarKanan(unsigned long lama);
    void putarKiri(unsigned long lama);
        
    void aturSpeed(byte laju);
    byte ambilSpeed();
    
  private:
    byte pinENA, pinIN1, pinIN2, 
         pinENB, pinIN3, pinIN4;
    byte laju;
};

#endif
