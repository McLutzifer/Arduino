
/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define RST_PIN   9     // SPI Reset Pin
#define SS_PIN    10    // SPI Slave Select Pin
#define Lukas "6C 9F 45 4A"


byte readCard[4];
byte lukas[11] = "6C9F 45 4A";

int lukas2[11] = {108, 159, 69, 74};

 
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Instanz des MFRC522 erzeugen

 
void setup() {
  // Diese Funktion wird einmalig beim Start ausgeführt
  Serial.begin(9600);  // Serielle Kommunikation mit dem PC initialisieren
  SPI.begin();         // Initialisiere SPI Kommunikation
  mfrc522.PCD_Init();  // Initialisiere MFRC522 Lesemodul


    
}
 
void loop() {
  // Diese Funktion wird in Endlosschleife ausgeführt
 
  // Nur wenn eine Karte gefunden wird und gelesen werden konnte, wird der Inhalt von IF ausgeführt
  // PICC = proximity integrated circuit card = kontaktlose Chipkarte



  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() ) {
    Serial.print("Gelesene UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // Abstand zwischen HEX-Zahlen und führende Null bei Byte < 16
      //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ); //? " 0" : " ");
      readCard[i] = mfrc522.uid.uidByte[i];
      Serial.print(readCard[i], HEX);
      //Serial.print(mfrc522.uid.uidByte[i], HEX);
    } 
    Serial.println(); 

    for (int i = 0; i < 4; i++) {
      Serial.println(readCard[i]);
    }

    if (readCard[0] == lukas2[0] && 
    readCard[1] == lukas2[1] && 
    readCard[2] == lukas2[2]) {
    Serial.println(F("SUCCESS"));
    }
 
    // Versetzt die gelesene Karte in einen Ruhemodus, um nach anderen Karten suchen zu können.
    mfrc522.PICC_HaltA();
    delay(1000);
  }  



}



int pushIntoArray(int array[], int size){
  int index = 0;
  int newArray[100];

  for (int i= 0; i<= size; i++){
    Serial.print(i);
  }
}
