// INCLUDES //////////////////////////
#include <LiquidCrystal.h>
#include <Servo.h>

// DEF for Servo
Servo myservo;

// DEF for LED chain

int tDelay = 100;
int latchPin = 15;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 14;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 16;     // (12) DS [S1] on 74HC595

byte leds = 0;



// DEF for LCD Display

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);



// PROTOTYPES //////////////////////////////////////
void updateShiftRegister();
void ledlight(int);
void ledlightUP(int);
void updateShiftRegisterUP();





/////////// SETUP /////////////////////////////////


void setup() 
{
	/* LED chain*/
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
  	/* LCD Display */
   // set the cursor to column 0, line 1
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
  // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  // Print a message to the LCD.
  lcd.print("Please Identify");

    /*Servo*/
  myservo.attach(2);
  myservo.write(90);// move servos to center position -> 90°
}




////////////LOOP////////////////////////

void loop() 
{

  // DOOR OPENNG PROCESS
  leds = 0;
  updateShiftRegister();
  delay(tDelay);

  for (int i = 8; i >= 0; i--) {
    ledlight(i);
  }

  myservo.write(90);// move servos to center position -> 90°
  delay(500);
  myservo.write(30);// move servos to center position -> 60°
  delay(1500);
  myservo.write(90);// move servos to center position -> 90°
  delay(500);
  myservo.write(150);// move servos to center position -> 120°
  delay(500);

  for (int i = 8; i >= 0; i--) {
    ledlightUP(i);
  }
  
}





// FUNCTIONS FOR LED chain

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}
void updateShiftRegisterUP()
{
   digitalWrite(latchPin, HIGH);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, LOW);
}



void ledlight(int port) 
{
    bitSet(leds, port);
    updateShiftRegister();
    delay(tDelay);
}
void ledlightUP(int port) 
{
    bitSet(leds, port);
    updateShiftRegisterUP();
    delay(tDelay);
}
