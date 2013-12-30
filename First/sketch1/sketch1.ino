// the setup routine runs once when you press reset:
void setup() {
  pinMode(0, INPUT);
  pinMode(13, OUTPUT);
  /*
  // initialize the digital pin as an output.
  for(int i = 0; i <= 13; i++)
  {
    pinMode(i, OUTPUT);     
  }

  for(int i = 0; i <= 13; i++)
  {
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(i, HIGH);
  }

  delay(2000);

  for(int i = 0; i <= 13; i++)
  {
    // turn the LED off by making the voltage LOW
    digitalWrite(i, LOW);
  }
  */
}

// the loop routine runs over and over again forever:
void loop() {
  int value = digitalRead(0);
  if(value == 1)
  {
    // turn the LED on (HIGH is the voltage level)
    digitalWrite(13, HIGH);
    delay(100);

    // turn the LED off by making the voltage LOW
    digitalWrite(13, LOW);
    delay(100);
  }
}

