#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 2;
const int receive_pin = 3;
const int transmit_en_pin = 3;

void setup()
{
  // Initialise the IO and ISR
  Serial.begin(9600);
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  //vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);   // Bits per sec
  pinMode(led_pin, OUTPUT);
}

byte count = 1;
double milli = millis();

void loop()
{
  char msg[7] = {'3'};
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  //msg[0] = count;
  if (millis() - milli >= 6000) {milli = millis();}
  if (millis() - milli >= 4000 && millis() - milli <= 5980){
    //digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_rx_stop();
    //Serial.println("2 Tx");
    vw_send((uint8_t *)msg, 7);
    vw_wait_tx(); // Wait until the whole message is gone
    //digitalWrite(led_pin, LOW);
  }

  if (millis() - milli >= 10 && millis() - milli <= 1980){
    //digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
    vw_rx_start();       // Start the receiver PLL running
    //Serial.println("2 Rx");
    if (vw_get_message(buf, &buflen)) {
      Serial.println(buf[0]);
      if(buf[0] == 49) {Serial.println("Perfect");digitalWrite(led_pin, HIGH);}
      } // Non-blocking
    //digitalWrite(led_pin, LOW);
  }

  if (millis() - milli >= 2000 && millis() - milli <= 3980){
    //digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
    vw_rx_start();       // Start the receiver PLL running
    //Serial.println("2 Rx");
    if (vw_get_message(buf, &buflen)) {
      Serial.println(buf[0]);
      if(buf[0] == 50) {Serial.println("Perfect");digitalWrite(led_pin, HIGH);}
      } // Non-blocking
    //digitalWrite(led_pin, LOW);
  }
  
  delay(10);
  digitalWrite(led_pin, LOW);
  //count = count + 1;
}
