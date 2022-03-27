#ifndef AD7606_H
#define AD7606_H

#include "arduino.h"

// Serial
// Send CVA and CVB high pulse, wait busy go to low, put CS low, {read 16 times DB7 and DB8} (Most significant bit first)
//
// Byte mode / paralel mode
// Send CVA and CVB high pulse, wait busy go to low, put CS low, {put RD low, read the values, put RD high}

class AD7606
{
protected:
	uint8_t _RESET;
	uint8_t _CS;
	uint8_t _CONVSTA;
	uint8_t _CONVSTB;
	uint8_t _RD;
	uint8_t _DB7;
	uint8_t _DB8;
	uint8_t _BUSY;
	uint8_t _D0_D7[8];
	uint8_t _D0_D15[16];
	uint8_t _OS0;
	uint8_t _OS1;
	uint8_t _OS2;
	uint8_t _RANGE;
	void pulse(uint8_t);
	void pulse(uint8_t, uint8_t);
	void ipulse(uint8_t);
	void ipulse(uint8_t, uint8_t);
	void reset();
public:
	void setOversampling(uint8_t);	
	void setRange(bool);
};

class AD7606_Serial : public AD7606
{
public:
	AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET); // Constructor for serial communication
	AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE); // Constructor for serial communication
	AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2); // Constructor for serial communication
	AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE); // Constructor for serial communication
	void read(int16_t *);   // Read raw values from ADC
	void read(int16_t *,uint8_t ); // Read raw values from ADC
};

class AD7606_8080 : public AD7606
{
public:
	AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET); // Constructor for parallel byte communication
	AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE); // Constructor for parallel byte communication
	AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2); // Constructor for parallel byte communication
	AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE); // Constructor for parallel byte communication
	void read(int16_t *);   // Read raw values from ADC
	void read(int16_t *,uint8_t ); // Read raw values from ADC
};

class AD7606_16 : public AD7606
{
public:
	AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET); // Constructor for parallel communication
	AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE); // Constructor for parallel communication
	AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2); // Constructor for parallel communication
	AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE); // Constructor for parallel communication
	void read(int16_t *);   // Read raw values from ADC
	void read(int16_t *,uint8_t ); // Read raw values from ADC
};
#endif