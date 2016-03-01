#include <VirtualWire.h>
#include <ServoTimer2.h>

ServoTimer2 focus;
void setup()
{
  Serial.begin(9600);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(6);
    vw_setup(2000);  // Bits per sec
    focus.attach(7);
    vw_rx_start();       // Start the receiver PLL running
}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen)) {
      Serial.println(buf[0]);
      focus.write(buf[0] - '0');
    }

}
