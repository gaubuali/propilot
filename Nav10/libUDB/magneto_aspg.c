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

#include "libUDB_internal.h"

#if (BOARD_TYPE == ASPG_BOARD)

//const unsigned char enableMagRead[] =        { 0x3C , 0x00 , 0x10 , 0x20 , 0x00 } ;
const unsigned char enableMagRead[] =        { 0x3C , 0x00 , 0x18 , 0x20 , 0x00 } ;	// changed to 50Hz output
const unsigned char enableMagCalibration[] = { 0x3C , 0x00 , 0x11 , 0x20 , 0x01 } ;
const unsigned char resetMagnetometer[]    = { 0x3C , 0x00 , 0x10 , 0x20 , 0x02 } ;

void I2C_readMagData(void) ;
void I2C_writeMagCommand(void) ;

void I2C_startReadMagData(void) ;
void I2C_stopReadMagData(void) ;
void I2C_doneReadMagData(void) ;
void I2C_recen(void) ;
void I2C_recstore(void) ;

void I2C_WriteMagData(void) ;
void I2C_stopWriteMagData(void) ;

void I2C_idle(void) ;

int udb_magFieldBody[3] ;  // magnetic field in the body frame of reference 
int udb_magOffset[3] = { 0 , 0 , 0 } ;  // magnetic offset in the body frame of reference
int magGain[3] = { RMAX , RMAX , RMAX } ; // magnetometer calibration gains
int rawMagCalib[3] = { 0 , 0 , 0 } ;
unsigned char magreg[6] ;  // magnetometer read-write buffer

int I2ERROR = 0 ;
int I2interrupts = 0 ;

void (* I2C_state ) ( void ) = &I2C_idle ;

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
#define I2C2_BRGVAL 395
#define I2C_NORMAL ((( I2C2CON & 0b0000000000011111 ) == 0) && ( (I2C2STAT & 0b0100010011000001) == 0 ))

// buffer for EEProm read / write, ACC and MAG use their own private buffers
#define I2C_BUF_LEN 128		// page write size
char __attribute__ ((section(".myDataSection"),address(0x2280))) I2C_buffer[I2C_BUF_LEN];	// read and write
int	I2C_Head, I2C_Tail;

struct tagI2C_flags I2C_flags;	// defined in ConfigASPG.h
//	unsigned int bInUse:1;		// in use right now
//	unsigned int bERROR:1;		// in use right now, restarting
//	unsigned int bMagCfg:1;		// mag config - should be 1
//	unsigned int bMagCal:1;		// mag calibration
//	unsigned int bMagReady:1;	// mag needs to be read
//	unsigned int bAccCfg:1;		// Acc config - should be 1
//	unsigned int bAccCal:1;		// Acc calibration
//	unsigned int bAccReady:1;	// Accelerometer needs to be read
//	unsigned int bReadMag:1;	// reading mag
//	unsigned int bReadAcc:1;	// reading Accelerometer
//	unsigned int bReadEE1:1;	// reading EE Prom, stage 1
//	unsigned int bReadEE2:1;	// reading EE Prom, stage 2
//	unsigned int bReadEE3:1;	// reading EE Prom, stage 3 (done)
//	unsigned int bWriteEE1:1;	// write EE Prom, stage 1
//	unsigned int bWriteEE2:1;	// write EE Prom, stage 2
//	unsigned int bWriteEE3:1;	// write EE Prom, stage 2 (done)

