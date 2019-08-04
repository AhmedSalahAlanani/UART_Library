#ifndef __UARTLIBRARY_H__
#define __UARTLIBRARY_H__

#include "UART_Library_Config.h"
#include <avr/io.h>

//Functions prototypes
void UARTInit(void);
uint16_t UARTReceive(void);
void UARTTransmit(uint16_t data);
void UARTReceiveInterruptEnable(void);
void UARTTransmitInterruptEnable(void);
void UARTDataRegisterEmptyInterruptEnable(void);

#endif