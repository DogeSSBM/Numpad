#include <stdint.h>
#define LED			LED_BUILTIN
#define ROW_NUM		5
#define COL_NUM		4
typedef unsigned int	uint;

typedef enum {COL_A=2, COL_B, COL_C, COL_D}Col;
typedef enum {ROW_1=6, ROW_2, ROW_3, ROW_4, ROW_5}Row;

const static Col colArr[COL_NUM] = {COL_A, COL_B, COL_C, COL_D};
const static Row rowArr[ROW_NUM] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5};

static bool numpadState[COL_NUM][ROW_NUM] = {0};
static bool numpadStateLast[COL_NUM][ROW_NUM] = {0};

bool pressedRC(const Row row, const Col col)
{

	return false;
}

void setup() {
	pinMode(LED, OUTPUT);

	for(uint row = 0; row < ROW_NUM; row++){
		pinMode(rowArr[row], INPUT_PULLUP);
	}
	for(uint col = 0; col < COL_NUM; col++){
		pinMode(colArr[col], INPUT);
	}
}

void loop() {
	digitalWrite(LED, HIGH);
	for(uint col = 0; col < COL_NUM; col++){
		pinMode(colArr[col], OUTPUT);
		digitalWrite(colArr[col], LOW);
		for(uint row = 0; row < ROW_NUM; row++){
			numpadStateLast[col][row] = numpadState[col][row];
			numpadState[col][row] = !digitalRead(rowArr[row]);
		}
		digitalWrite(colArr[col], HIGH);
		pinMode(colArr[col], INPUT);
	}
}
