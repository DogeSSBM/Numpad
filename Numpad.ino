#include <stdint.h>
#include <map>
#define LED			LED_BUILTIN
typedef unsigned int	uint;

// enum Col { COL_A=2, COL_B, COL_C, COL_D };
// enum Row { ROW_1=6, ROW_2, ROW_3, ROW_4, ROW_5 };

std::map<char, uint> cols = { { 'A', 2 }, { 'B', 3 }, { 'C', 4 }, { 'D', 5 } };
std::map<char, uint> rows = { { '1', 6 }, { '2', 7 }, { '3', 8 }, { '4', 9 }, { '5', 10 } };


// bool isBtnPressed(const Row row, const Col col) {
//
// 	return false;
// }

void setup() {
	pinMode(LED, OUTPUT);

	for (const auto& kv : rows) {
		pinMode(kv.second, INPUT_PULLUP);
	}
	for (const auto& kv : cols) {
		pinMode(kv.second, INPUT);
	}
}

void loop() {
	digitalWrite(LED, HIGH);
	for (const auto& kvRow : rows) {
		for (const auto& kvCol : cols) {
			pinMode(kvCol.second, OUTPUT);
			pinMode(kvCol.second, INPUT);
		}
	}
}
