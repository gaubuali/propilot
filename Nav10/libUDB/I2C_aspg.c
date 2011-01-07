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

// TODO:	this needs to change allot because now we have ACCEL and
//			eeprom on this interface, along with being interrupt
//			driven by data ready lines
//
// Now seperated into an I2C BUS driver and device drivers. All actions
// on bus driven by a pseudo-code interpreter.

#include "libUDB_internal.h"

#if (BOARD_TYPE == ASPG_BOARD)

// #define I2C2_FCL 400000
// #define I2C2_BRGVAL (((I2C2_FCL/FREQOSC)-(FREQOSC/10000000)) - 1)
// set SYS_I2C to the I2C port to use

#define SYS_I2C 2
#if SYS_I2C == 1
#define I2CCON		I2C1CON
#define I2CCONbits	I2C1CONbits
#define I2CSTAT		I2C1STAT
#define I2CSTATbits I2C1STATbits
#define I2CBRG		I2C1BRG
#define I2CTRN		I2C1TRN
#define I2CRCV		I2C1RCV
#define SI2CIP		_SI2C1IP
#define	MI2CIP		_MI2C1IP
#define	SI2CIF		_SI2C1IF
#define	MI2CIF		_MI2C1IF
#define	SI2CIE		_SI2C1IE
#define	MI2CIE		_MI2C1IE
#define I2C_SDA		_LATG3
#define I2C_SCL		_LATG2
#define tI2C_SDA( x ) _TRISG3 = x, _ODCG3 = 1
#define tI2C_SCL( x ) _TRISG2 = x, _ODCG2 = 1
#elif SYS_I2C == 2
#define I2CCON		I2C2CON
#define I2CCONbits	I2C2CONbits
#define I2CSTAT		I2C2STAT
#define I2CSTATbits I2C2STATbits
#define I2CBRG		I2C2BRG
#define I2CTRN		I2C2TRN
#define I2CRCV		I2C2RCV
#define SI2CIP		_SI2C2IP
#define	MI2CIP		_MI2C2IP
#define	SI2CIF		_SI2C2IF
#define	MI2CIF		_MI2C2IF
#define	SI2CIE		_SI2C2IE
#define	MI2CIE		_MI2C2IE
#define I2C_SDA		_LATA3
#define I2C_SCL		_LATA2
#define tI2C_SDA( x ) _TRISA3 = x, _ODCA3 = 1
#define tI2C_SCL( x ) _TRISA2 = x, _ODCA2 = 1
#else
#error Must define SYS_I2C 1 or 2
#endif

// #define I2C2_BRGVAL 395
#define I2C2_BRGVAL 95
#define I2C_NORMAL ((( I2C2CON & 0b0000000000011111 ) == 0) && ( (I2C2STAT & 0b0100010011000001) == 0 ))

// buffer for EEProm read / write, ACC and MAG use their own private buffers
#define I2C_BUF_LEN 128		// page write size
char __attribute__ ((section(".myDataSection"),address(0x2280))) I2C_buffer[I2C_BUF_LEN];	// EE read and write
int	I2C_Head, I2C_Tail;

void udb_init_I2C2(void)
{

	tI2C_SDA(0), tI2C_SCL(0);					// set them as outputs for later
	I2CCON = 0;									// clear
	I2C_SDA = I2C_SCL = 0;						// force both low, bus reset
	I2CBRG = I2C2_BRGVAL;						// config baud rate
	I2CCONbits.SCLREL = 1;
	I2CCONbits.DISSLW = 0 ;						// config I2C
	I2C_SDA = I2C_SCL = 1;						// force both high, bus reset

//	SI2CIP = 5 ; // slave I2C at priority 5
	MI2CIP = 5 ; // master I2C at priority 5
//	SI2CIF = 0 ; // clear the I2C slave interrupt
	MI2CIF = 0 ; // clear the I2C master interrupt
//	SI2CIE = 1 ; // slave enable the interrupt
	MI2CIE = 1 ; // master enable the interrupt

	I2CCONbits.I2CEN = 1 ; 						// enable I2C
#if ( MAG_YAW_DRIFT == 1 )
	MAG_INTpr = 2, MAG_DRt = 1, MAG_INTf = 0, MAG_INTpo = 0;
	MAG_INTe = 1;	// input pin, int on high & enabled, cleared
#endif
	ACC_INTpr = 2, ACC_DRt = 1, ACC_INTf = 0, ACC_INTpo = 0;
	ACC_INTe = 1;	// input pin, int on high & enabled, cleared

	return ;
}

