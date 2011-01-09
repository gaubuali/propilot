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

const I2C_Action magRead[] = {  
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3d}, 		// start command with address
	{.F.uCmd = RX_ACK, .F.uCount = 5}, 			// receive 8 bytes,
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, copy + inc + call
			.F.uCount = 6, .F.uResult = CCPY,
			.F.uACK = 1, .F.uBuf = 1}
 };

//const unsigned char enableMagCalibration[] = { 0x3C , 0x00 , 0x11 , 0x20 , 0x01 } ;
const I2C_Action magCalP[] = { // Plus bias calibration
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c},			// start command with address
	{.F.uCmd = TX, .F.uCount = 4 - 1},			// send 4 bytes,
		{.uChar[0] = 0, .uChar[1] = 0x11}, 		// first byte address then 10Hz & +bias 
		{.uChar[0] = 0x20, .uChar[1] = 0x01},	// then +- 1Ga range then 1 convert mode
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, copy + inc + call
			.F.uACK = 1}
 };
const I2C_Action magCalM[] = { // Minus bias calibration
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 4 - 1},			// send 4 bytes,
		{.uChar[0] = 0, .uChar[1] = 0x12},		// first byte address then 10Hz & -bias
		{.uChar[0] = 0x20, .uChar[1] = 0x01},	// then +- 1Ga range then 1 convert mode
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED, .F.uCount = 6, .F.uResult = CCPY}	// finished, copy
 };

//const unsigned char resetMagnetometer[]    = { 0x3C , 0x00 , 0x10 , 0x20 , 0x02 } ;
const I2C_Action magReset[] = {
	{.uChar[0] = 0}, 	// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 4 - 1},			// send 4 bytes,
		{.uChar[0] = 0, .uChar[1] = 0x10},		// first byte address then 10Hz & no bias 
		{.uChar[0] = 0x20, .uChar[1] = 0x02},	// then +- 1Ga range then idle mode
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished
			.F.uACK = 1}						// inc
 };

//const unsigned char enableMagRead[] =        { 0x3C , 0x00 , 0x10 , 0x20 , 0x00 } ;
const I2C_Action magCfg[] = {
	{.uChar[0] = 0}, 	// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 4 - 1},			// send 4 bytes,
		{.uChar[0] = 0, .uChar[1] = 0x10}, 			// first byte address then 10Hz & no bias 
//		{.uChar[0] = 0x20, .uChar[1] = 0x14},			// then +- 1Ga range then 50Hz continious
		{.uChar[0] = 0x20, .uChar[1] = 0x00},			// then +- 1Ga range then 5Hz continious
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished
			.F.uACK = 1}						// inc
};


int udb_magFieldBody[3] ;  // magnetic field in the body frame of reference 
int udb_magOffset[3] = { 0 , 0 , 0 } ;  // magnetic offset in the body frame of reference
int magGain[3] = { RMAX , RMAX , RMAX } ; // magnetometer calibration gains
int rawMagCalib[3] = { 0 , 0 , 0 } ;
unsigned char magreg[6] ;  // magnetometer read-write buffer

int mrindex ;  // index into the read write buffer 
// int CD[magCDindex].iResult = 0 ; // message sequence

int I2messages = 0 ;
int I2_Done = 0;

#define SETUP_I2C_MSG( x ) I2C_flags.bInUse = 1;							\
			CC = CD[magCDindex];											\
			I2_Done = ((sizeof x)>>1) - 1;									\
			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )	\
				uI2C_Commands[magregIndex] = x[magregIndex]

void rxMagnetometer(void)  // service the magnetometer
{
	int magregIndex ;
	if (oLED1 == LED_OFF)
		oLED1 = LED_ON;
	else oLED1 = LED_OFF;

#if ( MAG_YAW_DRIFT == 1 )
	if ( CD[magCDindex].Ident != magCDindex )			// do one time init of structure
	{
		CD[magCDindex].Ident = magCDindex;
		CD[magCDindex].iResult = 1;						// start it up
		CD[magCDindex].pcResult = &magreg[0];			// set destination
		I2C_call_back[magCDindex] = &doneReadMagData;	// set call back
	}
	I2messages++ ;
	mrindex = 0 ;

	if ( CD[magCDindex].I2CERROR || (CD[magCDindex].I2C_Index == I2_Done) || (I2C_Timeout == 0) )
	{
		if ( CD[magCDindex].iResult >= 8 )
			CD[magCDindex].iResult = 7 ;
		else ;
		switch ( CD[magCDindex].iResult )
		{ 
		case  1:    // read the magnetometer in case it is still sending data, so as to NACK it
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
//			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )
//				uI2C_Commands[magregIndex] = magRead[magregIndex];
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magRead );
				I2C_Start( 0 );
			}
			break ;
		case  2:	// put magnetomter into the power up defaults on a reset
//			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
//			{
//				magreg[magregIndex] = resetMagnetometer[magregIndex] ;
//			}
//			I2C_state = &I2C_writeMagCommand ;
//			_MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magReset );
				I2C_Start( 0 );
//				CD[magCDindex].iResult++ ;
			}
			break ;
		case  3:  // clear out any data that is still there
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magRead );
				I2C_Start( 0 );
			}
			break ;
		case  4:  // enable the calibration process
//			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
//			{
//				magreg[magregIndex] = enableMagCalibration[magregIndex] ;
//			}
//			I2C_state = &I2C_writeMagCommand ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magCalP );
				I2C_Start( 0 );
//				CD[magCDindex].iResult++;
			}
			break ;
		case  5 :  // read the calibration data
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magRead );
				I2C_Start( 0 );
			}
			break ;
		case  6 :   // enable normal continuous readings
//			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
//			{
//				magreg[magregIndex] = enableMagRead[magregIndex] ;
//			}
//			I2C_state = &I2C_writeMagCommand ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magCfg );
				I2C_Start( 0 );
			}
			break ;
		case 7 :  // read the magnetometer data
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_MSG( magRead );
				I2C_Start( 0 );
			}
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

void doneReadMagData(void)
{
	int vectorIndex ;
	int magFieldRaw[3] ;
	magFieldRaw[0] = (magreg[0]<<8)+magreg[1] ; 
	magFieldRaw[1] = (magreg[2]<<8)+magreg[3] ; 
	magFieldRaw[2] = (magreg[4]<<8)+magreg[5] ;

	// check to see if Magnetometer is stuck in the single reading mode:
	if ( (CD[magCDindex].iResult >= 7) && ( magFieldRaw[0] == previousMagFieldRaw[0] )
		&& ( magFieldRaw[1] == previousMagFieldRaw[1] )
		&& ( magFieldRaw[2] == previousMagFieldRaw[2] ) )
	{
//		I2C_state = &I2C_idle ;
		CD[magCDindex].iResult = 1 ;
	}
	previousMagFieldRaw[0] = magFieldRaw[0] ;
	previousMagFieldRaw[1] = magFieldRaw[1] ;
	previousMagFieldRaw[2] = magFieldRaw[2] ;

	if ( CD[magCDindex].iResult == 8 )	// was 7, read auto increments this
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
			CD[magCDindex].iResult = 1 ; // invalid reading, reset the magnetometer
		}
	}
	else if ( CD[magCDindex].iResult == 6 ) // was 5, read auto increments this
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
				CD[magCDindex].iResult = 1 ;  // invalid calibration, reset the magnetometer
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
