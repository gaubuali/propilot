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
#define iI2C_SDA	_RG3
#define iI2C_SCL	_RG2
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
#define iI2C_SDA	_RA3
#define iI2C_SCL	_RA2
#else
#error Must define SYS_I2C 1 or 2
#endif

// #define I2C2_BRGVAL 395
#define I2C2_BRGVAL 95
#define I2C_NORMAL ((( I2C2CON & 0b0000000000011111 ) == 0) && ( (I2C2STAT & 0b0100010011000001) == 0 ))

void I2C_default(void);

// buffer for EEProm read / write, ACC and MAG use their own private buffers
unsigned char __attribute__ ((section(".myDataSection"),address(0x2270))) I2C_buffer[I2C_BUF_LEN];	// peripheral buf
void (* I2C_call_back[8] ) ( void ) = { &I2C_default, &I2C_default,
										&I2C_default, &I2C_default,
										&I2C_default, &I2C_default,
										&I2C_default, &I2C_default };

const I2C_Action busReset[] = {  
	{.uChar[0] = 0},					// empty to make Index step
	{.F.uCmd = START, .F.uACK = 1, .F.uCount = 0x01}, // start command with address, ack don't care
	{.F.uCmd = STOP},					// then bus stop
	{.F.uCmd = FINISHED}				// finished, no callback / post process
};

I2C_Action uI2C_Commands[I2C_COM_LEN];	// command buffer
I2CCMD CC;		// peripheral driver command buffer, never mess with this
I2CCMD CD[8] = {// device driver command buffers - when finished CC gets copied
				// back here - do not use 0 as its used by the peripheral driver.
				// use one of these for each device.
	{.Ident = 0, .piResult = &CD[0].iResult, .pcResult = &I2C_buffer[0] },	// safe default of pointers
	{            .piResult = &CD[1].iResult, .pcResult = &I2C_buffer[0] },	// and not setting ident gives
	{            .piResult = &CD[2].iResult, .pcResult = &I2C_buffer[0] },	// the drivers a convient way 
	{            .piResult = &CD[3].iResult, .pcResult = &I2C_buffer[0] },	// of detecting startup and doing
	{            .piResult = &CD[4].iResult, .pcResult = &I2C_buffer[0] },	// one time init of their
	{            .piResult = &CD[5].iResult, .pcResult = &I2C_buffer[0] },	// private data
	{            .piResult = &CD[6].iResult, .pcResult = &I2C_buffer[0] },
	{            .piResult = &CD[7].iResult, .pcResult = &I2C_buffer[0] },
};

int I2Cinterrupts = 0 ;
unsigned int I2Cmessages = 0;

// int I2C_Address = 0;	// tries to keep track of current address by increment by one on each read
						// no way shape or form should this be counted on unless set externally and
						// addressed device is totally simple
int I2C_Timeout = 0;	// simple counter decremented to 0 in T3 interrupt (servoOut_aspg.c)

struct tagI2C_flags I2C_flags;	// defined in ConfigASPG.h
//	unsigned int bInUse:1;		// in use right now
//	unsigned int bERROR:1;		// in use right now, restarting
//	unsigned int bMagReady:1;	// mag needs to be read
//	unsigned int bAccReady:1;	// Accelerometer needs to be read
//	unsigned int bReadMag:1;	// reading mag
//	unsigned int bReadAcc:1;	// reading Accelerometer
//	unsigned int bReadEE1:1;	// reading EE Prom, stage 1
//	unsigned int bReadEE2:1;	// reading EE Prom, stage 2
//	unsigned int bReadEE3:1;	// reading EE Prom, stage 3 (done)
//	unsigned int bWriteEE1:1;	// write EE Prom, stage 1
//	unsigned int bWriteEE2:1;	// write EE Prom, stage 2
//	unsigned int bWriteEE3:1;	// write EE Prom, stage 2 (done)

int	I2C_one_time_init = 0;
union longbbbb tow_error_save;	// save time it happened
extern union longbbbb tow;	// save time it happened

