#include        <NRFLite.h>
#include        "rx.h"
#define LED     LED_BUILTIN

#define CE      0
#define CSN     10
#define TXID    1           // transmitter id (Numpad)
#define RXID    0           // receiver id (Dongle)

NRFLite radio;

void setup()
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    radio.init(RXID, CE, CSN); // Id=0
    Serial.begin(9600);
    delay(1000);

    Serial.println("Dongle online...");
}

void loop()
{
    uint8_t data;

    while(radio.hasData()){
        radio.readData(&data);
        Serial.println(data);
        digitalWrite(LED, data!=0);
    }
}
