#include <stdint.h>
#include <Keyboard.h>
#include <Mouse.h>
#define LED			LED_BUILTIN
#define C_NUM		4
#define R_NUM		5
#define KEYMAP_NUM	1
typedef unsigned int	uint;

typedef struct{
	struct{
		uint pin;
		int min;
		int max;
		int neutral;
		int state;
	}x;
	struct{
		uint pin;
		int min;
		int max;
		int neutral;
		int state;
	}y;
	struct{
		uint pin;
		bool state;
	}btn;
}Stick;

Stick stick = {0};

const static uint cArr[C_NUM] = {2, 3, 4, 5};
const static uint rArr[R_NUM] = {6, 7, 8, 9, 10};

bool numState[C_NUM][R_NUM] = {0};

const int numpad[C_NUM][R_NUM] = {
	{KEY_NUM_LOCK,KEYPAD_7,KEYPAD_4,KEYPAD_1,KEYPAD_0},
	{KEYPAD_SLASH,KEYPAD_8,KEYPAD_5,KEYPAD_2,KEYPAD_0},
	{KEYPAD_ASTERIX,KEYPAD_9,KEYPAD_6,KEYPAD_3,KEYPAD_PERIOD},
	{KEYPAD_MINUS,KEYPAD_PLUS,KEYPAD_PLUS,KEYPAD_ENTER,KEYPAD_ENTER}
};

const char numpadLabel[C_NUM][R_NUM] = {
	{'L','7','4','1','0'},
	{'/','8','5','2','0'},
	{'*','9','6','3','.'},
	{'-','+','+','E','E'}
};

void printAll(void)
{
	for(uint r = 0; r < R_NUM; r++){
		for(uint c = 0; c < C_NUM; c++){
			Serial.print(numState[c][r]? numpadLabel[c][r] : '#');
		}
		Serial.print("\n");
	}
	Serial.print("\n");
}

void setup()
{
	stick.x.pin = A9;
	stick.x.state = 0;
	stick.x.min = 0;
	stick.x.neutral = 529;
	stick.x.max = 1024;

	stick.y.pin = A8;
	stick.y.state = 0;
	stick.y.min = 0;
	stick.y.neutral = 531;
	stick.y.max = 1024;

	stick.btn.pin = 11;
	stick.btn.state = 0;

	pinMode(LED, OUTPUT);
	Serial.begin(9600);
	while(!Serial.dtr());
	delay(1000);
	Serial.println("Starting...");
	for(uint r = 0; r < R_NUM; r++){
		pinMode(rArr[r], INPUT_PULLUP);
	}
	for(uint c = 0; c < C_NUM; c++){
		pinMode(cArr[c], INPUT);
	}
	pinMode(stick.btn.pin, INPUT_PULLUP);
}

void loop()
{
	static elapsedMillis numUpdated[C_NUM][R_NUM] = {0};
	// static uint selection = 0;

	bool changed = false;
	for(uint c = 0; c < C_NUM; c++){
		pinMode(cArr[c], OUTPUT);
		digitalWrite(cArr[c], LOW);
		for(uint r = 0; r < R_NUM; r++){
			pinMode(rArr[r], INPUT_PULLUP);
			delayMicroseconds(100);
			const bool state = !digitalRead(rArr[r]);
			if(numUpdated[c][r] > 50 && state != numState[c][r]){
				numUpdated[c][r] = 0;
				numState[c][r] = state;
				changed = true;
				// if(state)
				// 	Keyboard.press(numpad[c][r]);
				// else
				// 	Keyboard.release(numpad[c][r]);
				// Keyboard.send_now();
			}
			pinMode(rArr[r], INPUT);
		}
		pinMode(cArr[c], INPUT);
	}
	if(changed)
		printAll();

	stick.btn.state = !digitalRead(stick.btn.pin);
	stick.x.state = analogRead(stick.x.pin) - stick.x.neutral;
	stick.y.state = analogRead(stick.y.pin) - stick.y.neutral;

	const int dx = -stick.x.state/128;
	const int dy = stick.y.state/128;

	if(abs(stick.x.state)>100 || abs(stick.y.state)>100)
		Mouse.move(dx, dy, 0);

	if(numState[C_NUM-1][R_NUM-1]){
		char buf[32] = {0};
		sprintf(buf, "(%4i, %4i) (%4i, %4i)\n", stick.x.state, stick.y.state, dx, dy);
		Serial.print(buf);
	}
}
