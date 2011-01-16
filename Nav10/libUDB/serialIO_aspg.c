// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libUDB_internal.h"
#include <string.h>

#if (BOARD_TYPE == ASPG_BOARD)

#define TX_BUF_LEN 512
char __attribute__ ((section(".myDataSection"),address(0x2300))) U1TX_buffer[TX_BUF_LEN];
char __attribute__ ((address(0x2500))) U2TX_buffer[TX_BUF_LEN];
int iU1Head, iU1Tail = 0;
int iU2Head, iU2Tail = 0;

////////////////////////////////////////////////////////////////////////////////
//
// GPS

void udb_init_GPS(void)
{
	// configure U2MODE
	U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//						// Bit14
	U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U1MODEbits.IREN = 0;	// Bit12 No IR translation
	U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//						// Bit10
	U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
	U1MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
	U1MODEbits.BRGH = 1;	// Bit3 4 clocks per bit period
	U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit
	
	// Load all values in for U1STA SFR
	U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U1STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U1STAbits.UTXISEL0 = 1;	//Bit13 Other half of Bit15
	//						//Bit12
	U1STAbits.UTXBRK = 0;	//Bit11 Disabled
	//U1STAbits.UTXEN = 1;	//Bit10 TX pins controlled by periph (handled below)
	//U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	//U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	//U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	//U1STAbits.PERR = 0;	//Bit3 *Read Only Bit*
	//U1STAbits.FERR = 0;	//Bit2 *Read Only Bit*
	U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	//U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	_U1RXIP = 3;	// Mid Range Interrupt Priority level, no urgent reason

	_U1TXIF = 0;	// Clear the Transmit Interrupt Flag
	_U1TXIE = 0;	// Disable Transmit Interrupts
	_U1RXIF = 0;	// Clear the Recieve Interrupt Flag
	_U1RXIE = 1;	// Enable Recieve Interrupts

	U1MODEbits.UARTEN = 1;	// And turn the peripheral on

	U1STAbits.UTXEN = 1;
	
	return ;
}

// int only good up to 32767
void udb_gps_set_rate(int rate)
{
	U1BRG = UDB_BAUD(rate) ;
	return ;
}


boolean udb_gps_check_rate(int rate)
{
	return ( U1BRG == UDB_BAUD(rate) ) ;
}


void __attribute__((__interrupt__, __no_auto_psv__)) _U1RXInterrupt(void)
{
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;	
	
	while ( U1STAbits.URXDA )
	{
		unsigned char rxchar = U1RXREG ;
		udb_gps_callback_received_char(rxchar) ;
	}

	_U1RXIF = 0 ; // clear the interrupt
	
	if ( U1STAbits.OERR )
		U1STAbits.OERR = 0 ;
	
	interrupt_restore_extended_state ;
	return ;
}

// send a packet to UART1 (GPS)
void udb_gps_send_packet( unsigned char *ucpData, int len )
{
	indicate_loading_inter ;
	// check and limit len, max send first 511 bytes
	if ( len > 511 )
		len = 511;
	else ;
	// check if still have data to transmit, if not we reset pointers to begin of buffer
	if (iU1Head == iU1Tail)
	{	_DI();	// have to make sure no interrupt
		iU1Head = 0, iU1Tail = 0;	// reset - also make it easy to see what's going on
		_EI();
	};
	// first xfer data to private buffer
//	if ( (iU1Head + len) < TX_BUF_LEN )	// case of data fits with one memcpy
//	{	memcpy( &U1TX_buffer[iU1Head], ucpData, len );
//		iU1Head += len;
//	} else {							// will take multiple copies
//		memcpy( &U1TX_buffer[iU1Head], ucpData, (TX_BUF_LEN - iU1Head) );
//		ucpData += (TX_BUF_LEN - iU1Head);	// next address
//		len -= (TX_BUF_LEN - iU1Head);		// what's left
//		memcpy( &U1TX_buffer[0], ucpData, len );
//		iU1Head = len;
//	}

	do {	// when memcpy no longer fails this will be removed
		U1TX_buffer[iU1Head] = *ucpData;
		iU1Head++, ucpData++, len--;
		if ( iU1Head > TX_BUF_LEN )
			iU1Head = 0;
		else ;
	} while (len > 0);

	_U1TXIF = 1 ; // fire the tx interrupt

}

