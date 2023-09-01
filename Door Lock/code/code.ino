#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

//define the symbol on the button of the key pad
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}      
};

byte rowPin[ROWS] = {3,2,1,0}; //connect to the row pinouts of the keypad
byte colPin[COLS] = {6,5,4}; //connect to the column pinout of the keypad

//intialize an instance of class new keypad
Keypad myKeypad = Keypad(makeKeymap(hexaKeys), rowPin, colPin, ROWS, COLS);

//motor driver set pin with arduino
int In1 = A0;
int In2 = A1;
int EA = A2;

//create password
char password[4] = {'1','2','3','4'};
char userPress[4];

void setup(){
  //pin configuration  
  pinMode(7, OUTPUT); //buzzer pin
  pinMode(EA, OUTPUT); // motor pins
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT); 

  digitalWrite(In1, 0);
  digitalWrite(In2, 0);

  lcd.begin(16,2); //set up the lcd's number of columns and rows
  lcd.setCursor(1,0);
  lcd.println("Welcome TO");
  lcd.setCursor(2,1);
  lcd.println("My Door Lock");
  delay(800);
  lcd.clear();
  lcd.println("press*");
    

}

void loop(){

  byte keyCount = 0;
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY) {
    if (keypressed == '*') {
        boolean a = 1;
        lcd.clear();
        lcd.println("Enter Password");
        lcd.setCursor(0,1);

        while (a) {
          keypressed = myKeypad.getKey();

          if (keypressed != NO_KEY) {
            userPress[keyCount] = keypressed;
            lcd.println("*");
            keyCount++;

            if (keyCount == 4) a=0;   
            }  
        }
        check_password();
      }              
    }    
  }

void dire(){
  analogWrite(EA, 225);

  //turn on motor A
  digitalWrite(In1, 1);
  digitalWrite(In2, 0);
  delay(1000);

  //off
  digitalWrite(In1, 0);
  digitalWrite(In2, 0); 
  delay(100); 

  //change direction motor A
  digitalWrite(In1, 0);
  digitalWrite(In2, 1);
  delay(1000); 
   

}

//to turn off the motor
void motorOff(){
  digitalWrite(In1, 0);
  digitalWrite(In2, 0);  
}

//to check password
void check_password(){
  byte b = 0;
  for (int i=0; i<4; i++) {
    if (userPress[i] == password[i]) {
      b++;
    } 
  }
  if (b == 4) {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.println("Valid Password");
    lcd.setCursor(1,2);
    lcd.println("Door Unlocked");

    dire(); //run the motor
    delay(3000); 
    lcd.clear();
    lcd.println("Door Locked");
    motorOff(); //off the motor
    delay(2000);
    lcd.clear();
    lcd.println("Press*");                  
 }
else {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.println("Invalid Password");
  lcd.setCursor(3,2);
  lcd.println("Blocked");

  //buzzer on
  tone(7, 1000);
  digitalWrite(7, HIGH);
  delay(2000);
  noTone(7);
  digitalWrite(7, LOW);
  lcd.clear();
  lcd.println("press*"); 
  }   
}
