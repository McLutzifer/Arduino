void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
}

void loop() {
  // S.O.S. in morse code
  for (int x = 0; x < 3; x++) {
    digitalWrite(13, HIGH);   
    delay(200);                      
    digitalWrite(13, LOW);    
    delay(200);       
  }
  for (int x = 0; x < 3; x++) {
    digitalWrite(13, HIGH);
    delay(600);
    digitalWrite(13, LOW);
    delay(600);
  }
  for (int x = 0; x < 3; x++) {
    digitalWrite(13, HIGH);   
    delay(200);                      
    digitalWrite(13, LOW);    
    delay(200);       
  }

  digitalWrite(13,LOW);
  delay(1000);
}
