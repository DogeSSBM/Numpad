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

#define K_NUM               KEY_NUM_LOCK
#define K_7                 KEYPAD_7
#define K_4                 KEYPAD_4
#define K_1                 KEYPAD_1
#define K_0                 KEYPAD_0

#define K_DIV               KEYPAD_SLASH
#define K_8                 KEYPAD_8
#define K_5                 KEYPAD_5
#define K_2                 KEYPAD_2
#define K_0                 KEYPAD_0

#define K_MUL               KEYPAD_ASTERIX
#define K_9                 KEYPAD_9
#define K_6                 KEYPAD_6
#define K_3                 KEYPAD_3
#define K_DOT               KEYPAD_PERIOD

#define K_SUB               KEYPAD_MINUS
#define K_ADD               KEYPAD_PLUS
#define K_RET               KEYPAD_ENTER

typedef unsigned int        uint;
typedef unsigned long       ul;
typedef uint8_t             u8;
typedef uint16_t            u16;
typedef uint32_t            u32;
typedef int8_t              i8;
typedef int16_t             i16;
typedef int32_t             i32;

const int code[C_NUM][R_NUM] = {
    {K_NUM, K_7,    K_4,    K_1,    K_0},
    {K_DIV, K_8,    K_5,    K_2,    K_0},
    {K_MUL, K_9,    K_6,    K_3,    K_DOT},
    {K_SUB, K_ADD,  K_ADD,  K_RET,  K_RET}
};

const char label[C_NUM][R_NUM] = {
    {'L','7','4','1','0'},
    {'/','8','5','2','0'},
    {'*','9','6','3','.'},
    {'-','+','+','E','E'}
};

NRFLite radio;

void rxInit(void)
{
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    radio.init(RXID, CE, CSN); // Id=0
    Serial.begin(9600);
    delay(1000);
    Serial.println("Dongle online...");
}
