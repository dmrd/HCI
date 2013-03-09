/* Accelerometer controlled melody playback for HCI436 lab */
/* Melody code borrowed from Tom Igoe
http://arduino.cc/en/Tutorial/Tone
 */
#include "pitches.h"

int speakerPin = 3;
int linPin = ;
int flexPin = ;
int maxLin = 1023;
int numNotes = 13;

int lastNote = -1;

// notes in the melody:
int notes[] = {NOTE_C4, NOTE_CS4 ,NOTE_D4 ,NOTE_DS4 ,NOTE_E4 ,NOTE_F4 ,NOTE_FS4 ,NOTE_G4 ,NOTE_GS4 ,NOTE_A4 ,NOTE_AS4 ,NOTE_B4 ,NOTE_C5}



void setup() {
    //initialize the serial communications:
    Serial.begin(9600);
    pinMode(groundpin, INPUT);
    pinMode(powerpin, INPUT);
}

void loop() {
    //read sensor values
    int linVal = analogRead(linPin);
    if (linVal < 5) {
        noTone(speakerPin);
    } else { 
        int cNote = (int) ((linVal / maxLin) * (numNotes + 1));
        if (cNote != lastNote) {
            tone(speakerPin, notes[cNote]);
            lastNote = cNote;
        }
        }
}
