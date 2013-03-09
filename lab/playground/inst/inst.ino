/* Accelerometer controlled melody playback for HCI436 lab */
/* Melody code borrowed from Tom Igoe
 http://arduino.cc/en/Tutorial/Tone
 */
#include "pitches.h"

int speakerPin = 3;

int note = 0;
int pos = 0;
int tempo;
int numNotes = 7;
int delayTime = 10;

// notes in the melody:
int notes[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int durations[] = {
  4, 8, 8, 4,4,4,4,4 };

//Accelerometer setup
const int groundpin = A2; // analog input pin 2
const int powerpin = A0; // analog input pin 0
const int xpin = A5; // x-axis of the accelerometer
const int ypin = A4; // y-axis
const int zpin= A3; // z-axis

int xval, yval, zval;
int xsteady, ysteady, zsteady;
int ythreshold = 10;
int zvelocity = 0;

int pitch = NOTE_C4;

void setup() {
  //initialize the serial communications:
  Serial.begin(9600);
  // Provide ground and power by using the analog inputs as normal
  // digital pins. This makes it possible to directly connect the
  // breakout board to the Arduino. If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);

  //read sensor values
  xsteady = analogRead(xpin);
  ysteady = analogRead(ypin);
  zsteady = analogRead(zpin);
  delay(200);
  
  int count = 50;
  for (int i = 0; i < count; i++) {
  xsteady += analogRead(xpin);
  ysteady += analogRead(ypin);
  zsteady += analogRead(zpin);
  }
  xsteady /= count;
  ysteady /= count;
  zsteady /= count;
}
int num = 0;
void loop() {
  //read sensor values
  xval = analogRead(xpin);
  yval = analogRead(ypin);
  zval = analogRead(zpin);
  
  int diff = zval - zsteady;
  if (zval > 0 && abs(diff) < 50) {
    int pitchmod = diff * 5;
    int noteDuration = (1000 + diff * 20)/durations[note];
    Serial.print("Note duration: ");
    Serial.println(noteDuration);
    tone(speakerPin, notes[note] - pitchmod,noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin);
    note = (note + 1) % numNotes;
  }
  
}


