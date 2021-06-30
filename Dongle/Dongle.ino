#include        <NRFLite.h>
#include        "rx.h"

void setup()
{
    Keyboard.begin();
    rxInit();
}

void loop()
{
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

    Keyboard.send_now();
}
