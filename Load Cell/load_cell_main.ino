#include <core_build_options.h>
#include <swRTC.h>

#include "HX711.h"
#include <SPI.h>
#include <SD.h>
#include <time.h>

#define led 10
#define sd 4
#define DOUT  3 
#define CLK  2

HX711 scale(DOUT, CLK);
float calibration_factor = -21000;

swRTC rtc;

File myFile;

//*오늘 날짜로 바꾸기 *//
int y,m,d = (2022,10,24);

void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);

  rtc.stopRTC();
  rtc.setTime(0,0,0);
  rtc.setDate(d,m,y);
  rtc.startRTC();
  Serial.begin(9600);
  
  scale.set_scale(calibration_factor); 
  scale.tare();
  long zero_factor = scale.read_average(); 
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
  
  if (!SD.begin(sd)) { 
    Serial.println("initialization failed!"); 
    while(1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("COUNT.txt", FILE_WRITE);
  // myFile.println("start");
  // myFile.println("unit: g");
  myFile.println("time force");
  myFile.close(); 
}

void loop() {
  // start = clock();
  digitalWrite(led, HIGH);
  
  Serial.print("Reading: ");
  float m = scale.get_units()*100;
  myFile = SD.open("COUNT.txt", FILE_WRITE);
  if(myFile){
    Serial.print(rtc.getHours(), DEC);
    Serial.print(":");
    Serial.print(rtc.getMinutes(), DEC);
    Serial.print(":");
    Serial.print(rtc.getSeconds(), DEC);

    Serial.print(" "); 
    Serial.print(m,3);
    Serial.print("g");
    Serial.println();

    myFile.print(rtc.getHours());
    myFile.print(":");
    myFile.print(rtc.getMinutes());
    myFile.print(":");
    myFile.print(rtc.getSeconds());
    myFile.print(" ");
    myFile.println(m);
    myFile.close(); 
  }
  // end = clock();
  // result = (double)(end-start);
  // Serial.print(result/CLOCKS_PER_SEC);
  // Serial.print("ms");
  // Serial.println();
}
