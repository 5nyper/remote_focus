#include <VirtualWire.h>
#include <ServoTimer2.h>

ServoTimer2 focus;

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
    int value = map(buf[0], 0, 180, 500, 2500);
    Serial.println(value);
    int data = speed(value, 1);
    focus.write(dat);
  }
}

void presetMode() {
  
}

int speed(int value, int inc) {
  if (value > focus.read()) {
    if (focus.read() == 2500 || focus.read() + inc == value)
      return value;
    else
      return focus.read() + inc;
  }
  else {
    if (focus.read() == 500 || focus.read() - inc == value)
      return value;
    else
      return focus.read() - inc;
  }
}
