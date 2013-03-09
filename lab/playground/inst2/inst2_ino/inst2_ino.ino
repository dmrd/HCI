/* Knock Sensor
  
   This sketch reads a piezo element to detect a knocking sound. 
   It reads an analog pin and compares the result to a set threshold. 
   If the result is greater than the threshold, it writes
   "knock" to the serial port, and toggles the LED on pin 13.
  
   The circuit:
	* + connection of the piezo attached to analog in 0
	* - connection of the piezo attached to ground
	* 1-megohm resistor attached from analog in 0 to ground

   http://www.arduino.cc/en/Tutorial/Knock
   
   created 25 Mar 2007
   by David Cuartielles <http://www.0j0.org>
   modified 30 Aug 2011
   by Tom Igoe
   
   This example code is in the public domain.

 */
 #include "pitches.h"

// these constants won't change:
const int knockSensor = A0; // the piezo is connected to analog pin 0
const int threshold = 26;  // threshold value to decide when the detected sound is a knock or not
const int duration = 100;
const int speakerPin = 3;

// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light
int time = 0;


int numNotes1 = 4;
int notes1[] = {NOTE_E4, NOTE_DS4, NOTE_D4, NOTE_CS4};
int durations1[] = {250,250,250,1000};

int numNotes2 = 4;
int notes2[] = {NOTE_E4, NOTE_DS4, NOTE_D4, NOTE_CS4};
int durations2[] = {100,100,100,100};

int neededDiff = 1000;

void playSiren(int constant) {
    Serial.println("Playing!");
    int cTime = millis();
    Serial.println(cTime);
    for (int i = 0; i < numNotes2; i++) {
        tone(speakerPin, notes2[i]*(constant/100), durations2[i]);
        delay(durations2[i]);
    }
    time = cTime;
}

void setup() {
 Serial.begin(9600);       // use the serial port
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  int maxval = 0, current = millis();
  while (millis() < current + duration) {
    int test = analogRead(knockSensor);
    if (test > maxval)
      maxval = test;
  }
  Serial.println(maxval);
  // if the sensor reading is greater than the threshold:
  if (maxval >= threshold) {
    // send the string "Knock!" back to the computer, followed by newline
    Serial.println("Knock!");  
    playSiren(maxval);    
  }
}
