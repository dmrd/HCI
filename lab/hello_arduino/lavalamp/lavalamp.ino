// Lava lamp code for HCI (COS 436/ELE 469)

int RGBLED_Red = 3;
int RGBLED_Blue = 5;
int RGBLED_Green = 6;
int LED2 = 9;
int LED3 = 10;
int LED4 = 11;

// N.B. The softpot should be plugged into analog pin A0.

void setVals(int rgb_r, int rgb_b, int rgb_g, int l2, int l3, int l4) {
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
  // First, get the value of the softpot.
  int softpot = analogRead(A0);
}
