#pragma once
#include <Adafruit_ATParser.h>
#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BLE.h>
#include <SoftwareSerial.h>

#define BLUEFRUIT_SWUART_RXD_PIN			14	// Required for software serial
#define BLUEFRUIT_SWUART_TXD_PIN			15	// Required for software serial
#define BLUEFRUIT_UART_CTS_PIN			16	// Required for software serial
#define BLUEFRUIT_UART_RTS_PIN			17	// Optional, set to -1 if unused
#define BLUEFRUIT_UART_MODE_PIN			-1	// Set to -1 if unused
#define VERBOSE_MODE					true  // If set to 'true' enables debug output
#define BUFSIZE						128	// Size of the read buffer for incoming data

SoftwareSerial bluefruitSS = SoftwareSerial(BLUEFRUIT_SWUART_TXD_PIN, BLUEFRUIT_SWUART_RXD_PIN);
Adafruit_BluefruitLE_UART ble(bluefruitSS, BLUEFRUIT_UART_MODE_PIN, BLUEFRUIT_UART_CTS_PIN, BLUEFRUIT_UART_RTS_PIN);

void getUserInput(char buffer[], const uint8_t maxSize)
{
	memset(buffer, 0, maxSize);
	while(Serial.available() == 0)
		delay(1);

	uint8_t count=0;
	do{
		count += Serial.readBytes(buffer+count, maxSize);
		delay(2);
	}while(count < maxSize && Serial.available() != 0);
}
