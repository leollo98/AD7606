#include "AD7606.cpp"

#define DB0 16
#define DB1 17
#define DB2 25
#define DB3 26
#define DB4 27
#define DB5 32
#define DB6 33
#define DB7 34
#define DB8 2
#define DB9 4
#define DB10 5
#define DB11 13
#define DB12 14
#define DB13 15
#define DB14 35
#define DB15 36
#define CVA_CVB 18
#define CS 19
#define RD 21
#define RESET 22
#define BUSY 23

int DB0_DB15[] = {DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7, DB8, DB9, DB10, DB11, DB12, DB13, DB14, DB15};

AD7606_16 AD(DB0_DB15, RD, CS, CVA_CVB, CVA_CVB, BUSY, RESET);

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