void udb_init_I2C2(void)
{

	tI2C_SDA(0), tI2C_SCL(0);					// set them as outputs for later
	I2CCON = 0;									// clear
	I2CBRG = I2C2_BRGVAL;						// config baud rate
	I2CCONbits.SCLREL = 1;
	I2CCONbits.DISSLW = 1 ;						// config I2C
	I2CTRN = 0, I2CRCV = 0;						// make sure clear

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

int mrindex ;  // index into the read write buffer 
int magMessage = 0 ; // message type

int I2messages = 0 ;

void rxMagnetometer(void)  // service the magnetometer
{
	int magregIndex ;
	if (oLED2 == LED_OFF)
		oLED2 = LED_ON;
	else oLED2 = LED_OFF;
#if ( MAG_YAW_DRIFT == 1 )
	I2messages++ ;
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
		I2ERROR = I2CSTAT ; 		// record the error for diagnostics
		I2CCONbits.I2CEN = 0; 		// turn off the I2C
		MI2CIF = 0;					// clear the I2C master interrupt
		MI2CIE = 0; 				// disable the interrupt
		I2C_SDA = 0, I2C_SCL = 0;	// pull SDA and SCL low
		return ;
	}

	mrindex = 0 ;
	{
		magMessage++ ;
		if ( magMessage > 7 )
		{
			magMessage = 7 ;
		}
		switch ( magMessage )
		{ 
		case  1:    // read the magnetometer in case it is still sending data, so as to NACK it
			I2C_state = &I2C_readMagData ;
			MI2CIF = 1 ;
			break ;
		case  2:	// put magnetomter into the power up defaults on a reset
			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
			{
				magreg[magregIndex] = resetMagnetometer[magregIndex] ;
			}
			I2C_state = &I2C_writeMagCommand ;
			MI2CIF = 1 ;
			break ;
		case  3:  // clear out any data that is still there
			I2C_state = &I2C_readMagData ;
			MI2CIF = 1 ;
			break ;
		case  4:  // enable the calibration process
			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
			{
				magreg[magregIndex] = enableMagCalibration[magregIndex] ;
			}
			I2C_state = &I2C_writeMagCommand ;
			MI2CIF = 1 ;
			break ;
		case  5 :  // read the calibration data
			I2C_state = &I2C_readMagData ;
			MI2CIF = 1 ;
			break ;
		case  6 :   // enable normal continuous readings
			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
			{
				magreg[magregIndex] = enableMagRead[magregIndex] ;
			}
			I2C_state = &I2C_writeMagCommand ;
			MI2CIF = 1 ;
			break ;
		case 7 :  // read the magnetometer data
			I2C_state = &I2C_readMagData ;
			MI2CIF = 1 ;
			break ;
		default  :
			I2C_state = &I2C_idle ;
			break ;
		}
	}
#endif
	return ;
}

#if SYS_I2C == 1
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C1Interrupt(void)
#elif SYS_I2C == 2
void __attribute__((__interrupt__,__no_auto_psv__)) _MI2C2Interrupt(void)
#endif
{
    indicate_loading_inter ;
	MI2CIF = 0 ; // clear the interrupt
	if (oLED1 == LED_OFF)
		oLED1 = LED_ON;
	else oLED1 = LED_OFF;
	(* I2C_state) () ; // execute the service routine
	return ;
}

void I2C_writeMagCommand(void)
{
	I2C_state = &I2C_WriteMagData ;
	I2CCONbits.SEN = 1 ;
	return ;
}

void I2C_WriteMagData(void)
{
	I2CTRN = magreg[mrindex++] ;
	if ( mrindex > 4)
	{
		I2C_state = &I2C_stopWriteMagData ;
	}
	return ;
}

void I2C_stopWriteMagData(void)
{
	I2C_state = &I2C_idle ;
	I2CCONbits.PEN = 1 ;
	return ;
}


void I2C_readMagData(void)
{
	if ( I2CCONbits.RCEN == 0 )
	{
		I2C_state = &I2C_startReadMagData ;
		I2CCONbits.SEN = 1 ;
	}
	return ;
}


void I2C_startReadMagData(void)
{
	I2C_state = &I2C_recen ;
	I2CTRN = 0x3D ;
	return ;
}

void I2C_recen(void)
{
	if ( I2CSTATbits.ACKSTAT == 1 )  // magnetometer not responding
	{
		magMessage = 0 ; // start over
		I2CCONbits.PEN = 1; // stop the bus
		I2C_state = &I2C_idle ; 
	}
	else
	{
		I2CCONbits.RCEN = 1 ;
		I2C_state = &I2C_recstore ;
	}
	return ;
}

void I2C_rerecen(void)
{
	I2CCONbits.RCEN = 1 ;
	I2C_state = &I2C_recstore ;
	return ;
}

void I2C_recstore(void)
{
	magreg[mrindex++] = I2CRCV ;
	if ( mrindex > 6 )
	{
		I2CCONbits.ACKDT = 1 ;
		I2C_state = &I2C_stopReadMagData ;
	}
	else
	{
		I2CCONbits.ACKDT = 0 ;
		I2C_state = &I2C_rerecen ;
	}
	I2CCONbits.ACKEN = 1 ;
	return ;
}


