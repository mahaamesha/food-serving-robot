#include "src/motor/Motor.h"  //L298N
#include "src/display/Display.h"//LCD_I2C & HCSR04
#include "src/interface/Interface.h"  //Indikator & button
#include "src/brain/Brain.h"  //Line, brain

Interface iface(13,12,11,10); //(led, submit, reset, num)

Brain brain(A0,A1,A2,A3); //(lineLL, L, R, RR)

Motor motor(3,2,4,5,6,7);     //(ENA, IN1, IN2, ENB, IN3, IN4)
Display mylcd(0x27,16,2,8,9); //(address, kolom, baris, trig, echo)

void setup() {
  Serial.begin(9600);
  
  mylcd.displayInit();
  
  motor.aturSpeed(30);  //default speed 50%
}
//(END) SETUP

void loop() {
  structBrain brainState = brain.idleBrain;

  /*STEP1 - standby, pilih tujuan, submit*/
  Serial.println("\n\n====== STEP 1 ======");
  while(brainState.inputFlag == 1){
    iface.inputDiBase(&brainState);
    mylcd.standby(brainState.tujuan);
  }//inputFlag=0

  /*STEP2 - menuju tujuan*/
  Serial.println("\n\n====== STEP 2 ======");
  mylcd.textServing(brainState.tujuan);
  byte isTujuan = 0;  //untuk cek pertigaan -| yg benar bukan
  while(brainState.goFlag == 1){
    if(brainState.tujuan != 0){
      brain.starterGo(&brainState); //while baseFlag=1

      brain.keepForward(brainState.backFlag); //terobos obstacle pertigaan |-

      brain.isPertigaanKiri(&isTujuan, &brainState);  //belok kiri jika nomor meja benar

      brain.ikutLine(&brainState);
    }
    brain.cekSampai(&brainState);  //terminasi
  }//goFlag=0, isTujuan=254

  /*STEP3 - notif ambil makanan*/
  Serial.println("\n\n====== STEP 3 ======");
  mylcd.textPerintahAmbil(brainState.tujuan); //enjoy the food
  while(brainState.backFlag == 0){
    delay(3000);  //delay display textPerintahAmbil
    brainState.tujuan = 255;
    brainState.inputFlag = 1;

    mylcd.textPerintahBalik(); //tekan submit jika sudah
    while(brainState.inputFlag == 1){
      iface.inputDiTujuan(&brainState);
    }//goFlag=1, inputFlag=0, backFlag=1
  }//tujuan=255, isTujuan=254

  /*STEP4 - putar balik, jalan ke base*/
  Serial.println("\n\n====== STEP 4 ======");
  while(brainState.goFlag == 1){
    Serial.print("DI TUJUAN | ");
    brain.putarBalik();

    mylcd.textKembali();
    while(brainState.backFlag == 1){
      //saat isTujuan=tujuan=255, di pertigaan -|, masuk ke jalur utama
      brain.isPertigaanKiri(&isTujuan, &brainState);
      //isTujuan=0, tujuan=255
      
      brain.turnRightLeft();  //saat di obstacle jalur L kanan, dan T kiri di akhir

      brain.keepForward(brainState.backFlag);

      brain.ikutLine(&brainState);

      //cekSampai() bekerja untuk monitoring ikutLine() saja
      brain.cekSampai(&brainState);  //terminasi
    }//goFlag=0, backFlag=0
    
    brainState.parkingFlag = 1;
  }

  /*STEP5 - putar balik, parking*/
  Serial.println("\n\n====== STEP 5 ======");
  while(brainState.parkingFlag == 1){
    Serial.print("DI BASE | ");
    brain.putarBalik();
    
    Serial.println("PARKING");
    while(brainState.parkingFlag == 1){
      brain.ikutLine(&brainState);

      brain.cekSampai(&brainState);  //terminasi
    }//goFlag=0, parkingFlag=0
  }
  //kembali ke perulangan loop --> brainState = brain.idleBrain;
}
//(END) LOOP