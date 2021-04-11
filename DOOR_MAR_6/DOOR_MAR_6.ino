

//////////////////////////////////
#include <EEPROM.h>     // We are going to read and write PICC's UIDs from/to EEPROM
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices


#include <LiquidCrystal.h>
#include <Servo.h>

// DEF for Servo
Servo myservo;


////////////////CARDREADER//////////////
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
///////////LEDS////////////////////////
#define DS_pin 16
#define STCP_pin 15
#define SHCP_pin 14


// DEF for LCD Display //////////////////////////////
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);

boolean registers[8];  //default value = false = 0
int delayTime = 100;



//////////////////////////////new///////////////////////////
byte storedCard[4];   // Stores an ID read from EEPROM
byte readCard[4];   // Stores scanned ID read from RFID Module
byte masterCard[4];   // Stores master card's ID read from EEPROM

uint8_t successRead;    // Variable integer to keep if we have Successful Read from Reader

/////////////////////////////new end ///////////////////////

byte lukas[4] = "6C 9F";



void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));



//////////////////////////////////////////////////////

  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  writeReg();


/////////////////////////////////////
    
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


void writeReg()
{
  digitalWrite(STCP_pin,LOW);

  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(SHCP_pin,LOW);
    digitalWrite(DS_pin, registers[i]);
    digitalWrite(SHCP_pin, HIGH);
  }
  digitalWrite(STCP_pin, HIGH);
}



void loop() {


  
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  if ( EEPROM.read(0))
  {
      for (int i = 0; i <8; i++)
  {
    registers[i] = HIGH;
    delay(delayTime);
    writeReg();
  }

////////////////////////////////////
  //myservo.write(90);// move servos to center position -> 90°
  //delay(500);
  myservo.write(30);// move servos to center position -> 60°
      lcd.clear();
    lcd.print("Welcome!");
 
  delay(1500);
  
    lcd.clear();
  //myservo.write(90);// move servos to center position -> 90°
  //delay(500);
  myservo.write(150);// move servos to center position -> 120°
  delay(500);

  lcd.write("Please identify");
//////////////////////////////
  
  for (int i = 7; i >= 0; i--)
  {
    registers[i] = LOW;
    delay(delayTime);
    writeReg();
  }

  }
}




















//////////////////////////////////...............new........///////////////
///////////////////////////////////////// Get PICC's UID ///////////////////////////////////
uint8_t getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  Serial.println(F("Scanned PICC's UID:"));
  for ( uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);

    for (int j=0; j < 4; j++) {
      if (readCard[i] != lukas[i]) {
        break;
      }
      Serial.print("Hello lukas");
    }
  }
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}




//////////////////////////////////////// Read an ID from EEPROM //////////////////////////////
void readID( uint8_t number ) {
  uint8_t start = (number * 4 ) + 2;    // Figure out starting position
  for ( uint8_t i = 0; i < 4; i++ ) {     // Loop 4 times to get the 4 Bytes
    storedCard[i] = EEPROM.read(start + i);   // Assign values read from EEPROM to array
  }
}





///////////////////////////////////////// Find ID From EEPROM   ///////////////////////////////////
bool findID( byte find[] ) {
  uint8_t count = EEPROM.read(0);     // Read the first Byte of EEPROM that
  for ( uint8_t i = 1; i < count; i++ ) {    // Loop once for each EEPROM entry
    readID(i);          // Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( find, storedCard ) ) {   // Check to see if the storedCard read from EEPROM
      return true;
    }
    else {    // If not, return false
    }
  }
  return false;
}


///////////////////////////////////////// Check Bytes   ///////////////////////////////////
bool checkTwo ( byte a[], byte b[] ) {   
  for ( uint8_t k = 0; k < 4; k++ ) {   // Loop 4 times
    if ( a[k] != b[k] ) {     // IF a != b then false, because: one fails, all fail
       return false;
    }
  }
  return true;  
}
