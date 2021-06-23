#include        <NRFLite.h>
#include        "rx.h"

void setup()
{
    rxInit();
}

void loop()
{
    uint8_t data[16] = {0};
    u8 size = 0;
    while(!radio.hasData());
    while(radio.hasData()){
        radio.readData(data+size);
        size++;
    }

    Serial.print("Key: ");
    Serial.print(code[data[1]][data[2]]);
    Serial.println(data[0]?" pressed":" released");

    if(data[0])
        Keyboard.press(code[data[1]][data[2]]);
    else
        Keyboard.release(code[data[1]][data[2]]);
    Keyboard.send_now();
}
