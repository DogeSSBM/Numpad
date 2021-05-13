#include <stdint.h>
#define LED			LED_BUILTIN
#define C_NUM		4
#define R_NUM		5
typedef unsigned int	uint;

const static uint cArr[C_NUM] = {2, 3, 4, 5};
const static uint rArr[R_NUM] = {6, 7, 8, 9, 10};

static bool numpadState[C_NUM][R_NUM] = {0};
static bool numpadStateLast[C_NUM][R_NUM] = {0};

void printAll(void)
{
	for(uint r = 0; r < R_NUM; r++){
		for(uint c = 0; c < C_NUM; c++){
			Serial.print(numpadState[c][r]? "#" : "-");
		}
		Serial.print("\n");
	}
	Serial.print("\n");
}

void setup()
{
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
}

void loop()
{
	for(uint c = 0; c < C_NUM; c++){
		pinMode(cArr[c], OUTPUT);
		digitalWrite(cArr[c], LOW);
		for(uint r = 0; r < R_NUM; r++){
			numpadStateLast[c][r] = numpadState[c][r];
			numpadState[c][r] = !digitalRead(rArr[r]);
		}
		digitalWrite(cArr[c], HIGH);
		pinMode(cArr[c], INPUT);
	}
	printAll();
	delay(100);
}
