// Lava lamp code for HCI (COS 436/ELE 469)

/*
  There are 4 effective LEDs in the circuit controlled by the Arduino
  Uno. One is an RGB LED, one is 2 red LEDs in series, one is a green
  LED, and one is a blue LED. We have created a mapping to control how
  each LED turns on with the softpot.

  Each LED X has 3 associated variables. First, the variable X is the
  number of the pin that will provide the PWM to control the light
  levels from the Arduino. Variable XLO is the value below which the
  LED is off and above which the LED has some current passing through
  it. Variable XHI is the value above which the LED is at maximum
  brightness and below which its brightness is not maximal.
*/

/*
  The RGB LED has three cathodes and a common anode. Each cathode
  corresponds to a color in the LED and is independently
  controllable.
*/

int range = 300;

int RGBLED_Red = 9;
int RGB_R_mid = 100;

int RGBLED_Blue = 10;
int RGB_B_mid = 500;

int RGBLED_Green = 11;
int RGB_G_mid = 900;

int softpot = A0;
int photosensor = A1;
int button = 2;

// brightness ranges from 0 to 1
double brightness = 1.0;

// mode is:
//   0: set color
//   1: set brightness
int mode = 0;

// psthreshold is the least amount of light needed to activate the lights
int psthreshold = 850;

// state variable is:
//    0: off
//    1: on
int state = 0;

int getBrightness(double mid, double cur) {
  int t1 = abs(mid - cur);
  int t2 = abs(mid - (cur - 1024));
  int t3 = abs(mid - (cur + 1024));
  
  int test1 = min(t1, t2);
  int minimum = min(test1, t3);
  
  if (minimum > range) return 0.0;
  
  return 255 * (range - minimum) / range;
}

void setVals(int cur) {
  if (state == 1) {
    rgb_r = getBrightness(RGB_R_mid, cur);
    rgb_g = getBrightness(RGB_G_mid, cur);
    rgb_b = getBrightness(RGB_B_mid, cur);
  }
  
  writeToLED();
}

void setBrightness(double cur) {
  if (state == 1) 
    brightness = cur / 1024;
  
  writeToLED();
}

void writeToLED() {
  analogWrite(RGBLED_Red, rgb_r * brightness * state);
  analogWrite(RGBLED_Blue, rgb_b * brightness * state);
  analogWrite(RGBLED_Green, rgb_g * brightness * state);
}

void toggleMode() {
  if (mode == 1)
    mode = 0;
  else
    mode = 1;
}

void setup() {
  pinMode(RGBLED_Red, OUTPUT);
  pinMode(RGBLED_Blue, OUTPUT);
  pinMode(RGBLED_Green, OUTPUT);
  pinMode(button, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Check to see if there is light in the room using the
  // photoresistor. If so, set the output to 0. Otherwise, use the
  // softpot.
  int current_light = analogRead(photosensor);
  int current_soft = analogRead(softpot);
  int button_state = digitalRead(button);
  
  if (button_state == HIGH) {
    while (digitalRead(button) == HIGH);
    toggleMode();
  }
  
  if (current_light > psthreshold)
    state = 1;
  else
    state = 0;
  
  if (mode == 0) {
    setVals(current_soft);
  } else
    setBrightness(current_soft);
  }
}
