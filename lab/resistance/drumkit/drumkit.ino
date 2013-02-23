const int fsr = 0;
const int pot = A2;
const int button = 2;
const int beeper = 3;

enum state {
    HOLD,
    RECORD,
    PLAY,
    NUM_STATES
};

int *hits;
int maxBeats = 850; //Max memory!
int lastBeat = 0;
int buttonState = 0;
enum state recording = HOLD;
int beatIndex = 0;
int delayms = 5;
int tempoDivisor = 100;



void setup() {
    pinMode(fsr, INPUT);
    pinMode(button, INPUT);
    pinMode(beeper, OUTPUT);
    Serial.begin(9600);
    hits = (int *)malloc(maxBeats * sizeof(int));
}

void loop() {
    buttonState = digitalRead(button);
    /*
    Serial.print(recording);
    Serial.print("\t");
    Serial.print(beatIndex);
    Serial.print("\t");
    Serial.print(analogRead(fsr));
    Serial.print("\n");
    */

    //Advance mode
    if (buttonState == HIGH) {
        //Loop until released
        while (digitalRead(button) == HIGH) ;
        nextState();
    } else { //Handle action in current mode
        stateAction();
    }
    if (recording == PLAY) {
      delay(max(1, analogRead(pot)/tempoDivisor));
    } else {
      delay(delayms);
    }
}



//Manage setup for new state
//Perhaps add tricolor LED to indicate state? (R - recording,
//      G - playback, B - hold?)
void nextState() {
    analogWrite(beeper, 0); //Stop any sound
    switch (recording) {
        case HOLD:
            recording = RECORD;
            for (int i = 0; i < maxBeats; i++) {
               hits[i] = 0; 
            }
            beatIndex = 0;
            break;
        case RECORD:
            recording = PLAY;
            lastBeat = beatIndex;
            beatIndex = 0;
            break;
        case PLAY:
            recording = HOLD;
            break;
    }
}


void play(int index) {
    if (hits[index] > 0) {
        analogWrite(beeper,100);
    } else {
        analogWrite(beeper, 0);
    }
}

void record(int index) {
    hits[index] = analogRead(fsr);
    if (hits[index] > 0) { Serial.println(index); }
    play(index);
}

void stateAction() {
    switch (recording) {
        case HOLD:
            break;
        case RECORD:
            record(beatIndex);
            beatIndex = (beatIndex + 1) % maxBeats;
            break;
        case PLAY:
            play(beatIndex);
            beatIndex = (beatIndex + 1) % lastBeat;
            break;
    }

}
