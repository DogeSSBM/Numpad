#pragma once
#define C_NUM               4
#define XLEN                C_NUM

#define R_NUM               5
#define YLEN                R_NUM

#define LED                 LED_BUILTIN
#define CE                  0
#define CSN                 10
#define TXID                1       // transmitter id (Numpad)
#define RXID                0       // receiver id (Dongle)

#define SYM_START           250
#define SYM_END             240

typedef unsigned int        uint;
typedef unsigned long       ul;
typedef uint8_t             u8;
typedef uint16_t            u16;
typedef uint32_t            u32;
typedef int8_t              i8;
typedef int16_t             i16;
typedef int32_t             i32;

const uint cArr[C_NUM] = {2, 3, 4, 5};
const uint rArr[R_NUM] = {6, 7, 8, 9, 18};
bool state[C_NUM][R_NUM];
bool last[C_NUM][R_NUM];

const char label[C_NUM][R_NUM] = {
    {'L','7','4','1','0'},
    {'/','8','5','2','0'},
    {'*','9','6','3','.'},
    {'-','+','+','E','E'}
};

NRFLite radio;

bool keyHeld(const uint x,/* x == c */const uint y/* y == r */)
{
    return state[x][y] && last[x][y];
}

bool keyPressed(const uint x,/* x == c */const uint y/* y == r */)
{
    return state[x][y] && !last[x][y];
}

bool keyReleased(const uint x,/* x == c */const uint y/* y == r */)
{
    return !state[x][y] && last[x][y];
}

bool keyState(const uint x,/* x == c */const uint y/* y == r */)
{
    return state[x][y];
}

bool keyChange(const uint x,/* x == c */const uint y/* y == r */)
{
    return state[x][y] != last[x][y];
}

bool keyPollAll(void)
{
    bool event = false;
    for(uint c = 0; c < C_NUM; c++){
        pinMode(cArr[c], OUTPUT);
        digitalWrite(cArr[c], LOW);
        for(uint r = 0; r < R_NUM; r++){
            pinMode(rArr[r], INPUT_PULLUP);
            last[c][r] = state[c][r];
            delayMicroseconds(100);
            state[c][r] = !digitalRead(rArr[r]);
            pinMode(rArr[r], INPUT);
            event |= state[c][r] != last[c][r];
        }
        pinMode(cArr[c], INPUT);
    }
    return event;
}

void printAll(void)
{
    for(uint r = 0; r < R_NUM; r++){
        for(uint c = 0; c < C_NUM; c++){
            if(keyPressed(c,r))
                Serial.print('v');
            else if(keyReleased(c,r))
                Serial.print('^');
            else
                Serial.print(keyState(c,r)?'_':'-');
        }
        Serial.print("\n");
    }
    Serial.print("\n");
}

void txInit(void)
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    radio.init(TXID, CE, CSN); // Id=1
    Serial.begin(9600);
    delay(1000);
    Serial.println("Numpad online...");

    for(uint r = 0; r < R_NUM; r++){
        pinMode(rArr[r], INPUT_PULLUP);
    }
    for(uint c = 0; c < C_NUM; c++){
        pinMode(cArr[c], INPUT);
    }
}
