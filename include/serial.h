#ifndef __EMB_SERIAL_H__
#define __EMB_SERIAL_H__
#include "types.h"

SerialPort_t*           SerialPort_new(SerialPortConfig_t* config, status_t* result);
status_t                SerialPort_delete(SerialPort_t* device);
status_t                SerialPort_open(SerialPort_t* device);
status_t                SerialPort_close(SerialPort_t* device);
static status_t         sanity_check(const SerialPortConfig_t* config);
static status_t         sanity_check_device(const SerialPort_t* device);
status_t                SerialPort_writeByte(const SerialPort_t* device, unsigned char data);
status_t                SerialPort_readByte(const SerialPort_t* device, unsigned char* data);

#endif //__EMB_SERIAL_H__