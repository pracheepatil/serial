#ifndef __EMB_SERIAL_TYPES_H__
#define __EMB_SERIAL_TYPES_H__
#include "defs.h"

typedef char SerialPortName_t[6];

typedef enum
{
	enSerialBaud_9600 ,
	enSerialBaud_19200,
	enSerialBaud_38400,
	enSerialBaud_57600,
	enSerialBaud_115200,
	enSerialBaud_Max
}EnSerialBaud_t;

typedef enum
{
	enSerialParity_ODD,
	enSerialParity_Even,
	enSerialParity_Max
}EnSerialParity_t;

typedef enum
{
	enSerialStopBit_One,
	enSerialStopBit_OneAndHalf,
	enSerialStopBit_Two,
	enSerialStopBit_Max
}EnSerialStopBit_t;

typedef struct
{
	EnSerialBaud_t    baud;
	EnSerialParity_t  parity;
	EnSerialStopBit_t stopBit;
	SerialPortName_t  name;
	void*             extra;
}SerialPortConfig_t;

typedef enum
{
	enBoolean_False,
	enBoolean_True,
	enBoolean_Max
}EnBoolean_t;

typedef struct _serial_port_device SerialPort_t;
typedef int status_t;


#endif //__EMB_SERIAL_TYPES_H__