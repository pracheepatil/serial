#include "../include/serial.h"
#include <avr/io.h>
#ifndef MYAVR
#error "This source file is only meant for avr family of processors."
#endif

#ifndef MYAVR
#error "Define the macro MYAVR as 0 (ATmega328|P) or 1(ATmega8) in user_config.h"
#endif

#if (MYAVR == 0)
#define APPLICATION_AVR 0
#elif (MYAVR == 1)
#define APPLICATION_AVR 1
#else
#error "MYAVR is defined but the value isn't 0 0r 1."
#endif


#define SET_BIT(REG,BIT) REG |= (1 << BIT)
#define IS_BIT_SET(REG, BIT) ((REG & (1 << BIT)) == 0 ? 0 : 1)
#define CLR_BIT(REG,BIT) REG &= (~(1 << BIT ))
#define BAUD_9600 ((( F_CPU / 16) + ( 9600/ 2)) / ( 9600) - 1)
#define BAUD_19200 ((( F_CPU / 16) + ( 19200/ 2)) / ( 19200) - 1)
#define BAUD_38400 ((( F_CPU / 16) + ( 38400/ 2)) / ( 38400) - 1)
#define BAUD_57600 ((( F_CPU / 16) + ( 57600/ 2)) / ( 57600) - 1)
#define BAUD_115200 ((( F_CPU / 16) + ( 115200/ 2)) / ( 115200) - 1)