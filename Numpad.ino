#include <stdint.h>
#include <Keyboard.h>
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
		int state;
	}x;
	struct{
		uint pin;
		int min;
		int max;
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

	stick.y.pin = A8;
	stick.y.state = 0;

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

	changed = false;

	const bool btn = !digitalRead(stick.btn.pin);
	changed |= btn != stick.btn.state;
	stick.btn.state = btn;

	const int xval = analogRead(stick.x.pin);
	const int xdif = abs(xval - stick.x.state);
	changed |= xdif > 10;
	stick.x.state = xval;

	const int yval = analogRead(stick.y.pin);
	const int ydif = abs(yval - stick.y.state);
	changed |= ydif > 10;
	stick.y.state = yval;

	char buf[32] = {0};
	sprintf(buf, "(%4i, %4i) %s\n",
		stick.x.state, stick.y.state, stick.btn.state?"PRESSED":"RELEASED"
	);

	if(changed)
		Serial.print(buf);
}
