#include <LiquidCrystal.h>

#include <Servo.h>
Servo myservo;



//www.elegoo.com
//2016.12.9 

int tDelay = 100;
int latchPin = 3;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 4;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 5;     // (12) DS [S1] on 74HC595

byte leds = 0;

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);


void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void setup() 
{

    // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

    myservo.attach(13);
  myservo.write(90);// move servos to center position -> 90°

    // set up the LCD's number of columns and rows:
  lcd.begin(8, 2);
  // Print a message to the LCD.
  lcd.print("Insert Code");
}

void loop() 
{
    myservo.write(90);// move servos to center position -> 90°
  delay(500);
  myservo.write(30);// move servos to center position -> 60°
  delay(500);
  myservo.write(90);// move servos to center position -> 90°
  delay(500);
  myservo.write(150);// move servos to center position -> 120°
  delay(500);


  leds = 0;
  updateShiftRegister();
  delay(tDelay);
  for (int i = 0; i < 8; i++)
  {
    bitSet(leds, i);
    updateShiftRegister();
    delay(tDelay);
  }
}





/*
SERVO
//www.elegoo.com
//2018.12.19

Servo myservo;

void setup(){

} 
void loop(){

}
*/



//DISPLAY
//#include <LiquidCrystal.h>



/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */
/* 

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {

}

void loop() {

}
*/
