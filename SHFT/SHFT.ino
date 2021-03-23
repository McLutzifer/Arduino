int DS_pin = 16;
int STCP_pin = 15;
int SHCP_pin = 14;

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_pin, OUTPUT);
  pinMode(STCP_pin, OUTPUT);
  pinMode(SHCP_pin, OUTPUT);writereg();
 

}

boolean registers(8);

void writereg()
{
  digitalWrite(SHCP_pin,LOW);

  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(STCP_pin,LOW);
    digitalWrite(DS_pin, registers(i));
    digitalWrite(STCP_pin, HIGH);
  }
  digitalWrite(SHCP_pin, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
