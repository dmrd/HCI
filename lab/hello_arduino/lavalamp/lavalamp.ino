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
int RGBLED_Red = 3;
int RGB_RLO = 0;
int RGB_RHI = 300;

int RGBLED_Blue = 5;
int RGB_BLO = 0;
int RGB_BHI = 300;

int RGBLED_Green = 6;
int RGB_GLO = 0;
int RGB_GHI = 300;

// Red LEDs
int LED2 = 9;
int LED2LO = 250;
int LED2HI = 550;

// Green LED
int LED3 = 10;
int LED3LO = 500;
int LED3HI = 800;

// Blue LED
int LED4 = 11;
int LED4LO = 750;
int LED4HI = 1023;

int softpot = A0;
int photosensor = A1;

int scale(double lo, double hi, double cur) {
  if (cur > hi) return 255;
  if (cur < lo) return 0;
  return 255 * (cur - lo) / (hi - lo)
}

void setVals(int cur) {
  int rgb_r = scale(RGB_RLO, RGB_RHI, cur);
  int rgb_g = scale(RGB_GLO, RGB_GHI, cur);
  int rgb_b = scale(RGB_BLO, RGB_BHI, cur);

  int l2 = scale(LED2LO, LED2HI, cur);
  int l3 = scale(LED3LO, LED3HI, cur);
  int l4 = scale(LED4LO, LED4HI, cur);

  analogWrite(RGBLED_Red, rgb_r);
  analogWrite(RGBLED_Blue, rgb_b);
  analogWrite(RGBLED_Green, rgb_g);
  analogWrite(LED2, l2);
  analogWrite(LED3, l3);
  analogWrite(LED4, l4);
}

void setup() {
  pinMode(RGBLED_Red, OUTPUT);
  pinMode(RGBLED_Blue, OUTPUT);
  pinMode(RGBLED_Green, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Check to see if there is light in the room using the
  // photoresistor. If so, set the output to 0. Otherwise, use the
  // softpot.
  if (analogRead(photosensor) < 100)
    setVals(analogRead(softpot));
  else
    setVals(analogRead(0));
}
