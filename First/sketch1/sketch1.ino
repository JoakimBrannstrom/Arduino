
void toggle(void* args);
void conditionalAction(bool condition, void (*action)(void*), void* args);

// the setup routine runs once when you press reset:
void setup() {
  pinMode(0, INPUT);
  pinMode(13, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  int pinNr = 13;
  conditionalAction(digitalRead(0) == 1, toggle, &pinNr);
}

void toggle(void* args)
{
  int pinNr = *((int*)args);
  digitalWrite(pinNr, HIGH);
  delay(100);
  digitalWrite(pinNr, LOW);
  delay(100);
}

void conditionalAction(bool condition, void (*action)(void*), void* args)
{
  if(condition)
    action(args);
}

