#define DS_pin 16
#define STCP_pin 15
#define SHCP_pin 14


boolean registers[8];  //default value = false = 0

int delayTime = 100;

void setup() 
{
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);
  writeReg();
 

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

void loop() 
{
  for (int i = 0; i <8; i++)
  {
    registers[i] = HIGH;
    delay(delayTime);
    writeReg();
  }
  for (int i = 7; i >= 0; i--)
  {
    registers[i] = LOW;
    delay(delayTime);
    writeReg();
  }

  

}
