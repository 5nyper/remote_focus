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
    int value = map(buf[0], 0, 180, 0, 2000);
    Serial.println(value);
    //focus.write(value);
  }
}
