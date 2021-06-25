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

void hang(const char *msg)
{
    Keyboard.releaseAll();
    Keyboard.end();
    Serial.println(msg);
    while(1){
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
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
        hang("Out of sync");
    }

    char l = label[data[2]][data[3]];
    int c = code[data[2]][data[3]];

    Serial.print("Key: ");
    Serial.print(l);
    Serial.println(data[1]?" pressed":" released");

    if(data[1]==255)
        Keyboard.press(c);
    else if(data[1]==0)
        Keyboard.release(c);
    else
        hang("unknown data[1] value");
    Keyboard.send_now();
}
