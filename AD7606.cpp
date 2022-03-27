#include "AD7606.h"

// Constructor for serial comunicatio
AD7606_Serial::AD7606_Serial(int DB7, int DB8, int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	_CS = CS;
	_CONVSTA = CONVSTA;
	_CONVSTB = CONVSTB;
	_DB7 = DB7;
	_DB8 = DB8;
	_RD = RD;
	_BUSY = BUSY;
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};

// Constructor for parallel byte comunication
AD7606_8080::AD7606_8080(int D0_D7[8], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	_CS = CS;
	_CONVSTA = CONVSTA;
	_CONVSTB = CONVSTB;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D7[i] = D0_D7[i];
	}
	_RD = RD;
	_BUSY = BUSY;
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};
AD7606_16::AD7606_16(int D0_D15[16], int RD, int CS, int CONVSTA, int CONVSTB, int BUSY, int RESET)
{
	_RESET = RESET;
	_CS = CS;
	_CONVSTA = CONVSTA;
	_CONVSTB = CONVSTB;
	for (uint8_t i = 0; i < 8; i++)
	{
		_D0_D15[i] = D0_D15[i];
	}
	_RD = RD;
	_BUSY = BUSY;
	digitalWrite(_CS, 0);
	digitalWrite(_CONVSTA, 0);
	digitalWrite(_CONVSTB, 0);
	digitalWrite(_RESET, 0);
	reset();
};

// Constructor for parallel comunication

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
	delayMicroseconds(1);
	digitalWrite(pin, LOW);
	delayMicroseconds(1);
}
// Send a pulse to 1 or more pin for 1us
void AD7606::pulse(uint8_t pin1, uint8_t pin2)
{
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
	delayMicroseconds(1);
	digitalWrite(pin1, LOW);
	digitalWrite(pin2, LOW);
	delayMicroseconds(1);
}
// Send a inverted pulse to 1 or more pin for 1us
void AD7606::ipulse(uint8_t pin)
{
	digitalWrite(pin, LOW);
	delayMicroseconds(1);
	digitalWrite(pin, HIGH);
	delayMicroseconds(1);
}
// Send a inverted pulse to 1 or more pin for 1us
void AD7606::ipulse(uint8_t pin1, uint8_t pin2)
{
	digitalWrite(pin1, LOW);
	digitalWrite(pin2, LOW);
	delayMicroseconds(1);
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);
	delayMicroseconds(1);
}

// Read raw values from all 8 channels
// rawDataBuffer is a pointer to an array of 8 16-bit integers
void AD7606_Serial::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;
	uint16_t value2 = 0;

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	digitalWrite(_CS, 0); // Enable DOUTA/DOUTB lines and shift-out the conversion results

	while (_BUSY)
	{
		//  wait for conversions to be completed (low level on BUSY)
	}

	for (uint8_t k = 0; k < 4; k++)
	{
		for (uint8_t i = 0; i < 16; i++)
		{
			ipulse(_RD);
			value1 << 1;
			value2 << 1;
			value1 += digitalRead(_DB7);
			value2 += digitalRead(_DB8);
		}
		*(rawDataBuffer + k) = value1;
		*(rawDataBuffer + 4 + k) = value2;
	}
	digitalWrite(_CS, 1);
}
void AD7606_8080::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	digitalWrite(_CS, 0);

	while (_BUSY)
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
void AD7606_16::read(int16_t *rawDataBuffer)
{
	uint16_t value1 = 0;

	pulse(_CONVSTA, _CONVSTB); // Pulse CONVSTA/CONVSTB to start conversion

	digitalWrite(_CS, 0);

	while (_BUSY)
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
