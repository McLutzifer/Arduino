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
void updateShiftRegisterUP();
void ledlight(int );
void ledlightUP(int );


/////////// SETUP /////////////////////////////////


void setup() 
{
	/* LED chain*/
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

// starting with lghts OFF
   digitalWrite(latchPin, HIGH);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, LOW);
  

  
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

digitalWrite(14, LOW);
digitalWrite(15, LOW);
digitalWrite(16, LOW);

int x = 8;

if (x > 6)
{

  // DOOR OPENNG PROCESS
  leds = 0;
  updateShiftRegister();
  delay(tDelay);

  
  for (int i = 8; i >= 0; i--) {  //lights yellow to green up
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

leds = 0;

 for (int i = 0; i <= 8; i++) {   //lights green to yellow down
    ledlightUP(i);
  }

    lcd.clear();
    lcd.print("Welcome!");
    delay(1000);
    lcd.clear();
  
} //end if

} // end loop



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
