/*
 * Lassobot code
 * HCI
 */

int buttonPin = 2;
int motorPin = 3;
int motorMode = 0;
int speed = 200;

void switchMode() {
  if (motorMode == 0)
    motorMode = 1;
  else
    motorMode = 0;
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState > 0) {
    switchMode();
  }

  if (motorMode) {
    analogWrite(speed, motorPin);
  }
}