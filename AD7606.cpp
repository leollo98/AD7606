#include "AD7606.h"
#include <SPI.h>

#if CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
	#define VSPI FSPI
#endif

#if CONFIG_IDF_TARGET_ESP32 || CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3
	#define spiClk 0x2000 //20Mhz
#else
	#define spiClk SPI_CLOCK_DIV2 //8Mhz
#endif


SPIClass * vspi = NULL;

// Resets the AD7606
void AD7606::reset()
{
	digitalWrite(_RESET, 1);
	delayMicroseconds(1);
	digitalWrite(_RESET, 0);
	delayMicroseconds(1);
}

// Send a pulse to 1 or more pin for 1us
void AD7606::pulse(uint8_t pin)
{
	digitalWrite(pin, HIGH);
	digitalWrite(pin, HIGH);
	digitalWrite(pin, LOW);
	digitalWrite(pin, LOW);
}
// Send a pulse to 1 or more pin for 1us
void AD7606::pulse(uint8_t pin1, uint8_t pin2)
{
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
	digitalWrite(pin1, LOW);
	digitalWrite(pin2, LOW);
}
// Send a inverted pulse to 1 or more pin for 1us
void AD7606::ipulse(uint8_t pin)
{
	digitalWrite(pin, LOW);
	digitalWrite(pin, LOW);
	digitalWrite(pin, HIGH);
	digitalWrite(pin, HIGH);
}
// Send a inverted pulse to 1 or more pin for 1us
void AD7606::ipulse(uint8_t pin1, uint8_t pin2)
{
	digitalWrite(pin1, LOW);
	digitalWrite(pin2, LOW);
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
}
void AD7606::setOversampling(uint8_t times){
	times > 6 ? times = 6: times;
	pinMode(_OS0,OUTPUT);
	pinMode(_OS1,OUTPUT);
	pinMode(_OS2,OUTPUT);
	digitalWrite(_OS0,bitRead(B001,times));
	digitalWrite(_OS1,bitRead(B010,times));
	digitalWrite(_OS2,bitRead(B100,times));
}

void AD7606::extendedRange(bool range){
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_RANGE,range);
}

void AD7606::setRange(bool range){
	extendedRange(range);
}

