#include "HX711.h"

#define DOUT  3 
#define CLK  2   

HX711 scale(DOUT, CLK);

float calibration_factor = -21000;    

void setup() {
  Serial.begin(9600);
  
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); 
  Serial.print("Zero factor: "); 
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); 

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3);
  Serial.print(" *100g"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}
