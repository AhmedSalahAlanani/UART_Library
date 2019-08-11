#ifndef __UARTCONFIG_H__
#define __UARTCONFIG_H__

#define UARTMode				1 		//1 for Asynchronous mode , 0 for Synchronous mode   
#define Baud  					2400  	//Set Baud rate 

#ifndef F_CPU
#define F_CPU 1000000UL					//Set Clock frequency 
#endif
 					
#define AsynchronousSpeed		1		//1 for normal speed or 0 for double speed
#define DataBitSize				8		//5 for 5-bit data bit length , 6 for 6-bit data bit length , 7 for 7-bit data bit length , 8 for 8-bit data bit length
#define parity					2		//0 for even parity , 1 for odd parity
#define StopBits				1		//1 for 1 stop bit , 2 for 2 stop bits

#endif

