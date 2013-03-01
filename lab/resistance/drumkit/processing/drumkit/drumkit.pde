import processing.serial.*;
import cc.arduino.*;
import ddf.minim.*;

/*player.setGain(-10.0);*/

Arduino arduino;
Minim minim;


/*Pins*/
//Analog in
int drumFsr = 0;
int volumePot = 2;
//Digital in
int modeButton = 2;
//Digital out
int beeper = 3;

/*Beat information*/
int numTracks = 10; //Number of tracks
int cTrack = 0;
int trackSize = 10000; // Most possible ticks
int lastBeat = 0;      // Last current tick before looping
int[][] tracks = new int[numTracks][]; //All the tracks
AudioPlayer[] sounds = new AudioPlayer[numTracks]; //Sounds to play for each track

/*state*/
int numStates = 5; //0,1 record/hold
int state = 0; //0:play 1:hold 2-4:record drum types
int beat = 0;
int cutoff = 30;
double delayms = 1;


void setup()
{
    println("Serial ports: ");
    println(Serial.list());
    arduino = new Arduino(this, Arduino.list()[0], 57600);
    arduino.pinMode(drumFsr, Arduino.INPUT);
    arduino.pinMode(volumePot, Arduino.INPUT);
    arduino.pinMode(modeButton, Arduino.INPUT);
    clearTracks(); //Initialize tracks

    minim = new Minim(this);

    //Load sounds
    sounds[0] = minim.loadFile("drums/kick.mp3");
    sounds[1] = minim.loadFile("drums/cymbal.mp3");
    sounds[2] = minim.loadFile("drums/vsnare.mp3");
}

void cleanTracks() {
    
  
  
}

void nextState() {
    beat = 0;
    state = (state + 1) % numStates;
    if (state == 1) { 
        lastBeat = 0;
        clearTracks();
    } else if (state == 0) {
      cleanTracks();
    }
}

void clearTracks() {
    for (int i = 0; i < numTracks; i++) {
        tracks[i] = new int[trackSize];
    }
}

void hold() {
  /*
    //Only action is to clear tracks if reset button is pressed
    if (arduino.digitalRead(modeButton) == Arduino.HIGH) {
        //Manage debounce
        while (arduino.digitalRead(modeButton) == Arduino.HIGH) { println("Hold"); }
        clearTracks();
    }
    */
}

void record() {
    cTrack = state - 2;
    int hit = arduino.analogRead(drumFsr);
    if (hit > cutoff) { println("Hit"); tracks[cTrack][beat] = hit; }
    if (state == 2) { lastBeat = max(beat,lastBeat); }
}

void play() {
    //Cheap edge case avoidance...
    if (beat == 0 || beat == trackSize - 1) { return; }
    for (int t = 0; t < numTracks; t++) {
        if (tracks[t][beat] > 30 && tracks[t][beat] > tracks[t][beat-1] &&
        tracks[t][beat] > tracks[t][beat + 1]) {
            print("Play");
            println(t);
            sounds[t].play(0);
        }
    }
}

void draw()
{
    /*
     * Check button - mode change?
     * If play, then play current tick. Advance.  Read potentiometer to get tempo
     * If hold, do nothing
     * If record, then record fsr to current track/tick.  Play other tracks as
     *      well.
     */
    
    if (arduino.digitalRead(modeButton) == arduino.HIGH) {
        //Manage debounce
        while (arduino.digitalRead(modeButton) == arduino.HIGH) { print("") ; }
        nextState();
        print("Debounced: ");
        println(state);
    } else {
        
        switch (state) {
            case 0:
                play();
                beat++;
                break;
            case 1:
                hold();
                break;
            default:
                record();
                beat++;
                break;
        }
    }
    delay(arduino.analogRead(volumePot));
}
