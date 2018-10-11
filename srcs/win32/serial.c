#include "../include/serial.h"
#include <stdlib.h>
#include <avr/io.h>

struct _serial_port_device
{
	EnSerialBaud_t    baud;
	EnSerialParity_t  parity;
	EnSerialStopBit_t stopBit;
	SerialPortName_t  name;
	uint8_t           id;
	//uint8_t           is_open;
};

SerialPort_t* SerialPort_new(SerialPortConfig_t* config, status_t* result){
	*result = sanity_check(config);
	if(*result == 0)
	{
		return enBoolean_False;
	}
	SerialPort_t* conf = (SerialPort_t*)malloc(sizeof(SerialPort_t));
	//if(config->name[1] == '\0')
	
	SET_BIT(UCSRC, UMSEL00);  // SET ASYNCHRONOUS MODE
	
	SET_BIT(UCSRC, UCSZ0);
	SET_BIT(UCSRC, UCSZ1);
	CLR_BIT(UCSRB, UCSZ2);  // SET DATA SIZE
	
	switch(config->baud)
	{
		case 0:
		UBRRH = (BAUD_9600 >> 8);
		UBRRL = BAUD_9600;
		conf->baud = enSerialBaud_9600;
		break;
		case 1:
		UBRRH = (BAUD_19200 >> 8);
		UBRRL = BAUD_19200;
		conf->baud =enSerialBaud_19200;
		break;
		case 2:
		UBRRH = (BAUD_38400 >> 8);
		UBRRL = BAUD_38400;
		conf->baud = enSerialBaud_38400;
		break;
		case 3:
		UBRRH = (BAUD_57600 >> 8);
		UBRRL = BAUD_57600;
		conf->baud = enSerialBaud_57600;
		break;
		case 4:
		UBRRH = (BAUD_115200 >> 8);
		UBRRL = BAUD_115200;
		conf->baud = enSerialBaud_115200;
		break;
		default:
		*result = enBoolean_False;
		break;
	}
	switch(config->parity)
	{
		case 0:
		SET_BIT(UCSRC, UPM01);
		SET_BIT(UCSRC, UPM00);
		conf->parity = enSerialParity_ODD;
		break;
		case 1:
		SET_BIT(UCSRC, UPM01);
		CLR_BIT(UCSRC, UPM00);
		conf->parity = enSerialParity_Even;
		break;
		default:
		*result = enBoolean_False;
		break;
	}
	switch(config->stopBit)
	{
		case 0:
		CLR_BIT(UCSRC, USBS);
		conf->stopBit = enSerialStopBit_One;
		break;
		case 1:
		//enSerialStopBit_OneAndHalf = Not supported At mega 328p
		case 2:
		SET_BIT(UCSRC, USBS);
		conf->stopBit = enSerialStopBit_Two;
		break;
		default:
		*result = enBoolean_False;
		break;
	}
	*result = enBoolean_True;
	return conf;
}

status_t SerialPort_delete(SerialPort_t* device){
	status_t result = sanity_check_device(device);
	if(!result){
		return enBoolean_False;
	}
	free(device);
	return enBoolean_True;
}

static status_t  sanity_check(const SerialPortConfig_t* config){
	if(config == 0){
		return enBoolean_False;
	}
	if((config->baud ) >= enSerialBaud_9600 || (config->baud) < enSerialBaud_Max){
		return enBoolean_True;
	}
	if((config->parity) >= enSerialParity_ODD || (config-> parity) < enSerialParity_Max){
		return enBoolean_True;
	}
	if((config->stopBit) >= enSerialStopBit_One || (config->stopBit) < enSerialStopBit_Max){
		return enBoolean_True;
	}
	return enBoolean_True;
}

static status_t  sanity_check_device(const SerialPort_t* device){
	if(device == 0){
		return enBoolean_False;
	}
	if((device->baud ) >= enSerialBaud_9600 || (device->baud) < enSerialBaud_Max){
		return enBoolean_True;
	}
	if((device->parity) >= enSerialParity_ODD || (device->parity) < enSerialParity_Max){
		return enBoolean_True;
	}
	if((device->stopBit) >= enSerialStopBit_One || (device->stopBit) < enSerialStopBit_Max){
		return enBoolean_True;
	}
	return enBoolean_True;
}

status_t  SerialPort_open(SerialPort_t* device){
	status_t result = sanity_check_device(device);
	if(!result){
		return enBoolean_False;
	}
	switch(device->id){
	case 0:
	    if(IS_BIT_SET(UCSRA,TXEN)==0) {
	      SET_BIT(UCSRB, TXEN);
	    }
	    if(IS_BIT_SET(UCSRA,TXEN)==0){
	      SET_BIT(UCSRB, RXEN);
	    }
	   break;
	 }
    return enBoolean_True;
}

status_t  SerialPort_close(SerialPort_t* device){
	status_t result = sanity_check_device(device);
	if(!result){
		return enBoolean_False;
	}
	switch(device->id){
     case 0:
         if(IS_BIT_SET(UCSRA,TXEN)){
	       CLR_BIT(UCSRB, TXEN);
	      }
	     if(IS_BIT_SET(UCSRA,RXEN)){
	      CLR_BIT(UCSRB, RXEN);
	     }
		break;
    }
	return enBoolean_True;
}

status_t  SerialPort_writeByte(const SerialPort_t* device, unsigned char data){
	status_t result = sanity_check_device(device);
	if(!result){
		return enBoolean_False;
	}
	switch(device->id){
	 case 0:
	    while (!IS_BIT_SET(UCSRA, UDRE0))
	       UDR0 = data;
		break;
	}
    return enBoolean_True;
}

status_t  SerialPort_readByte(const SerialPort_t* device, unsigned char* data){
	status_t result = sanity_check_device(device);
	if(!result){
		return enBoolean_False;
	}
	switch(device->id){
     case 0:
	      while (!IS_BIT_SET(UCSRA, RXC))
	        *data = UDR0;
		  break;
	}
	return enBoolean_True;
}


int myfunc(void)
{
	return 0;
}

