#include "pitches.h"
#ifdef REST
# undef REST
#endif
#define REST -1

int treblePin = 3;
int piezoPin1 = A0;
int piezoPin2 = A1;

int threshold = 50;

int currentNote = 0;

int pauseTime = 100;

int trebleNotes[] = {NOTE_C4, NOTE_G4, NOTE_C5, REST, NOTE_E5, NOTE_DS5, REST,
    NOTE_C4, NOTE_G4, NOTE_C5, REST, NOTE_DS5, NOTE_E5, REST, NOTE_C4, NOTE_G4,
    NOTE_C5, REST, NOTE_E4, NOTE_A4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5,
    NOTE_F5, NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6, REST};

void waitForKnock() {
  int sense1, sense2;  
  while (true) {
      sense1 = analogRead(piezoPin1);
      sense2 = analogRead(piezoPin2);
      if (sense1 > threshold || sense2 > threshold)
        break;
      Serial.print(threshold - sense1);
      Serial.print(", ");
      Serial.println(threshold - sense2);
    }
    Serial.println(sense1);
    Serial.println(sense2);
}

void playNextNote() {
    if (trebleNotes[currentNote] == REST)
        noTone(treblePin);
    else if (currentNote <= 33)
        tone(treblePin, trebleNotes[currentNote]);
    else
        currentNote = -1;
    currentNote++;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
    waitForKnock();
    playNextNote();
    delay(pauseTime);
}
