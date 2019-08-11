#include "UART_Library.h"

void UARTInit(void)
{
	//Enable the receiver and transmitter
	UCSRB  |= (1 << RXEN) | (1 << TXEN) ;

	//Setting data bits
	#if (DataBitSize==5)
	UCSRC = (1<<URSEL);										//5-bit data length
	#elif (DataBitSize==6)
	UCSRC = (1<<UCSZ0) | (1<<URSEL) ;									//6-bit data length
	#elif (DataBitSize==7)
	UCSRC = (1 << UCSZ1) | (1<<URSEL);									//7-bit data length
	#elif (DataBitSize==8)
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);		//8-bit data length
	#endif
	
	//Synchronous or Asynchronous mode	
	#if (UARTMode==1)
	UCSRC &= ~(1 << UMSEL);					//Resetting the UMSEL bit to 0 for Asynchronous mode
	#elif (UARTMode==0)
	UCSRC |= (1 << UMSEL);					//Setting the UMSEL bit to 1 for Synchronous mode	 
 	#endif
	
	//Setting asynchronous speed
	#if (UARTMode==1)
	#if (AsynchronousSpeed==1)
	UCSRA &= ~(1 << U2X);		//setting the U2X bit to 0 for normal asynchronous	
	#elif (AsynchronousSpeed==0)
	UCSRA &= ~(1 << U2X);		//setting the U2X bit to 0 for normal asynchronous
	#endif
	#endif
	
	//Setting the number of Stop Bits to use
	#if (StopBits==1)
	UCSRC &= ~(1 << USBS);									//clears the USBS for 1 stop bit
	#elif (StopBits==2)
	UCSRC |= (1 << USBS);									//Sets 2 stop bits
	#endif
	
	//Setting the Parity Mode  
	#if (parity==0)
	UCSRC |= (1 << UPM1);									//Sets parity to EVEN
	#elif (parity==1)
	UCSRC |= (1 << UPM1) | (1 << UPM0);						//Sets parity to ODD
	#endif
	
	//Setting the Baud rate
	#if (UARTMode==1)
	uint8_t  UBBR_Value = ( (F_CPU / 16) / Baud ) - 1;
 	UBRRH = (unsigned char) (UBBR_Value >> 8);
	UBRRL = (unsigned char) UBBR_Value;
	#endif
	}

uint8_t UARTReceive(void)
{
	while ( !(UCSRA & (1 << RXC)) );						//Wait for the RXC to not have 0
	return UDR;												//Get that data outa there and back to the main program!
}

void UARTTransmit(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE))) ;
	/* Put data into buffer, sends the data */
	UDR = data;
}


void UARTReceiveInterruptEnable(void)
{
	UCSRB |= (1<<RXCIE);
}

void UARTTransmitInterruptEnable(void)
{
	UCSRB |= (1<<TXCIE);
}

void UARTDataRegisterEmptyInterruptEnable(void)
{
	UCSRB |= (1<<UDRIE);
}