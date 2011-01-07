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

// I2C pseudo code drivers - see I2C_aspg.c for docs

//const unsigned char enableMagRead[] =        { 0x3C , 0x00 , 0x10 , 0x20 , 0x00 } ;
const unsigned char enableMagRead[] =        { 0xA0 , 0x00 ,  'P' , 'F' , 'G' } ;	// changed to 50Hz output
const unsigned char enableMagCalibration[] = { 0x3C , 0x00 , 0x11 , 0x20 , 0x01 } ;
const unsigned char resetMagnetometer[] = { 0xA0 , 0x00 , 'P' , 'F' , 'G' } ; // write to address 000
//const unsigned char resetMagnetometer[]    = { 0x3C , 0x00 , 0x10 , 0x20 , 0x02 } ;

// nothing, start, slave, tx(8), address(2 = 0) + "ASPG V0.0\0", stop, finished
const I2C_Action writeEEtest[] = {  {{.uChar[0] = 0}}, 	// empty to make Index step
	{{.tagF = {.uCmd = START, .uCount = 0xAE}}}, 		// start command with address
	{{.tagF = {.uCmd = TX, .uCount = 12 - 1}}},			// send 12 bytes, 
	{{.uChar[0] = 0, .uChar[1] = 0}}, 					// first 2 bytes are address
		{{.uChar[0] = 'A', .uChar[1] = 'S'}}, 			// next 2 are "AS"
		{{.uChar[0] = 'P', .uChar[1] = 'G'}}, 			// next 2 are "PF"
		{{.uChar[0] = ' ', .uChar[1] = 'V'}}, 			// next 2 are "G "
		{{.uChar[0] = '0', .uChar[1] = '.'}}, 			// next 2 are "G "
		{{.uChar[0] = '0', .uChar[1] = 0}}, 			// next 2 are "G "
	{{.tagF = {.uCmd = STOP}}},							// bus stop
	{{.tagF = {.uCmd = FINISHED}}}						// finished
};
const I2C_Action readEEtest[] = {  {{.uChar[0] = 0}}, 	// empty to make Index step
	{{.tagF = {.uCmd = START, .uCount = 0xAE}}}, 		// start command with address
	{{.tagF = {.uCmd = TX, .uCount = 1}}}, 				// send 2 bytes, 
	{{.uChar[0] = 0x0, .uChar[1] = 0x0}}, 				// 2 bytes are address (MSB first)
	{{.tagF = {.uCmd = RESTART, .uCount = 0xAF}}}, 		// start command with address
	{{.tagF = {.uCmd = RX_ACK, .uCount = 10 - 1}}},		// receive 10 bytes, 
	{{.tagF = {.uCmd = STOP}}},							// bus stop
	{{.tagF = {.uCmd = FINISHED}}}						// finished
};
const I2C_Action magRead[] = {  {{.uChar[0] = 0}}, 	// empty to make Index step
	{{.tagF = {.uCmd = START, .uCount = 0x3d}}}, 		// start command with address
	{{.tagF = {.uCmd = RX_ACK, .uCount = 5}}}, 			// receive 8 bytes, 
	{{.tagF = {.uCmd = STOP}}},							// bus stop
	{{.tagF = {.uCmd = FINISHED}}}						// finished
 };


int EE_Write_Timer = 0;
int udb_magFieldBody[3] ;  // magnetic field in the body frame of reference 
int udb_magOffset[3] = { 0 , 0 , 0 } ;  // magnetic offset in the body frame of reference
int magGain[3] = { RMAX , RMAX , RMAX } ; // magnetometer calibration gains
int rawMagCalib[3] = { 0 , 0 , 0 } ;
unsigned char magreg[6] ;  // magnetometer read-write buffer

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

int mrindex ;  // index into the read write buffer 
int magMessage = 0 ; // message type

int I2messages = 0 ;

int I2_Done = 0;

void rxMagnetometer(void)  // service the magnetometer
{
	int magregIndex ;
	if (oLED1 == LED_OFF)
		oLED1 = LED_ON;
	else oLED1 = LED_OFF;
// return;
// all needs mass changes to use pseudo code driver
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
	mrindex = 0 ;
	if ( magMessage == 0 )
		magMessage = 1 ;

	if ( I2CERROR || (I2C_Index == I2_Done) || (I2C_Timeout == 0) )
	{
		if ( magMessage > 7 )
		{
			magMessage = 7 ;
		}
		switch ( magMessage )
		{ 
		case  1:    // read the magnetometer in case it is still sending data, so as to NACK it
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			I2_Done = ((sizeof writeEEtest)>>1) - 1;	// implied size of 2 bytes each
			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )
				uI2C_Commands[magregIndex] = writeEEtest[magregIndex];
//			I2_Done = ((sizeof magRead)>>1) - 1;	// implied size of 2 bytes each
//			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )
//				uI2C_Commands[magregIndex] = magRead[magregIndex];
			I2C_Start( 0 );
			EE_Write_Timer = 126; // wait for this
			magMessage++ ;
			break ;
		case  2:	// put magnetomter into the power up defaults on a reset
			I2_Done = ((sizeof readEEtest)>>1) - 1;	// implied size of 2 bytes each
			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )
				uI2C_Commands[magregIndex] = readEEtest[magregIndex] ;

			I2C_Start( 0 );
			magMessage = 1;
//			EE_Write_Timer = 6; // wait for this
//			magMessage++ ;
//			I2C_state = &I2C_writeMagCommand ;
//			MI2CIF = 1 ;
			break ;
		case  3:  // clear out any data that is still there
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			break ;
		case  4:  // enable the calibration process
			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
			{
				magreg[magregIndex] = enableMagCalibration[magregIndex] ;
			}
//			I2C_state = &I2C_writeMagCommand ;
//			MI2CIF = 1 ;
			break ;
		case  5 :  // read the calibration data
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			break ;
		case  6 :   // enable normal continuous readings
			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
			{
				magreg[magregIndex] = enableMagRead[magregIndex] ;
			}
//			I2C_state = &I2C_writeMagCommand ;
//			MI2CIF = 1 ;
			break ;
		case 7 :  // read the magnetometer data
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			break ;
		default  :
//			I2C_state = &I2C_idle ;
			break ;
		}
	}
#endif
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
//		I2C_state = &I2C_idle ;
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
//		I2C_state = &I2C_idle ;
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
//		I2C_state = &I2C_idle ;
	}
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
