#include "AD7606.cpp"

#define DB0 16
#define DB1 17
#define DB2 25
#define DB3 26
#define DB4 27
#define DB5 32
#define DB6 33
#define DB7 34
#define CVA_CVB 18
#define CS 19
#define RD 21
#define RESET 22
#define BUSY 23

int DB0_DB7[] = {DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7};

AD7606_8080 AD(DB0_DB7, RD, CS, CVA_CVB, CVA_CVB, BUSY, RESET);

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	int16_t Data[8];
	AD.read(Data, 6); // dont read 7 and 8 channel, or read all 6 channels of AD7606-6
	for (uint8_t i = 0; i < 6; i++)
	{
		Serial.println(Data[i]);
	}
}