void udb_init_I2C2(void)
{
	int	iCounter, iGiveUp;
	I2CCONbits.I2CEN = 0 ; 						// disable I2C
	SI2CIE = 0 ; // slave disable the interrupt
	MI2CIE = 0 ; // master disable the interrupt
	tI2C_SDA(0), tI2C_SCL(0);					// set them as outputs for later
	I2CCON = 0;									// clear
	I2C_SDA = I2C_SCL = 0;						// force both low, bus reset
	I2CBRG = I2C2_BRGVAL;						// config baud rate
	I2CCONbits.SCLREL = 1;
	I2CCONbits.DISSLW = 0 ;						// config I2C
	I2C_SDA = I2C_SCL = 1;						// force both high, bus reset
	if ( (iI2C_SDA != 1) || (iI2C_SCL != 1) )	// try reset bus
	{	iGiveUp = 0;							// of course nothing we can do
		do {									// if a slave is streching SCL
			for ( iCounter = 1; iCounter < 32; iCounter++ )
				;
			I2C_SCL = 0;
			for ( iCounter = 1; iCounter < 32; iCounter++ )
				;
			I2C_SCL = 1;
			for ( iCounter = 1; iCounter < 32; iCounter++ )
				;
			iGiveUp++;
		} while (((iI2C_SDA != 1) || (iI2C_SCL != 1)) && iGiveUp <= 100);
		if ( iGiveUp >= 100 )					// gave up, mark bus as in use
			I2C_flags.bInUse = 1, CC.I2CERROR = BUS; // un-recoverable bus error
	}

//	SI2CIP = 4 ; // slave I2C at priority 4
	MI2CIP = 4 ; // master I2C at priority 4
//	SI2CIF = 0 ; // clear the I2C slave interrupt
	MI2CIF = 0 ; // clear the I2C master interrupt
//	SI2CIE = 1 ; // slave enable the interrupt
	MI2CIE = 1 ; // master enable the interrupt

	I2CCONbits.I2CEN = 1 ; 						// enable I2C
	if ( I2C_one_time_init == 0 )
	{
		I2C_one_time_init = 1;
#if ( MAG_YAW_DRIFT == 1 )
		MAG_INTpr = 2, MAG_DRt = 1, MAG_INTf = 0, MAG_INTpo = 0;
		MAG_INTe = 0;	// input pin, int on high & disabled, cleared
#endif
		ACC_INTpr = 2, ACC_DRt = 1, ACC_INTf = 0, ACC_INTpo = 0;
		ACC_INTe = 0;	// input pin, int on high & disabled, cleared

		uI2C_Commands[I2C_COM_LEN-2] = busReset[2];	// stop action
		uI2C_Commands[I2C_COM_LEN-1] = busReset[3];	// finished action
	};
	return ;
}

