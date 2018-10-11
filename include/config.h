#ifndef __EMB_SERIAL_CONFIG_H__
#define __EMB_SERIAL_CONFIG_H__
#include "../user_config.h"


#if (defined(MYAVR) && (MYAVR == 0))
#define F_CPU 16000000L
#elif (defined(MYAVR) && (MYAVR == 1))
#define F_CPU 12000000L

#else
#error "value isn't 0 or 1"
#endif

#if (defined(MYAVR) && (MYAVR == 0))
#define UBRRH UBRR0H  // Baud Rate Register
#define UBRRL UBRR0L
#define UCSRA UCSR0A
#define UCSRB UCSR0B
#define UCSRC UCSR0C

#define UCSZ0  UCSZ00 // frame size Register
#define UCSZ1 UCSZ01
#define UCSZ2 UCSZ02
  
#define USBS USBS0   // stop bit
#define UPM0 UPM00   // parity mode
#define UPM1 UPM01  

#define TXEN TXEN0
#define RXEN RXEN0

#define TXC TXC0
#define RXC RXC0


#elif (defined(MYAVR) && (MYAVR == 1))
#define UBRRH UBRRH
#define UBRRL UBRRL
#define UCSRA UCSRA
#define UCSRB UCSRB
#define UCSRC UCSRC

#define UCSZ0 UCSZ0 //frame size Register
#define UCSZ1 UCSZ1
#define UCSZ2 UCSZ2

#define USBS USBS  // Stop bit
#define UPM0 UPM0  // parity mode
#define UPM1 UPM1

#define TXEN TXEN
#define RXEN RXEN

#define TXC TXC
#define RXC RXC

#else
#error "value isn't 0 or 1"
#endif







#endif //__EMB_SERIAL_CONFIG_H__