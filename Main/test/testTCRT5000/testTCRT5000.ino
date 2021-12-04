/*
 * TESTING TCRT5000
 * Hitam, sinyal=1
 * Putih, sinyal=0
 * Kalau terbaca sebagai analog input, 0-1024
 */

//const int PIN_SENSOR = 2;
const int PIN_SENSOR = A7;

void setup(){
  Serial.begin(9600);
  pinMode(PIN_SENSOR, INPUT);
}

void loop(){
  //int nilaiPin = digitalRead(PIN_SENSOR);
  int nilaiPin = analogRead(PIN_SENSOR);
  Serial.println(nilaiPin);
  delay(250);
}
 