// Constructor for emulated SPI comunication
AD7606_ESPI::AD7606_ESPI(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	_DB8 = DB8;
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
AD7606_ESPI::AD7606_ESPI(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	_DB8 = DB8;
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
AD7606_ESPI::AD7606_ESPI(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	_DB8 = DB8;
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
AD7606_ESPI::AD7606_ESPI(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	_DB8 = DB8;
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
[[deprecated( Use AD7606_ESPI insted )]]
AD7606_Serial::AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	pinMode(_DB7,OUTPUT);
	_DB8 = DB8;
	pinMode(_DB8,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
[[deprecated( Use AD7606_ESPI insted )]]
AD7606_Serial::AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	pinMode(_DB7,OUTPUT);
	_DB8 = DB8;
	pinMode(_DB8,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
[[deprecated( Use AD7606_ESPI insted )]]
AD7606_Serial::AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	pinMode(_DB7,OUTPUT);
	_DB8 = DB8;
	pinMode(_DB8,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};
[[deprecated( Use AD7606_ESPI insted )]]
AD7606_Serial::AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_DB7 = DB7;
	pinMode(_DB7,OUTPUT);
	_DB8 = DB8;
	pinMode(_DB8,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	digitalWrite(_RD, 1);
	reset();
};

// Read raw values from all 8 channels
// rawDataBuffer is a pointer to an array of 8 16-bit integers
void AD7606_ESPI::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;
	uint16_t value2 = 0;
	
	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion


	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 4; k++)
	{
		for (int8_t i = 15; i >= 0; i--)
		{
			ipulse(_RD);
			value1 += digitalRead(_DB7) << i;
			value2 += digitalRead(_DB8) << i;
		}
		*(rawDataBuffer + k) = value1;
		*(rawDataBuffer + 4 + k) = value2;
	}
	digitalWrite(_CS, 1);
}
void AD7606_ESPI::read(int16_t *rawDataBuffer,uint8_t times)
{
	times > 4 ? times = 4 : times;
	uint16_t value1 = 0;
	uint16_t value2 = 0;
	
	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < times; k++)
	{
		for (int8_t i = 15; i >= 0; i--)
		{
			ipulse(_RD);
			value1 += digitalRead(_DB7) << i;
			value2 += digitalRead(_DB8) << i;
		}
		*(rawDataBuffer + k) = value1;
		*(rawDataBuffer + 4 + k) = value2;
	}
	digitalWrite(_CS, 1);
}
int16_t * AD7606_ESPI::readAndReturn()
{
	int16_t rawDataBuffer[8];
	uint16_t value1 = 0;
	uint16_t value2 = 0;
	
	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 4; k++)
	{
		for (int8_t i = 15; i >= 0; i--)
		{
			ipulse(_RD);
			value1 += digitalRead(_DB7) << i;
			value2 += digitalRead(_DB8) << i;
		}
		rawDataBuffer[k] = value1;
		rawDataBuffer[4+k] = value2;
	}
	digitalWrite(_CS, 1);
	return rawDataBuffer;
}

void AD7606_Serial::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;
	uint16_t value2 = 0;

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 4; k++)
	{
		for (int8_t i = 15; i >= 0; i--)
		{
			ipulse(_RD);
			value1 += digitalRead(_DB7) << i;
			value2 += digitalRead(_DB8) << i;
		}
		*(rawDataBuffer + k) = value1;
		*(rawDataBuffer + 4 + k) = value2;
	}
	digitalWrite(_CS, 1);
}
void AD7606_Serial::read(int16_t *rawDataBuffer,uint8_t times)
{
	times > 4 ? times = 4 : times;
	uint16_t value1 = 0;
	uint16_t value2 = 0;

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < times; k++)
	{
		for (int8_t i = 15; i >= 0; i--)
		{
			ipulse(_RD);
			value1 += digitalRead(_DB7) << i;
			value2 += digitalRead(_DB8) << i;
		}
		*(rawDataBuffer + k) = value1;
		*(rawDataBuffer + 4 + k) = value2;
	}
	digitalWrite(_CS, 1);
}

// Constructor for parallel byte comunication
AD7606_8080::AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D7[i] = D0_D7[i];
		pinMode(_D0_D7[i],OUTPUT);
	}
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_8080::AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D7[i] = D0_D7[i];
	}
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_8080::AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D7[i] = D0_D7[i];
	}
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_8080::AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D7[i] = D0_D7[i];
	}
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};

// Read raw values from all 8 channels
// rawDataBuffer is a pointer to an array of 8 16-bit integers
void AD7606_8080::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;
	
	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 8; k++)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			ipulse(_RD);
			for (uint8_t j = 15; j >= 8; j++)
			{
				value1 += digitalRead(_D0_D7[j - 8]) << j;
			}
			for (uint8_t j = 7; j >= 0; j++)
			{
				value1 += digitalRead(_D0_D7[j]) << j;
			}
		}
		*(rawDataBuffer + k) = value1;
	}
	digitalWrite(_CS, 1);
}
void AD7606_8080::read(int16_t *rawDataBuffer,uint8_t times)
{
	times > 8 ? times = 8 : times;
	uint16_t value1 = 0;

	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results
	
	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < times; k++)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			ipulse(_RD);
			for (uint8_t j = 15; j >= 8; j++)
			{
				value1 += digitalRead(_D0_D7[j - 8]) << j;
			}
			for (uint8_t j = 7; j >= 0; j++)
			{
				value1 += digitalRead(_D0_D7[j]) << j;
			}
		}
		*(rawDataBuffer + k) = value1;
	}
	digitalWrite(_CS, 1);
}
int16_t * AD7606_8080::readAndReturn()
{
	int16_t rawDataBuffer[8];
	uint16_t value1 = 0;
	
	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 8; k++)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			ipulse(_RD);
			for (uint8_t j = 15; j >= 8; j++)
			{
				value1 += digitalRead(_D0_D7[j - 8]) << j;
			}
			for (uint8_t j = 7; j >= 0; j++)
			{
				value1 += digitalRead(_D0_D7[j]) << j;
			}
		}
		rawDataBuffer[k] = value1;
	}
	digitalWrite(_CS, 1);
	return rawDataBuffer;
}