void I2C_stopReadMagData(void)
{
	I2CCONbits.PEN = 1;
	I2C_state = &I2C_doneReadMagData ;
	return ;
}

int previousMagFieldRaw[3] = { 0 , 0 , 0 } ;

void I2C_doneReadMagData(void)
{
	int vectorIndex ;
	int magFieldRaw[3] ;
	magFieldRaw[0] = (magreg[0]<<8)+magreg[1] ; 
	magFieldRaw[1] = (magreg[2]<<8)+magreg[3] ; 
	magFieldRaw[2] = (magreg[4]<<8)+magreg[5] ;

	// check to see if Magnetometer is stuck in the single reading mode:
	if ( (magMessage == 7) && ( magFieldRaw[0] == previousMagFieldRaw[0] )
		&& ( magFieldRaw[1] == previousMagFieldRaw[1] )
		&& ( magFieldRaw[2] == previousMagFieldRaw[2] ) )
	{
		I2C_state = &I2C_idle ;
		magMessage = 0 ;
	}
	previousMagFieldRaw[0] = magFieldRaw[0] ;
	previousMagFieldRaw[1] = magFieldRaw[1] ;
	previousMagFieldRaw[2] = magFieldRaw[2] ;

	if ( magMessage == 7 )
	{
		udb_magFieldBody[0] = MAG_X_SIGN((__builtin_mulsu((magFieldRaw[MAG_X_AXIS]), magGain[MAG_X_AXIS] ))>>14)-(udb_magOffset[0]>>1) ;
		udb_magFieldBody[1] = MAG_Y_SIGN((__builtin_mulsu((magFieldRaw[MAG_Y_AXIS]), magGain[MAG_Y_AXIS] ))>>14)-(udb_magOffset[1]>>1) ;
		udb_magFieldBody[2] = MAG_Z_SIGN((__builtin_mulsu((magFieldRaw[MAG_Z_AXIS]), magGain[MAG_Z_AXIS] ))>>14)-(udb_magOffset[2]>>1) ;
		I2C_state = &I2C_idle ;
		if ( ( abs(udb_magFieldBody[0]) < MAGNETICMAXIMUM ) &&
			 ( abs(udb_magFieldBody[1]) < MAGNETICMAXIMUM ) &&
			 ( abs(udb_magFieldBody[2]) < MAGNETICMAXIMUM ) )
		{
			//dcm_flags._.mag_drift_req = 1 ;
			udb_magnetometer_callback_data_available();
		}
		else
		{
			magMessage = 0 ; // invalid reading, reset the magnetometer
		}
	}
	else if ( magMessage == 5 )
	{
		for ( vectorIndex = 0 ; vectorIndex < 3 ; vectorIndex++ )
		{
			rawMagCalib[vectorIndex] = magFieldRaw[vectorIndex] ;
			if (  ( magFieldRaw[vectorIndex] > MAGNETICMINIMUM ) && ( magFieldRaw[vectorIndex] < MAGNETICMAXIMUM ) )
			{
				magGain[vectorIndex] = __builtin_divud( ((long) ( 700.0*RMAX)), magFieldRaw[vectorIndex] ) ;
			}
			else
			{
				magGain[vectorIndex] = RMAX ;
				magMessage = 0 ;  // invalid calibration, reset the magnetometer
			}
		}
		I2C_state = &I2C_idle ;
	}
	return ;
}

void I2C_idle(void)
{
	return ;
}

// function triggers reading the mag in response to it raising DRDY
void __attribute__((__interrupt__,__no_auto_psv__)) _INT1Interrupt(void)
{
    indicate_loading_inter ;
	_INT1IF = 0;
	I2C_flags.bMagReady = 1;
	if ( !I2C_flags.bInUse )
		rxMagnetometer();
}

// function triggers reading the ACC in response to it raising INT1
void __attribute__((__interrupt__,__no_auto_psv__)) _INT2Interrupt(void)
{
    indicate_loading_inter ;
	_INT2IF = 0;
	I2C_flags.bAccReady = 1;
	if ( !I2C_flags.bInUse )
		rxMagnetometer();
}
#endif