#if SYS_I2C == 1
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C1Interrupt(void)
#elif SYS_I2C == 2
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C2Interrupt(void)
#endif
{
	unsigned char uByte, *lpByte;
    indicate_loading_inter ;
	interrupt_save_extended_state ;
	MI2CIF = 0 ; // clear the interrupt
#if ( LED_RED_MAG_CHECK == 1 )
	if ( magMessage == 7 )
	{
		LED_RED = LED_OFF ;
	}
	else
	{
		LED_RED = LED_ON ;
	}
#endif

/*
	if ( I2CCONbits.I2CEN == 0 ) // I2C is off
	{
		I2C_state = &I2C_idle ; // disable response to any interrupts
		I2C_SDA = 1, I2C_SCL = 1 ; // pull SDA and SCL high
		udb_init_I2C2() ; // turn the I2C back on
		magMessage = 0 ; // start over again
		return ;
	}
	if (  I2C_NORMAL )
	{
	} 	else 	{
		I2C_state = &I2C_idle;		// disable the response to any more interrupts
		magMessage = 0; 			// start over again
//		I2ERROR = I2CSTAT ; 		// record the error for diagnostics
		I2CCONbits.I2CEN = 0; 		// turn off the I2C
		MI2CIF = 0;					// clear the I2C master interrupt
		MI2CIE = 0; 				// disable the interrupt
		I2C_SDA = 0, I2C_SCL = 0;	// pull SDA and SCL low
		return ;
	}
*/


	if ( CC.I2C_Index > 63)	// run-away, terminate
	{	CC.I2C_Index = 61;										// end it
		uI2C_Commands[CC.I2C_Index].uChar[0] = STOP;			// make next command stop bus
		uI2C_Commands[CC.I2C_Index+1].uChar[0] = FINISHED;		// then finished
		CC.I2C_Subcode = 0, CC.I2CERROR = RUNAWAY;				// say reason for termination
	};

	switch ( CC.I2C_Subcode ) {
		case 0:	// starting
			CC.I2C_Code.uInt = uI2C_Commands[CC.I2C_Index].uInt;	// save it
			switch (CC.I2C_Code.F.uCmd ) {
				// 0=nothing, 1=start, 2=restart, 3=stop, 4=TX, 5=RX with ACK, 6=RX 1 with NACK, 7=finished
				case NOTHING:	// nominal first command to make I2C_Index != 0, thus I2C busy
					CC.I2C_Index++;
					MI2CIF = 1 ;								// re-trigger the interrupt
				break;
				case START:
					I2CCONbits.SEN = 1;							// start up bus
					CC.I2C_Subcode = START;
				break;
				case RESTART:
					I2CCONbits.RSEN = 1;						// restart
					CC.I2C_Subcode = RESTART;
				break;
				case STOP:
					I2CCONbits.PEN = 1;							// stop bus
					CC.I2C_Subcode = STOP;
				break;
				case TX:
					I2CCONbits.ACKDT = 0;
					CC.I2C_Subcode = TX_LOW;
					CC.I2C_Sublen = CC.I2C_Code.F.uCount;
					CC.I2C_Index++;
					MI2CIF = 1 ;								// re-trigger the interrupt
				break;
				case RX_ACK:
					I2CCONbits.RCEN = 1;						// receive bytes with ACK's
					CC.I2C_Subcode = RX_ACK;
					CC.I2C_Sublen = CC.I2C_Code.F.uCount;
				break;
				case RX_NACK:
					I2CCONbits.RCEN = 1;						// receive 1 then NACK
					CC.I2C_Subcode = RX_NACK;
					CC.I2C_Sublen = CC.I2C_Code.F.uCount;
				break;
				case FINISHED:

	if (oLED2 == LED_OFF)
		oLED2 = LED_ON;
	else oLED2 = LED_OFF;

					CC.I2C_Subcode = FINISHED;					// set this to finished as well
					I2C_Timeout = -1;							// show got to finished rather than timeout
					switch ( CC.I2C_Code.F.uResult ) {			// do finished actions
						case NOTHING:
						default:
						break;
						case RSET:	// set .iResult to .uCount
							CC.iResult = CC.I2C_Code.uChar[1];	// set mode
						break;
						case RADD:	// add .uCount to iResult
							CC.iResult += CC.I2C_Code.uChar[1];	// add mode
						break;
						case PSET:	// set *ipResult to .uCount
							*CC.piResult = CC.I2C_Code.uChar[1];	// set mode
						break;
						case PADD:	// add .uCount to iResult
							*CC.piResult += CC.I2C_Code.uChar[1];	// add mode
						case CCPY:								// copy .uCount characters to *puResult
						case HCPY:								// copy .uCount characters to *puResult
							if ( CC.I2C_Code.F.uResult == CCPY )
								CC.I2C_Sublen = CC.I2C_Code.uChar[1];
							else CC.I2C_Sublen = CC.I2C_Head;
							CC.I2C_Tail = 0;						// start at begin of buffer
							lpByte = CC.pcResult;					// get destination address
							if ( (CC.I2C_Sublen >= 1) && (CC.I2C_Sublen <= I2C_BUF_LEN) ) // check
								while ( CC.I2C_Sublen-- )
									*lpByte = I2C_buffer[CC.I2C_Tail++], lpByte++;
						break;
					}
					if ( CC.I2C_Code.F.uACK )
						CC.iResult += 1;							// update iResult
					CC.Messages++;									// messages to this driver
					CD[CC.Ident&0x7] = CC;							// store result state
					if ( CC.I2C_Code.F.uBuf )
						(* I2C_call_back[CC.Ident&0x7]) () ;		// execute the callback routine
					I2Cmessages++;									// global messages
					// TODO: check I2C_Flags and process
//					if ( I2C_flags.bMagReady || (iMAG_DR1 & MAG_INTe) )	// high priority as it has no buffer
					if ( I2C_flags.bMagReady )	// high priority as it has no buffer
					{
						magSetupRead();	// do a read of device
//						I2C_Start( 0 );								// re-trigger the interrupt
						MI2CIF = 1;									// re-trigger the interrupt
					} else
					if ( I2C_flags.bAccReady || iACC_DR1)	// lower priority as it has buffer
//					if ( I2C_flags.bAccReady || ACC_INTe)	// lower priority as it has buffer
					{	uByte = iACC_DR1;
						if ( (I2C_buffer[7] & 0x1f) || I2C_flags.bAccReady )
						{
							accSetupRead();	// do a read of device
//							I2C_Start( 0 );							// re-trigger the interrupt
							MI2CIF = 1;								// re-trigger the interrupt
						} else I2C_flags.bInUse = 0;
					} else I2C_flags.bInUse = 0;
				break;
			}
		break;	// starting
		case START:													// bus started now sending address
			if ( CC.I2C_Code.F.uACK )
				CC.I2C_Subcode = START_NA;							// no ACKSTAT check
			else CC.I2C_Subcode = START_ACK;						// check ACKSTAT bit, still checks other errors
			CC.I2C_Slave = CC.I2C_Code.uChar[1];					// save it
			I2CTRN = CC.I2C_Slave;									// send it
		break;
		case START_ACK: // started and check device responded
			if ( I2CSTATbits.ACKSTAT == 1 )
				CC.I2CERROR = NO_ACK;								// no ACK received
		case START_NA: // check other bus errors
			if ( !I2C_NORMAL )
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			CC.I2C_Subcode = NOTHING;								// either way do next command
			CC.I2C_Index++;											// point to next
			if ( CC.I2CERROR )
				goto I2C_ERROR;										// process error
			else MI2CIF = 1;										// re-trigger the interrupt
		break;
		case RESTART:	// same handling as start but resends the stored address in read mode (ie bit0 = 1)
			if ( uI2C_Commands[CC.I2C_Index].F.uACK )
				CC.I2C_Subcode = START_NA;							// no ACKSTAT check
			else CC.I2C_Subcode = START_ACK;						// check ACKSTAT bit, still checks other errors
			if ( uI2C_Commands[CC.I2C_Index].F.uBuf )				// make read
				I2CTRN = (CC.I2C_Slave | 0x01);						// send it
			else {
				CC.I2C_Slave = CC.I2C_Code.uChar[1];				// save it
				I2CTRN = CC.I2C_Slave;								// send it
			};
		break;
		case STOP:
			CC.I2C_Index++;
			CC.I2C_Subcode = NOTHING;
			MI2CIF = 1;												// re-trigger the interrupt
		break;
		case TX_LOW:
			if ( I2CSTATbits.ACKSTAT == 1 )							// always expects ACK
				CC.I2CERROR = NO_ACK;								// no ACK received
			if ( !I2C_NORMAL )										// and no bus errors
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			if ( CC.I2CERROR )										// save info for debug etc
			{
				goto I2C_ERROR;										// process error
			} else {
				if ( CC.I2C_Code.F.uBuf )
				{
					I2CTRN = I2C_buffer[CC.I2C_Tail++];				// send it
				} else {
//					CC.I2C_Index++;									// point to next one to send
					I2CTRN = uI2C_Commands[CC.I2C_Index].uChar[0];	// send it
					CC.I2C_Subcode = TX_HIGH;						// set to send other byte in pair
				}
				CC.I2C_Sublen--;									// reduce length
				if ( CC.I2C_Sublen < 0 )
					CC.I2C_Subcode = NOTHING, CC.I2C_Index++;		// run out of bytes to send
			}
		break;
		case TX_HIGH:
			if ( I2CSTATbits.ACKSTAT == 1 )							// always expects ACK
				CC.I2CERROR = NO_ACK;								// no ACK received
			if ( !I2C_NORMAL )										// and no bus errors
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			if ( CC.I2CERROR )										// save info for debug etc
			{
				goto I2C_ERROR;										// process error
			} else {
				if ( CC.I2C_Code.F.uBuf )
				{
					I2CTRN = I2C_buffer[CC.I2C_Tail++];				// send it
				} else {
					I2CTRN = uI2C_Commands[CC.I2C_Index].uChar[1];	// send it
					CC.I2C_Subcode = TX_LOW;						// set to send other byte in pair
				}
				CC.I2C_Sublen--;									// reduce length
				CC.I2C_Index++;										// point to next one to send / command
				if ( CC.I2C_Sublen < 0 )
					CC.I2C_Subcode = NOTHING;						// run out of bytes to send
			}
		break;
		case RX_ACK:												// last byte always NACK received
			if ( !I2CSTATbits.RBF )
				CC.I2CERROR = NO_REC;								// did not get a byte for some reason
			else uByte = I2CRCV;
			if ( !I2C_NORMAL )										// and no bus errors
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			if ( CC.I2CERROR )										// save info for debug etc
			{
				goto I2C_ERROR;										// process error
			} else {
//				if ( CC.I2C_Code.uRec )								// check if we want to save it
				I2C_buffer[CC.I2C_Head++] = uByte;					// save it
				CC.I2C_Sublen--;									// point to next one to send
				if ( CC.I2C_Sublen < 0 )
				{	CC.I2C_Subcode = RX_NACK_CLK;					// run out of bytes to rec
					I2CCONbits.ACKDT = 1;							// clk 9th bit with NACK
					I2CCONbits.ACKEN = 1;
				} else {
					CC.I2C_Subcode = RX_ACK_CLK;					// run out of bytes to rec
					I2CCONbits.ACKDT = 0;							// clk 9th bit with ACK
					I2CCONbits.ACKEN = 1;
				}
			}
		break;
		case RX_ACK_CLK:											// send 9th bit
			if ( !I2C_NORMAL )										// and no bus errors
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			if ( CC.I2CERROR )										// save info for debug etc
			{
				goto I2C_ERROR;										// process error
			} else {
				CC.I2C_Subcode = RX_ACK;							// do next one
				I2CCONbits.RCEN = 1;
			}
		break;
		case RX_NACK:												// last byte always NACK received
			if ( !I2CSTATbits.RBF )
				CC.I2CERROR = NO_REC;								// did not get a byte for some reason
			else uByte = I2CRCV;
			if ( !I2C_NORMAL )										// and no bus errors
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			if ( CC.I2CERROR )										// save info for debug etc
			{
				goto I2C_ERROR;										// process error
			} else {
				I2C_buffer[CC.I2C_Head++] = uByte;					// save it
//				CC.I2C_Subcode = NOTHING, I2C_Index++;				// run out of bytes to rec
				I2CCONbits.ACKDT = 1;								// clk 9th bit with NACK
				I2CCONbits.ACKEN = 1;
				CC.I2C_Subcode = RX_NACK_CLK;						// run out of bytes to rec
			}
		break;
		case RX_NACK_CLK:											// send 9th bit
			if ( !I2C_NORMAL )										// and no bus errors
				CC.I2CERROR = BUS;									// some other bus error
			else ;
			if ( CC.I2CERROR )										// save info for debug etc
			{	
				goto I2C_ERROR;										// process error
			} else {
				CC.I2C_Subcode = NOTHING, CC.I2C_Index++;			// run out of bytes to rec
			}
			MI2CIF = 1;												// re-trigger the interrupt
		break;
	}

	goto I2C_DONE;
I2C_ERROR:
	CC.I2CERROR_CON = I2CCON, CC.I2CERROR_STAT = I2CSTAT;	// store
	CD[0] = CC, tow_error_save = tow;					// store error state
	CC.I2C_Index = I2C_COM_LEN-2;						// make next command stop bus
	CC.I2C_Subcode = NOTHING;							// either way do next command
	if ( CC.I2CERROR == BUS )							// reset module
		udb_init_I2C2();
	else ;
	MI2CIF = 1;											// re-trigger the interrupt
I2C_DONE:
	interrupt_restore_extended_state ;
}

void I2C_Start( int T_O )
{
	if ( (abs(T_O)) < 2 )						// set 2ms minimum timeout
		I2C_Timeout = 3;
	else I2C_Timeout = abs(T_O);

	if ( T_O >= 0 )						// call with negative number to just trigger
	{
		CC.I2C_Subcode = NOTHING; 		// otherwise reset everything
		CC.I2C_Tail = 0, CC.I2C_Head = 0;
		CC.I2C_Index = 0;
		CC.I2CERROR = NOTHING, CC.I2CERROR_CON = NOTHING;
		CC.I2CERROR_STAT = NOTHING;		// store
	};
	MI2CIF = 1 ;	// Start the interrupt, may need to do checks here for bus busy
					// but this is also the only way to get out of a timeout
}

void I2C_Reset( void )
{
	udb_init_I2C2();	// turn off then turn on module
	uI2C_Commands[0] = busReset[0];
	uI2C_Commands[1] = busReset[1];
	uI2C_Commands[2] = busReset[2];
	I2C_Start( 0 );		// fake start and stop on address 0
}

void I2C_default(void)
{
        return ;
}

#endif
