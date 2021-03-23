int DS_pin = 16;
int STCP_pin = 15;
int SHCP_pin = 14;

//better     #define STCP_pin 9

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);writereg();
 

}

boolean registers[8];

void writereg()
{
  digitalWrite(SHCP_pin,LOW);

  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(STCP_pin,LOW);
    digitalWrite(DS_pin, registers[i]);
    digitalWrite(STCP_pin, HIGH);
  }
  digitalWrite(SHCP_pin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int i = 0; i <9; i++)
  {
    registers[i] = HIGH;
    delay(100);
    writereg();
  }
  for (int i = 8; i > 0; i++)
  {
    registers[i] = LOW;
    delay(100);
    writereg();
  }

}
