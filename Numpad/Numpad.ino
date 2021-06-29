#include        <NRFLite.h>
#include        "tx.h"

void setup()
{
    txInit();
}

void loop()
{
    while(!keyPollAll());

    for(u8 x = 0; x < XLEN; x++){
        for(u8 y = 0; y < YLEN; y++){
            if(keyChange(x,y)){
                Serial.print("Key: ");
                Serial.print(label[x][y]);
                Serial.println(keyState(x,y)?" pressed":" released");                digitalWrite(LED, HIGH);
                u8 data[5] = {(u8)250, keyState(x,y)?(u8)255:(u8)0, x, y, (u8)240};
                for(uint i = 0; i < 5; i++)
                    radio.send(RXID, &data[i], sizeof(u8));
                digitalWrite(LED, LOW);
            }
        }
    }
    printAll();
}
