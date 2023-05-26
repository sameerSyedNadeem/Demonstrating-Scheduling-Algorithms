#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 2;
const int receive_pin = 3;
const int transmit_en_pin = 3;

void setup()
{
    delay(1000);
    Serial.begin(9600);  // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    //vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec
    pinMode(led_pin, OUTPUT);
    vw_rx_start();       // Start the receiver PLL running
}
double milli = millis();

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  char msg[7] = {'1'};

  if (millis() - milli >= 6000) {milli = millis();}

  if (millis() - milli >= 10 && millis() - milli <= 1980){
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_rx_stop();
    //Serial.println("2 Tx");
    vw_send((uint8_t *)msg, 7);
    vw_wait_tx(); // Wait until the whole message is gone
  }
  
  if (millis() - milli >= 2000 && millis() - milli <= 3980){
    vw_rx_start();       // Start the receiver PLL running
    if (vw_get_message(buf, &buflen)) {
      Serial.println(buf[0]);
      if(buf[0] == 50) {Serial.println("Perfect"); digitalWrite(led_pin, HIGH);}
      } // Non-blocking
  }

  if (millis() - milli >= 4000 && millis() - milli <= 5980){
    vw_rx_start();       // Start the receiver PLL running
    if (vw_get_message(buf, &buflen)) {
      Serial.println(buf[0]);
      if(buf[0] == 51) {Serial.println("Perfect"); digitalWrite(led_pin, HIGH);}
      } // Non-blocking
  }
  
  delay(10);
  digitalWrite(led_pin, LOW);
}