// Output one character to the GPS
void udb_gps_send_char( char outchar )
{
	unsigned char cSends[2];
	cSends[0] = outchar;
	udb_gps_send_packet( &cSends[0], 1 );
	
	return ;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U1TXInterrupt(void)
{
	unsigned char ucSend;
	indicate_loading_inter ;

	if (iU1Head != iU1Tail)	// have some to send
	{
		do {
			ucSend = U1TX_buffer[iU1Tail++];	// get next one to send
			if ( iU1Tail > TX_BUF_LEN )			// wrap at end of buffer
				iU1Tail = 0;
			else ;
			U1TXREG = ucSend;					// send it
		} while ( !U1STAbits.UTXBF && (iU1Head != iU1Tail));
	}
	_U1TXIF = 0 ; // clear the interrupt
}

/////////////////////////////////////////////////////////////////////////////////////////
// Serial

void udb_init_USART(void)
{
	// configure U2MODE
	U2MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//						// Bit14
	U2MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U2MODEbits.IREN = 0;	// Bit12 No IR translation
	U2MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//						// Bit10
	U2MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U2MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U2MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U2MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
#if (SERIAL_OUTPUT_INVERT == 1)
	U2MODEbits.URXINV = 1;	// Bit4 IdleState = 0  (for dsPIC)
#else
	U2MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
#endif
	U2MODEbits.BRGH = 1;	// Bit3 4 clocks per bit period
	U2MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U2MODEbits.STSEL = 0;	// Bit0 One Stop Bit
	
	// Load all values in for U1STA SFR
	U2STAbits.UTXISEL1 = 1;	//Bit15 Int when buffer empty, shift register still busy
#if (SERIAL_OUTPUT_INVERT == 1)
	U2STAbits.UTXINV = 1;	//Bit14 IdleState = 1  (for dsPIC)
#else
	U2STAbits.UTXINV = 0;	//Bit14 IdleState = 0  (for dsPIC)
#endif
	U2STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
	//				 		//Bit12
	U2STAbits.UTXBRK = 0;	//Bit11 Disabled
	//U2STAbits.UTXEN = 1;	//Bit10 TX pins controlled by periph (handled below)
	//U2STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	//U2STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U2STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U2STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	//U2STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	//U2STAbits.PERR = 0;	//Bit3 *Read Only Bit*
	//U2STAbits.FERR = 0;	//Bit2 *Read Only Bit*
	U2STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	//U2STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	_U2TXIP = 3;	// Mid Range Interrupt Priority level, no urgent reason
	_U2RXIP = 3;	// Mid Range Interrupt Priority level, no urgent reason

	_U2TXIF = 0;	// Clear the Transmit Interrupt Flag
	_U2TXIE = 1;	// Enable Transmit Interrupts
	_U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	_U2RXIE = 1;	// Enable Recieve Interrupts

	U2MODEbits.UARTEN = 1;	// And turn the peripheral on

	U2STAbits.UTXEN = 1;
	
	return ;
}


void udb_serial_set_rate(long int rate)
{
	U2BRG = UDB_BAUD(rate) ;
	return ;
}


void udb_serial_start_sending(void)
{
	_U2TXIF = 1 ; // fire the tx interrupt
	return ;
}



void __attribute__((__interrupt__, __no_auto_psv__)) _U2RXInterrupt(void)
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	while ( U2STAbits.URXDA )
	{
		unsigned char rxchar = U2RXREG ;
		udb_serial_callback_received_char(rxchar) ;
	}

	_U2RXIF = 0 ; // clear the interrupt

	if ( U2STAbits.OERR )
		U2STAbits.OERR = 0 ;
	
	// interrupt_restore_extended_state ;
	return ;
}

