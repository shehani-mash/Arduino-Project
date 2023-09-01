#include <LiquidCrystal.h>
//const int rs=13, en=12, d4=4, d5=3, d6=2, d7=1;
LiquidCrystal lcd(13, 12, 4, 3, 2, 1);
int ldr = A0;
int lamp = 7;
int lightValue = 0;
void setup() {
lcd.begin(16, 2);
pinMode(lamp, OUTPUT);
}
void loop() {
lightValue = analogRead(ldr);
if(lightValue < 370){
digitalWrite(lamp, 1);
lcd.clear();
lcd.setCursor(0,0 );
lcd.print("Resistence is : ");
lcd.setCursor(0,1 );
lcd.print(lightValue);
}
else{
digitalWrite(lamp, 0);
lcd.clear();
lcd.setCursor(0,0 );
lcd.print("Resistence is : ");
lcd.setCursor(0,1 );
lcd.print(lightValue);
}
delay(500);
}
