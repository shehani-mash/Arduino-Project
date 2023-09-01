#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);
int sensor=A0;
float temp;
float tempc;
float tempf;
int fan =7;
void setup() {
 pinMode(A0,INPUT);
 pinMode(fan,OUTPUT);
 lcd.begin(16,2);
}
void loop() {
 temp = analogRead(sensor);
 tempc=(temp*4.88)/10;
 lcd.setCursor(0,0);
 lcd.print("Temp in C = ");
 lcd.print(tempc);
 
 //convert to farenheit
 tempf=(tempc*1.8)+32;
 lcd.setCursor(0,1);
 lcd.print("Temp in F: ");
 lcd.print(tempf);
 if (tempc >= 25){
 digitalWrite(fan,HIGH);
 }
 else{
 digitalWrite(fan,LOW);
 }
}
