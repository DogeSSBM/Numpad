#include        <NRFLite.h>
#include        "tx.h"

void setup()
{
    txInit();
}

void loop()
{
    while(!keyPollAll());
    printAll();

    for(u8 x = 0; x < XLEN; x++){
        for(u8 y = 0; y < YLEN; y++){
            if(keyChange(x,y)){
                Serial.print("Key: ");
                Serial.print(label[x][y]);
                Serial.println(keyState(x,y)?" pressed":" released");                digitalWrite(LED, HIGH);
                const u8 data[3] = {keyState(x,y)?255:0, x, y};
                radio.send(RXID, data, 3);
                digitalWrite(LED, LOW);
            }
        }
    }
}