I2C_Action uI2C_Commands[64];	// command buffer
int I2C_Index = 0;			// current command
int I2CERROR = 0, I2CERROR_CON = 0, I2CERROR_STAT = 0;	// record for errors
int I2Cinterrupts = 0 ;
int I2Cmessages = 0;
int I2C_Subcode = 0, I2C_Sublen = 0;
I2C_Action I2C_Code;
int I2C_Slave = 0;		// on a start condition saves the slave address
// int I2C_Address = 0;	// tries to keep track of current address by increment by one on each read
						// no way shape or form should this be counted on unless set externally and
						// addressed device is totally simple
int I2C_Timeout = 0;	// simple counter decremented to 0 in T3 interrupt (servoOut_aspg.c)


#if SYS_I2C == 1
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C1Interrupt(void)
#elif SYS_I2C == 2
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C2Interrupt(void)
#endif
{
	unsigned char uByte;
    indicate_loading_inter ;
	MI2CIF = 0 ; // clear the interrupt
	if (oLED2 == LED_OFF)
		oLED2 = LED_ON;
	else oLED2 = LED_OFF;
	if ( I2C_Index > 63)	// run-away, terminate
	{	I2C_Index = 61;								// end it
		uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
		uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
		I2C_Subcode = 0, I2CERROR = RUNAWAY;			// say reason for termination
	};

	switch ( I2C_Subcode ) {
		case 0:	// starting
			I2C_Code.uInt = uI2C_Commands[I2C_Index].uInt;	// save it
			switch (I2C_Code.tagF.uCmd ) {
				// 0=nothing, 1=start, 2=restart, 3=stop, 4=TX, 5=RX with ACK, 6=RX 1 with NACK, 7=finished
				case NOTHING:	// nominal first command to make I2C_Index != 0, thus I2C busy
					I2C_Index++;
					MI2CIF = 1 ; // re-trigger the interrupt
				break;
				case START:
					I2CCONbits.SEN = 1;		// start up bus
					I2C_Subcode = START;
				break;
				case RESTART:
					I2CCONbits.RSEN = 1;	// restart
//					I2C_Index++;
					I2C_Subcode = RESTART;
				break;
				case STOP:
					I2CCONbits.PEN = 1;		// stop bus
//					I2C_Index++;
					I2C_Subcode = STOP;
				break;
				case TX:
					I2CCONbits.ACKDT = 0;
					I2C_Subcode = TX_LOW;
					I2C_Sublen = I2C_Code.tagF.uCount;
					I2C_Index++;
					MI2CIF = 1 ; // re-trigger the interrupt
				break;
				case RX_ACK:
					I2CCONbits.RCEN = 1;	// receive bytes with ACK's
					I2C_Subcode = RX_ACK;
					I2C_Sublen = I2C_Code.tagF.uCount;
					// I2C_Index++;		// done once receive finished
				break;
				case RX_NACK:
					I2CCONbits.RCEN = 1;	// receive 1 then NACK
					I2C_Subcode = RX_NACK;
					I2C_Sublen = I2C_Code.tagF.uCount;
					// I2C_Index++;		// done once receive finished
				break;
				case FINISHED:
					I2C_Subcode = FINISHED;	// set this to finished as well
					I2C_Timeout = -1;		// show got to finished rather than timeout
//					I2C_Index++;			// done, remember to stop bus first please
				break;
			}
		break;	// starting
		case START:		// bus started now sending address
			if ( I2C_Code.tagF.uACK )
				I2C_Subcode = START_NA;						// no ACKSTAT check
			else I2C_Subcode = START_ACK;					// check ACKSTAT bit, still checks other errors
			I2C_Slave = I2C_Code.uChar[1];					// save it
			I2CTRN = I2C_Slave;								// send it
//			I2C_Index++;									// point to next command
		break;
		case START_ACK: // started and check device responded
			if ( I2CSTATbits.ACKSTAT == 1 )
				I2CERROR = NO_ACK;							// no ACK received
		case START_NA: // check other bus errors
			if ( !I2C_NORMAL )
				I2CERROR = BUS;								// some other bus error
			else ;
			I2C_Subcode = NOTHING;							// either way do next command
			I2C_Index++;									// point to next
			if ( I2CERROR )
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;	// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED; // then finished
			};
			MI2CIF = 1;			 							// re-trigger the interrupt
		break;
		case RESTART:	// same handling as start but resends the stored address in read mode (ie bit0 = 1)
			if ( uI2C_Commands[I2C_Index].tagF.uACK )
				I2C_Subcode = START_NA;						// no ACKSTAT check
			else I2C_Subcode = START_ACK;					// check ACKSTAT bit, still checks other errors
			I2CTRN = (I2C_Slave | 0x01);					// send it
//			I2C_Index++;									// point to next command
		break;
		case STOP:
//			I2CCONbits.PEN = 1;		// stop bus
			I2C_Index++;
			I2C_Subcode = NOTHING;
			MI2CIF = 1;			 							// re-trigger the interrupt
		break;
		case TX_LOW:
			if ( I2CSTATbits.ACKSTAT == 1 )					// always expects ACK
				I2CERROR = NO_ACK;							// no ACK received
			if ( !I2C_NORMAL )								// and no bus errors
				I2CERROR = BUS;								// some other bus error
			else ;
			if ( I2CERROR )									// save info for debug etc
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
				I2C_Subcode = NOTHING;						// either way do next command
				MI2CIF = 1;		 							// re-trigger the interrupt
			} else {
				if ( I2C_Code.tagF.uBuf ) 
				{
					I2CTRN = I2C_buffer[I2C_Tail++];		// send it
				} else {
//					I2C_Index++;							// point to next one to send
					I2CTRN = uI2C_Commands[I2C_Index].uChar[0];	// send it
					I2C_Subcode = TX_HIGH;					// set to send other byte in pair
				}
				I2C_Sublen--;								// reduce length
				if ( I2C_Sublen < 0 )
					I2C_Subcode = NOTHING, I2C_Index++;	// run out of bytes to send
			}
		break;
		case TX_HIGH:
			if ( I2CSTATbits.ACKSTAT == 1 )					// always expects ACK
				I2CERROR = NO_ACK;							// no ACK received
			if ( !I2C_NORMAL )								// and no bus errors
				I2CERROR = BUS;								// some other bus error
			else ;
			if ( I2CERROR )									// save info for debug etc
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
				I2C_Subcode = NOTHING;						// either way do next command
				MI2CIF = 1;		 							// re-trigger the interrupt
			} else {
				if ( I2C_Code.tagF.uBuf ) 
				{
					I2CTRN = I2C_buffer[I2C_Tail++];		// send it
				} else {
					I2CTRN = uI2C_Commands[I2C_Index].uChar[1];	// send it
					I2C_Subcode = TX_LOW;					// set to send other byte in pair
				}
				I2C_Sublen--;								// reduce length
				I2C_Index++;								// point to next one to send / command
				if ( I2C_Sublen < 0 )
					I2C_Subcode = NOTHING;					// run out of bytes to send
			}
		break;
		case RX_ACK:										// last byte always NACK received
			if ( !I2CSTATbits.RBF )
				I2CERROR = NO_REC;							// did not get a byte for some reason
			else uByte = I2CRCV;
			if ( !I2C_NORMAL )								// and no bus errors
				I2CERROR = BUS;								// some other bus error
			else ;
			if ( I2CERROR )									// save info for debug etc
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
				I2C_Subcode = NOTHING;						// either way do next command
				MI2CIF = 1;		 							// re-trigger the interrupt
			} else {
//				if ( I2C_Code.uRec )						// check if we want to save it
				I2C_buffer[I2C_Head++] = uByte;				// save it
				I2C_Sublen--;								// point to next one to send
				if ( I2C_Sublen < 0 )
				{	I2C_Subcode = RX_NACK_CLK;				// run out of bytes to rec
//					I2CCONbits.RCEN = 1;
					I2CCONbits.ACKDT = 1;					// clk 9th bit with NACK
					I2CCONbits.ACKEN = 1;
				} else {
					I2C_Subcode = RX_ACK_CLK;				// run out of bytes to rec
//					I2CCONbits.RCEN = 1;
					I2CCONbits.ACKDT = 0;					// clk 9th bit with ACK
					I2CCONbits.ACKEN = 1;
				}
			}
		break;
		case RX_ACK_CLK:									// send 9th bit
			if ( !I2C_NORMAL )								// and no bus errors
				I2CERROR = BUS;								// some other bus error
			else ;
			if ( I2CERROR )									// save info for debug etc
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
				I2C_Subcode = NOTHING;						// either way do next command
				MI2CIF = 1;		 							// re-trigger the interrupt
			} else {
				I2C_Subcode = RX_ACK;						// do next one
				I2CCONbits.RCEN = 1;
			}
		break;
		case RX_NACK:										// last byte always NACK received
			if ( !I2CSTATbits.RBF )
				I2CERROR = NO_REC;							// did not get a byte for some reason
			else uByte = I2CRCV;
			if ( !I2C_NORMAL )								// and no bus errors
				I2CERROR = BUS;								// some other bus error
			else ;
			if ( I2CERROR )									// save info for debug etc
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
				I2C_Subcode = NOTHING;						// either way do next command
			} else {
//				if ( I2C_Code.uRec )						// check if we want to save it
				I2C_buffer[I2C_Head++] = uByte;				// save it
//				I2C_Subcode = NOTHING, I2C_Index++;		// run out of bytes to rec
				I2CCONbits.ACKDT = 1;					// clk 9th bit with NACK
				I2CCONbits.ACKEN = 1;
				I2C_Subcode = RX_NACK_CLK;				// run out of bytes to rec			
			}
		break;
		case RX_NACK_CLK:									// send 9th bit
			if ( !I2C_NORMAL )								// and no bus errors
				I2CERROR = BUS;								// some other bus error
			else ;
			if ( I2CERROR )									// save info for debug etc
			{
				I2CERROR_CON = I2CCON, I2CERROR_STAT = I2CSTAT;	// store
				uI2C_Commands[I2C_Index].uChar[0] = STOP;		// make next command stop bus
				uI2C_Commands[I2C_Index+1].uChar[0] = FINISHED;	// then finished
				I2C_Subcode = NOTHING;						// either way do next command
			} else {
				I2C_Subcode = NOTHING, I2C_Index++;			// run out of bytes to rec
			}
			MI2CIF = 1;		 								// re-trigger the interrupt
		break;
	}

	return ;
}

void I2C_Start( int T_O )
{
	if ( T_O < 2 )											// set 2ms minimum timeout
		I2C_Timeout = 2;
	else I2C_Timeout = T_O;

	I2C_Subcode = NOTHING, I2C_Head = I2C_Index = 0;		// reset everything
	I2CERROR = I2CERROR_CON = I2CERROR_STAT = NOTHING;		// store
	MI2CIF = 1 ; // Start the interrupt, may need to do checks here for bus busy
}

#endif