// send a packet to UART2
void udb_serial_send_packet( unsigned char *ucpData, int len )
{
	// check and limit len, max send first 511 bytes
	if ( len > 511 )
		len = 511;
	else ;
	// check if still have data to transmit, if not we reset pointers to begin of buffer
	if (iU2Head == iU2Tail)
	{	_DI();	// have to make sure no interrupt
		iU2Head = 0, iU2Tail = 0;	// reset - also make it easy to see what's going on
		_EI();
	};
	// first xfer data to private buffer
//	if ( (iU2Head + len) < TX_BUF_LEN )	// case of data fits with one memcpy
//	{	memcpy( &U2TX_buffer[iU2Head], ucpData, len );
//		iU1Head += len;
//	} else {							// will take multiple copies
//		memcpy( &U2TX_buffer[iU2Head], ucpData, (TX_BUF_LEN - iU2Head) );
//		ucpData += (TX_BUF_LEN - iU2Head);	// next address
//		len -= (TX_BUF_LEN - iU2Head);		// what's left
//		memcpy( &U2TX_buffer[0], ucpData, len );
//		iU2Head = len;
//	}

	do {	// when memcpy no longer fails this will be removed
		U2TX_buffer[iU2Head] = *ucpData;
		iU2Head++, ucpData++, len--;
		if ( iU2Head > TX_BUF_LEN )
			iU2Head = 0;
		else ;
	} while (len > 0);

	_U2TXIF = 1 ; // fire the tx interrupt

}

// send a null terminated string to UART2
void udb_serial_send_string( unsigned char *ucpData )
{
	int len = 0;
//	// check and limit len, max send first 511 bytes
//	if ( len > 511 )
//		len = 511;
//	else ;
	// check if still have data to transmit, if not we reset pointers to begin of buffer
	if (iU2Head == iU2Tail)
	{	_DI();	// have to make sure no interrupt
		iU2Head = 0, iU2Tail = 0;	// reset - also make it easy to see what's going on
		_EI();
	};
	// first xfer data to private buffer
//	if ( (iU2Head + len) < TX_BUF_LEN )	// case of data fits with one memcpy
//	{	memcpy( &U2TX_buffer[iU2Head], ucpData, len );
//		iU1Head += len;
//	} else {							// will take multiple copies
//		memcpy( &U2TX_buffer[iU2Head], ucpData, (TX_BUF_LEN - iU2Head) );
//		ucpData += (TX_BUF_LEN - iU2Head);	// next address
//		len -= (TX_BUF_LEN - iU2Head);		// what's left
//		memcpy( &U2TX_buffer[0], ucpData, len );
//		iU2Head = len;
//	}

	while ((len < 511) && *ucpData) 
	{	// when memcpy no longer fails this will be removed
		U2TX_buffer[iU2Head] = *ucpData;
		iU2Head++, ucpData++, len++;
		if ( iU2Head > TX_BUF_LEN )
			iU2Head = 0;
		else ;
	};

	_U2TXIF = 1 ; // fire the tx interrupt

}

// Output one character to the serial port
void udb_serial_send_char( char outchar )
{
	unsigned char cSends[2];
	cSends[0] = outchar;
	udb_serial_send_packet( &cSends[0], 1 );
	
	return ;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _U2TXInterrupt(void)
{
	unsigned char ucSend;

	if (iU2Head != iU2Tail)	// have some to send
	{
		while ( !U2STAbits.UTXBF && (iU2Head != iU2Tail))
		{
			ucSend = U2TX_buffer[iU2Tail++];	// get next one to send
			if ( iU2Tail > TX_BUF_LEN )			// wrap at end of buffer
				iU2Tail = 0;
			else ;
			U2TXREG = ucSend;					// send it
		};
	}
	_U2TXIF = 0 ; // clear the interrupt
}


#endif
