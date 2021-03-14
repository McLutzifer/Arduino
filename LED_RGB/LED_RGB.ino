// Define Pins
#define BLUE 3
#define GREEN 4
#define RED 6

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

//define variables
int redValue;
int greenValue;
int blueValue;


// main loop
void loop() {
  #define delayTime 10 // fading time between colors

  redValue = 255; // choose a value between 1 and 255 to change the color
  greenValue = 0;
  blueValue = 0;


  for (int i = 0; i < 255; i++)
  {
    redValue --;
    greenValue++;
 
    analogWrite(RED, redValue);
    analogWrite(GREEN, greenValue);
    delay(delayTime)
  }

  redValue = 0;
  greenValue = 255;
  blueValue = 0;

  for (int i = 0
}
