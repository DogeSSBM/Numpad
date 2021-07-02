#include        <NRFLite.h>
#include        "rx.h"

void setup()
{
    Keyboard.begin();
    rxInit();
}

void loop()
{
<<<<<<< HEAD
    uint8_t data[5] = {0};

    if(!readDataBytes(data, 5))
        sync();
=======
    const Packet p = readPacket();
    printPacket(p);

    switch(p.state){
        case 255:
            Keyboard.press(getCode(p.x, p.y));
            break;
        case 0:
            Keyboard.release(getCode(p.x, p.y));
            break;
        default:
            Keyboard.releaseAll();
            break;
    }
>>>>>>> 06a75cc9ffb29e389c00901bd710469a5f670367

    Keyboard.send_now();
}
