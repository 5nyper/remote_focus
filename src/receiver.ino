#include <VirtualWire.h>
#include <ServoTimer2.h>

ServoTimer2 focus;
bool toggle = false;
int spe = 10;

void setup() {
  Serial.begin(9600);
  focus.attach(7);
  vw_set_rx_pin(6); 
  vw_setup(4000);
  vw_rx_start();
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) {
    if (buf[0] == 200) {
      delay(1000);
      toggle = true;
      presetMode();
    }
    else {
      int value = map(buf[0], 10, 190, 500, 2500);
      Serial.print("value: ");
      Serial.println(value);
      focus.write(value);
    }
  }
}

void presetMode() {
  while(toggle == true) {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
    if (vw_get_message(buf, &buflen)) {
       if (buf[0] == 201) {
        toggle = false;
        delay(1000);
        break;
      }
      if (buf[0] <= 10) {
        spe = map(buf[0], 0, 10, 1, 100);
        Serial.print("spe: ");
        Serial.println(spe);
      }
      else {
        int value = map(buf[0], 10, 190, 500, 2500);
        Serial.println(value);
        speed(value, spe);
      }
    }
  }
}

void speed(int value, int inc) {
  if (value > focus.read()) {
    while (true) {
      if (focus.read() == 2500 || focus.read() + inc >= value)
        break;
      else {
        Serial.print("read: ");
        Serial.print(focus.read());
        Serial.print(" value: ");
        Serial.println(focus.read() + inc);
        focus.write(focus.read() + inc);
      }
    }
  }
  else {
    while (true) {
      if (focus.read() == 500 || focus.read() - inc <= value)
        break;
      else {
        Serial.print("read: ");
        Serial.print(focus.read());
        Serial.print(" value: ");
        Serial.println(focus.read() - inc);
        focus.write(focus.read() - inc);
      }
    }
  }
}
