void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (int i = 0; i < 3; i++)
  {
  digitalWrite(12, HIGH);
  delay(200);
  digitalWrite(12, LOW);
  delay(200);
  }

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(7, HIGH);
  delay(700);
  digitalWrite(7, LOW);
  delay(700);
  }

    for (int i = 0; i < 3; i++)
  {
  digitalWrite(4, HIGH);
  delay(200);
  digitalWrite(4, LOW);
  delay(200);
  }
}