// Constructor for parallel comunication
AD7606_16::AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D15[i] = D0_D15[i];
	}
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_16::AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D15[i] = D0_D15[i];
	}
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_16::AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D15[i] = D0_D15[i];
	}
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_16::AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET,int OS0,int OS1,int OS2,int RANGE)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_RD = RD;
	pinMode(_RD,OUTPUT);
	_BUSY = BUSY;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D15[i] = D0_D15[i];
	}
	_OS0 = OS0;
	pinMode(_OS0,OUTPUT);
	_OS1 = OS1;
	pinMode(_OS1,OUTPUT);
	_OS2 = OS2;
	pinMode(_OS2,OUTPUT);
	_RANGE = RANGE;
	pinMode(_RANGE,OUTPUT);
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};

// Read raw values from all 8 channels
// rawDataBuffer is a pointer to an array of 8 16-bit integers
void AD7606_16::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;
	
	digitalWrite(_CS, 0);

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 8; k++)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			ipulse(_RD);
			for (uint8_t j = 15; j >= 0; j++)
			{
				value1 += digitalRead(_D0_D7[j]) << j;
			}
		}
		*(rawDataBuffer + k) = value1;
	}
	digitalWrite(_CS, 1);
}
void AD7606_16::read(int16_t *rawDataBuffer,uint8_t times)
{
	times > 8 ? times = 8 : times;
	uint16_t value1 = 0;
	
	digitalWrite(_CS, 0);

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < times; k++)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			ipulse(_RD);
			for (uint8_t j = 15; j >= 0; j++)
			{
				value1 += digitalRead(_D0_D7[j]) << j;
			}
		}
		*(rawDataBuffer + k) = value1;
	}
	digitalWrite(_CS, 1);
}
int16_t * AD7606_16::readAndReturn()
{
	int16_t rawDataBuffer[8];
	uint16_t value1 = 0;
	
	digitalWrite(_CS, 0);

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 8; k++)
	{
		for (uint8_t i = 0; i < 2; i++)
		{
			ipulse(_RD);
			for (uint8_t j = 15; j >= 0; j++)
			{
				value1 += digitalRead(_D0_D7[j]) << j;
			}
		}
		rawDataBuffer[k] = value1;
	}
	digitalWrite(_CS, 1);
	return rawDataBuffer;
}


AD7606_SPI::AD7606_SPI(int MISO, int SCK, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	pinMode(_RESET,OUTPUT);
	_CS = CS;
	pinMode(_CS,OUTPUT);
	_CONVSTA = CONVSTA;
	pinMode(_CONVSTA,OUTPUT);
	_CONVSTB = CONVSTB;
	pinMode(_CONVSTB,OUTPUT);
	_BUSY = BUSY;
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	SPI.begin(SCK,MISO,MOSI,CS);
  	SPI.setBitOrder(SPI_MSBFIRST);
  	SPI.setClockDivider(0x2000);
  	SPI.setDataMode(SPI_MODE3);
	reset();
};

void AD7606_SPI::read(int16_t *rawDataBuffer)
{
	digitalWrite(_CS, 0);

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 8; k++)
	{
		rawDataBuffer[k] = SPI.transfer16(0x0000);
	}
	digitalWrite(_CS, 1);
}
void AD7606_SPI::read(int16_t *rawDataBuffer,uint8_t times)
{	
	digitalWrite(_CS, 0);

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion
	
	times > 8 ? times = 8 : times; // save some uSecunds 

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < times; k++)
	{
		rawDataBuffer[k] = SPI.transfer16(0x0000);
	}
	digitalWrite(_CS, 1);
}


int16_t * AD7606_SPI::readAndReturn()
{
	int16_t rawDataBuffer[8];
	
	digitalWrite(_CS, 0);
	
	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	while (digitalRead(_BUSY))
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 8; k++)
	{
		rawDataBuffer[k] = SPI.transfer16(0x0000);
	}
	digitalWrite(_CS, 1);
	return rawDataBuffer;
}
