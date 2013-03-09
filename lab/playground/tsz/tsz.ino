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
    while (analogRead(piezoPin1) < threshold || analogRead(piezoPin2) < threshold)
        ;
}

void playNextNote() {
    if (trebleNotes[currentTone] == REST)
        noTone(treblePin);
    else
        tone(treblePin, trebleNotes[currentNote]);
    currentNote++;
}

void setup() {
}

void loop() {
    waitForKnock();
    playNextNote();
    delay(pauseTime);
}
