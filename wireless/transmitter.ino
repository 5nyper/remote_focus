#include <VirtualWire.h>

const int set = 9;
const int presetApin = 7;
const int presetBpin = 6;
const int presetCpin = 5;
const int LEDpin = 3;
const int reset = 4;

bool toggle = false;

int presetA,presetB,presetC;

int pins[5] = {set, presetApin, presetBpin, presetCpin, reset};

void setup() {
  for (int i = 0; i< sizeof(pins); i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH);
  }
  pinMode(LEDpin, OUTPUT);
  vw_set_tx_pin(11);
  vw_setup(4000);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(reset) == LOW) {
    toggle = true;
    getPreset();
  }
  digitalWrite(LEDpin, HIGH);
  int pot = analogRead(2);
  int angle = map(pot, 0, 1023, 0, 180);
  vw_send((uint8_t *)&angle, sizeof(angle));
  vw_wait_tx();
  if (digitalRead(set) == LOW && digitalRead(presetApin) == LOW) {
    presetA = angle;
  }
  if (digitalRead(set) == LOW && digitalRead(presetBpin) == LOW) {
    presetB = angle;
  }
  if (digitalRead(set) == LOW && digitalRead(presetCpin) == LOW) {
    presetC = angle;
  }

}

void getPreset() {
  delay(1000);
  digitalWrite(LEDpin, LOW);
  while(toggle == true) {
    if (digitalRead(presetApin) == LOW) {
      vw_send((uint8_t *)&presetA, sizeof(presetA));
      vw_wait_tx();
    }
    else if (digitalRead(presetBpin) == LOW) {
      vw_send((uint8_t *)&presetB, sizeof(presetB));
      vw_wait_tx();
    }
    else if (digitalRead(presetCpin) == LOW) {
      vw_send((uint8_t *)&presetC, sizeof(presetC));
      vw_wait_tx();
    }
    if (digitalRead(reset) == LOW) {
      toggle = false;
      delay(1000);
      digitalWrite(LEDpin, HIGH);
      break;
    }
  }
}
