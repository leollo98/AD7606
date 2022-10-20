#include "AD7606.cpp"

#define DB7 16
#define DB8 17
#define CVA_CVB 18
#define CS 19
#define RD 21
#define RESET 22
#define BUSY 23

AD7606_ESPI AD(DB7, DB8, RD, CS, CVA_CVB, CVA_CVB, BUSY, RESET);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	int16_t Data[8];
	AD.read(Data);
	for (uint8_t i = 0; i < 8; i++)
	{
		Serial.println(Data[i]);
	}
}
