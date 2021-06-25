#include        <NRFLite.h>
#include        "rx.h"

void sync()
{
    u8 data = 0;
    while(data != 240){
        if(radio.hasData())
            radio.readData(&data);
    }

}

void setup()
{
    Keyboard.begin();
    rxInit();
    sync();
}

void loop()
{
    uint8_t data[5] = {0};
    u8 size = 0;
    while(size < 5){
        if(radio.hasData()){
            radio.readData(&data[size]);
            size++;
        }
    }

    if(data[0] != 250 || data[4] != 240){
        Serial.println("Out of sync");
        sync();
    }

    // for(uint i = 0; i < size; i++){
    //     Serial.print("raw ");
    //     Serial.print(i);
    //     Serial.print(": ");
    //     Serial.println(data[i]);
    // }

    Serial.print("Key: ");
    Serial.print(label[data[2]][data[3]]);
    Serial.println(data[1]?" pressed":" released");

    // if(data[0])
    //     Keyboard.press(code[data[1]][data[2]]);
    // else
    //     Keyboard.release(code[data[1]][data[2]]);
    // Keyboard.send_now();
}
