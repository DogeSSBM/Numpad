#include        <NRFLite.h>
#include        "rx.h"

void sync()
{
    u8 data;
    do{
        if(radio.hasData()){
            radio.readData(&data);
            Serial.print("Sync packet data: ");
            Serial.println(data, HEX);
        }
    }while(data != 240);
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

bool readDataBytes(u8 *data,  const u8 numBytes)
{
    for(uint i = 0; i < numBytes; i++){
        while(!radio.hasData());
        radio.readData(&data[i]);
        Serial.print("Recived data packet ");
        Serial.print(i);
        Serial.print(". Data: ");
        Serial.println(data[i]);
    }
    return data[0] == 250 && data[4] == 240;
}

void loop()
{
    uint8_t data[5] = {0};

    if(!readDataBytes(data, 5))
        sync();

    char l = label[data[2]][data[3]];
    int c = code[data[2]][data[3]];

    Serial.print("Key: ");
    Serial.println(l);
    Serial.print("Code: ");
    Serial.println(c, HEX);
    Serial.println(data[1]?"Pressed\n":"Released\n");

    if(data[1]==255)
        Keyboard.press(c);
    else if(data[1]==0)
        Keyboard.release(c);
    else{
        Serial.println("unknown data[1] value");
        sync();
    }
    Keyboard.send_now();
}
