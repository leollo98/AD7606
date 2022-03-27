# AD7606

Arduino library for Serial/Parallel ADC AD7606, AD7606-6, and AD7606-4.

## Description

This library should work for the devices mentioned below.

|  Device  | Channels | Resolution |  Max sps  | Notes  |
|:--------:|:--------:|:----------:|:---------:|:-------|
| AD7606   |    8     |     16     |  200000   | Tested |
| AD7606-6 |    6     |     16     |  200000   |        |
| AD7606-4 |    4     |     16     |  200000   |        |


## Interface

### Initializing

To initialize the library you must call constructor as described below.

- **AD7606_Serial( DB7, DB8, RD, CS, CONVSTA, CONVSTB, BUSY, RESET, OS0, OS1, OS2, RANGE)** Constructor for Serial comunication with all device ports, and optional Over Sampling and Range. 
- **AD7606_8080( DB7, DB8, RD, CS, CONVSTA, CONVSTB, BUSY, RESET, OS0, OS1, OS2, RANGE)** Constructor for Parallel byte comunication with all device ports, and optional Over Sampling and Range. 
- **AD7606_16( DB7, DB8, RD, CS, CONVSTA, CONVSTB, BUSY, RESET, OS0, OS1, OS2, RANGE)** Constructor for Parallel 2 bytes comunication with all device ports, and optional Over Sampling and Range. 

After construction the **setOversampling(x)** can be called with the number of samples in 2^x form, with limit of 6, or 64 samples.
The function **setRange(bool)** can be used to set the limits to 5V (+/- 2.5V) with false or 10V (+/- 5V) with true.


### Data rate

Using the Arduino Framework, we have some limitations with frequency and times, so is possible that this library don't work for you if your microcontroller can do a logic low to high to low (LHL) in less than 50ns (20MHz), this should not be a problem for the vast majority of micocontrolles, an ESP32(240MHz) can do LHL in 333ns (3MHz).

The total time is based on this LHL with the folowing requirementes to read all chanels.

|  Mode  | AD7606 | AD7606-6 | AD7606-4 |       Notes        |
|:------:|:------:|:--------:|:--------:|:------------------:|
| Serial |   64   |   48     |    32    | Using 2 data lanes |
|  8080  |   16   |   12     |    8     |                    |
|   16   |   8    |   6      |    4     |                    |



### reading less channels

Reading the ADC is very straightforward, the **read()** function handles all in one call.
But if you want to read less channels, like in the case of AD7606-6 or AD7606-4, or just 2 channels in serial or 1 on 8080 or 16 modes, you can use the **read()** function with 2 arguments, one for the data vector and 1 for the number o channels.
In serial mode 1 channel give back channels 1 and 5, because they are read simultaneously.
In 8080 or 16 modes, the channels are retrive in order, so if you want to read the 6 channel, is necessary to read all previous channels.



## Seting modes

To set the IC in the correct mode is necessary to change the polarity on 2 pins
|  Mode           | PAR/SER/BYTE | DB15 |
|:---------------:|:------------:|:----:|
| Parallel 16     |   0          |  0   |
| Serial          |   1          |  0   |
| Parallel 8080   |   1          |  1   |
  
In the chinese development board, you have 2 places for resistors, R1 and R2, marked with SP1 and 8080.
To set the mode to serial or parallel 8080 is necessary to put the resistor in the SP1 pads, and use de DB15 to set between the 2 modes.
To set the Parallel 16 mode just leave the resistor in the 8080 pads.


## Using with 5V, 3.3V, 2.7V and 2.3V devices.

This IC have 2 different Voltage inputs, the AVcc (+5V) to supply power and the Vdrive (Vio) to communications.
If you have a 5V compatible microcontroller, you can set both to 5V.
If you have a 3.3V compatible microcontroller, you can set AVcc to 5V and Vdrive to 3.3V, so all comunication will be 3.3V.
The limits are 4.75V to 5.25V in the AVcc, and 2.3V to 5.25V in the Vdrive, but with lower Vdrive voltages the IC became slower.
The total time with Vdrive between 3.3V to 5.25V is 5µs, with Vdrive equal to 2.7V the total time is 9.7µs, and with 2.3V the total time is 10.7µs



## Future ideas & improvements

- Improve documentation
- More examples ?



## Examples

See [examples](https://github.com/leollo98/AD7606/tree/main/examples).