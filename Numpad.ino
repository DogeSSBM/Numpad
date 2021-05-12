#include <stdint.h>
#define LED			LED_BUILTIN
#define X_NUM		4
#define Y_NUM		5
typedef unsigned int	uint;

const static uint xArr[X_NUM] = {2, 3, 4, 5};
const static uint yArr[Y_NUM] = {6, 7, 8, 9, 10};

static bool numpadState[X_NUM][Y_NUM] = {0};
static bool numpadStateLast[X_NUM][Y_NUM] = {0};

void printAll(void)
{
	for(uint y = 0; y < Y_NUM; y++){
		for(uint x = 0; x < X_NUM; x++){
			Serial.print(numpadState[x][y]? "#" : "-");
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
	for(uint y = 0; y < Y_NUM; y++){
		pinMode(yArr[y], INPUT_PULLUP);
	}
	for(uint x = 0; x < X_NUM; x++){
		digitalWrite(xArr[x], HIGH);
		pinMode(xArr[x], INPUT);
	}
}

void loop()
{
	digitalWrite(LED, HIGH);
	for(uint x = 0; x < X_NUM; x++){
		pinMode(xArr[x], OUTPUT);
		digitalWrite(xArr[x], LOW);
		for(uint y = 0; y < Y_NUM; y++){
			numpadStateLast[x][y] = numpadState[x][y];
			numpadState[x][y] = !digitalRead(yArr[y]);
		}
		digitalWrite(xArr[x], HIGH);
		pinMode(xArr[x], INPUT);
	}
	digitalWrite(LED, LOW);
	printAll();
	delay(100);
}
