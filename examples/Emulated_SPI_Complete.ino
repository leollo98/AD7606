#include "AD7606.cpp"

#define DB7 16
#define DB8 17
#define CVA_CVB 18
#define CS 19
#define RD 21
#define RESET 22
#define BUSY 23
#define OS0 26
#define OS1 27
#define OS2 32
#define RANGE 33

AD7606_ESPI AD(DB7, DB8, RD, CS, CVA_CVB, CVA_CVB, BUSY, RESET, OS0, OS1, OS2, RANGE);

void setup()
{
	Serial.begin(115200);
	AD.setOversampling(6); // 64 Samples
	AD.setRange(false);	   // +/- 2.5V
}

void loop()
{
	int16_t Data[8];
	AD.read(Data, 6); // dont read 4 and 8 channel, or read all 6 channels of AD7606-6
	for (uint8_t i = 0; i < 6; i++)
	{
		Serial.println(Data[i]);
	}
}
