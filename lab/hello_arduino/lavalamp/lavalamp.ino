// Lava lamp code for HCI (COS 436/ELE 469)

int RGBLED_Red = 3;
int RGB_RLO = 0;
int RGB_RHI = 300;

int RGBLED_Blue = 5;
int RGB_BLO = 0;
int RGB_BHI = 300;

int RGBLED_Green = 6;
int RGB_GLO = 0;
int RGB_GHI = 300;

//Red LEDs
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

// N.B. The softpot should be plugged into analog pin A0.

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
  setVals(analogRead(A0));
}
