
// the setup routine runs once when you press reset:
void setup() {
  pinMode(0, INPUT);
  pinMode(13, OUTPUT);
}

void toggle(int pinNr)
{
  digitalWrite(pinNr, HIGH);
  delay(100);
  digitalWrite(pinNr, LOW);
  delay(100);
}

void conditionalAction(bool condition, void (*action)(int), int args)
{
  if(condition)
    action(args);
}

// the loop routine runs over and over again forever:
void loop() {
  conditionalAction(digitalRead(0) == 1, toggle, 13);
}

