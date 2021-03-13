void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // S.O.S. in morse code
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(200);                      
    digitalWrite(LED_BUILTIN, LOW);    
    delay(200);       
  }
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(600);
    digitalWrite(LED_BUILTIN, LOW);
    delay(600);
  }
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(200);                      
    digitalWrite(LED_BUILTIN, LOW);    
    delay(200);       
  }

  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);
}
