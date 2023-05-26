#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driverTx1(2000, 12);
RH_ASK driverTx2(2000, 13);

void setup()
{
    Serial.begin(9600);    // Debugging only
    if (!driverTx1.init())
         Serial.println("init failed");
    if (!driverTx2.init())
         Serial.println("init failed");
}

const char *msg1 = "yeh";
const char *msg2 = "lo";
int count = 0;
void loop()
{
    if (count<20 && count >0)
    {
      driverTx1.send((uint8_t *)msg1, strlen(msg1));
      driverTx1.waitPacketSent();
    }
    else
    {
      driverTx2.send((uint8_t *)msg2, strlen(msg2));
      driverTx2.waitPacketSent();
    }
    if (count == 40){count = 0;}
    delay(100);
}
