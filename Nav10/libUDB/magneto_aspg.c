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

unsigned char magreg[6] ;  // magnetometer read-write buffer

const I2C_Action magRead[8] = {  
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c},		// start command with address
	{.F.uCmd = TX, .F.uCount = 1 - 1},			// send 1 bytes,
		{.uChar[0] = 3, .uChar[1] = 0}, 		// first byte address
	{.F.uCmd = RESTART, .F.uCount = 0x3d}, 		// start command with address
	{.F.uCmd = RX_ACK, .F.uCount = 6 - 1}, 		// receive 6 bytes,
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, copy + inc + call
			.F.uCount = sizeof(magreg), 
			.F.uResult = CCPY, .F.uACK = 1, .F.uBuf = 1}
 };

//const unsigned char enableMagCalibration[] = { 0x3C , 0x00 , 0x11 , 0x20 , 0x01 } ;
const I2C_Action magCalP[] = { // Plus bias calibration
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c},		// start command with address
	{.F.uCmd = TX, .F.uCount = 4 - 1},			// send 4 bytes,
		{.uChar[0] = 0, .uChar[1] = 0x11}, 		// first byte address then 10Hz & +bias 
		{.uChar[0] = 0x20, .uChar[1] = 0x01},	// then +- 1Ga range then 1 convert mode
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, inc
			.F.uACK = 1}
 };
const I2C_Action magCalM[] = { // Minus bias calibration
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0x3c}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 4 - 1},			// send 4 bytes,
		{.uChar[0] = 0, .uChar[1] = 0x12},		// first byte address then 10Hz & -bias
		{.uChar[0] = 0x20, .uChar[1] = 0x01},	// then +- 1Ga range then 1 convert mode
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, inc
			.F.uACK = 1}
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
		{.uChar[0] = 0, .uChar[1] = 0x18},			// first byte address then 50Hz & no bias
		{.uChar[0] = 0x20, .uChar[1] = 0x00},		// then +- 1Ga range then continious
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished
			.F.uACK = 1}						// inc
};


int udb_magFieldBody[3] ;  // magnetic field in the body frame of reference 
int udb_magFieldBodyInput[3] ;  // magnetic field in the body frame of reference 
int udb_magOffset[3] = { 0 , 0 , 0 } ;  // magnetic offset in the body frame of reference
int magGain[3] = { RMAX , RMAX , RMAX } ; // magnetometer calibration gains
int rawMagCalib[3] = { 0 , 0 , 0 } ;

// int CD[magCDindex].iResult = 0 ; // message sequence

int I2_Done = 0;
int magConfigAttempts = 0;		// going to limit this in case there is a problem

// the + 3 at the end of this is to leave space for the on error bus stop + finished
#define magReadStart ((sizeof uI2C_Commands)/2) - (((sizeof magRead)/2) + 3)

#define SETUP_I2C_MSG( x ) I2C_flags.bInUse = 1;							\
			CC = CD[magCDindex];											\
			I2_Done = ((sizeof x)>>1) - 1;									\
			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )	\
				uI2C_Commands[magregIndex] = x[magregIndex]

void __attribute__((__no_auto_psv__)) magSetupRead( void )	// setup a device read
{
//	int magregIndex ;
//	interrupt_save_extended_state ;

	I2C_flags.bInUse = 1;
	I2C_flags.bReadMag = 1;					// mark as in progress
	I2C_flags.bMagReady = 0;				// mark as started
//	SETUP_I2C_MSG( magRead );
	CC = CD[magCDindex];
	I2C_Timeout = 3;
	CC.I2C_Subcode = NOTHING, CC.I2C_Tail = 0, CC.I2C_Head = 0;		// reset everything
	CC.I2CERROR = CC.I2CERROR_CON = CC.I2CERROR_STAT = NOTHING;		// store
	CC.I2C_Index = magReadStart;
//	CC.I2C_Index -= ((sizeof magRead)>>1) - 1;;
//	CC.I2C_Index -= 3;

//	interrupt_restore_extended_state ;
}

void rxMagnetometer(void)  // service the magnetometer
{
	int magregIndex ;
//	if (oLED1 == LED_OFF)
//		oLED1 = LED_ON;
//	else oLED1 = LED_OFF;

#if ( MAG_YAW_DRIFT == 1 )
	if ( CD[magCDindex].Ident != magCDindex )			// do one time init of structure
	{
		CD[magCDindex].Ident = magCDindex;
		CD[magCDindex].iResult = MAG_DREAD1;			// start it up
		CD[magCDindex].pcResult = &magreg[0];			// set destination
		I2C_call_back[magCDindex] = &doneReadMagData;	// set call back
		CD[magCDindex].I2C_Subcode = FINISHED;
		I2_Done = ((sizeof magRead)>>1) - 1;			// pre-copy most used
		for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )
			uI2C_Commands[magregIndex+magReadStart] = magRead[magregIndex];
	}

	if ( (CD[magCDindex].I2C_Subcode == FINISHED) || CD[magCDindex].I2CERROR || (CD[magCDindex].I2C_Index == I2_Done) || (I2C_Timeout == 0) )
	{
		if ( CD[magCDindex].iResult >= MAG_NORMAL )
			CD[magCDindex].iResult = MAG_NORMAL ;
		else ;
		switch ( CD[magCDindex].iResult )
		{
		case MAG_WAIT:	// not started yet
		break;
		case  MAG_DREAD1:    // read the magnetometer in case it is still sending data, so as to NACK it
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
//			for ( magregIndex = 0 ; magregIndex <= I2_Done; magregIndex++ )
//				uI2C_Commands[magregIndex] = magRead[magregIndex];
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				magSetupRead();			// do a read of device
				I2C_Start( -1 );
			}
		break ;
		case  MAG_RESET:	// put magnetomter into the power up defaults on a reset
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
			}
		break ;
		case  MAG_DREAD2:	// clear out any data that is still there
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				magSetupRead();			// do a read of device
				I2C_Start( -1 );
			}
		break ;
		case  MAG_DELAY1:	// delay one call cycle
			CD[magCDindex].iResult++ ;
		break ;
		case  MAG_CAL:		// send calibration command
//			for ( magregIndex = 0 ; magregIndex < 5 ; magregIndex++ )
//			{
//				magreg[magregIndex] = enableMagCalibration[magregIndex] ;
//			}
//			I2C_state = &I2C_writeMagCommand ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				if ( magConfigAttempts < 10 )	// only going to try 10 times
				{
					if ( magConfigAttempts & 1 )	// alternate plus and minus strap
					{	SETUP_I2C_MSG( magCalM );
					} else { SETUP_I2C_MSG( magCalP ); };
					I2C_Start( 0 );
				} else {
					magSetupRead();			// do a read of device
					I2C_Start( -1 );
				}
				magConfigAttempts++;
			}
		break ;
		case  MAG_CAL_DOREAD:  // read the calibration data
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				magSetupRead();			// do a read of device
				I2C_Start( -1 );
			}
		break ;
		case MAG_CAL_PROCESS:	// actually handled in doneReadMagData
		break ;
		case MAG_SEND_CFG:			// send command for normal continuous readings
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
//				MAG_INTe = 1;			// int enabled, no longer need this routine
			}
		break ;
		case MAG_NORMAL:	// read the magnetometer data
		case MAG_NORMAL+1:	// read the magnetometer data
//			I2C_state = &I2C_readMagData ;
//			MI2CIF = 1 ;
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				magSetupRead();			// do a read of device
				I2C_Start( -1 );
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
int MagFieldFilter[3] = { 0 , 0 , 0 } ;
int magSameReadings = 0;
void doneReadMagData(void)
{
	int vectorIndex ;
	int magFieldRaw[3] ;
	magFieldRaw[0] = (magreg[0]<<8)+magreg[1] ; 
	magFieldRaw[1] = (magreg[2]<<8)+magreg[3] ; 
	magFieldRaw[2] = (magreg[4]<<8)+magreg[5] ;

	switch ( CD[magCDindex].iResult )	{
	case MAG_NORMAL:
	case MAG_NORMAL+1:
	case MAG_NORMAL+2:
		CD[magCDindex].iResult = MAG_NORMAL;
		// check to see if Magnetometer is stuck in the single reading mode:
		if (   ( magFieldRaw[0] == previousMagFieldRaw[0] )
			&& ( magFieldRaw[1] == previousMagFieldRaw[1] )
			&& ( magFieldRaw[2] == previousMagFieldRaw[2] ) )
		{
	//		I2C_state = &I2C_idle ;
			if ( magSameReadings++ > 4)			// make sure its actually stuck
				CD[magCDindex].iResult = MAG_DREAD1 ;
		} else magSameReadings = 0;
		I2C_flags.bReadMag = 0;					// mark as done
		MagFieldFilter[0] = (MagFieldFilter[0] - (MagFieldFilter[0] / 8)) + (magFieldRaw[0] / 8);	// super simple filter
		MagFieldFilter[1] = (MagFieldFilter[1] - (MagFieldFilter[1] / 8)) + (magFieldRaw[1] / 8);	// super simple filter
		MagFieldFilter[2] = (MagFieldFilter[2] - (MagFieldFilter[2] / 8)) + (magFieldRaw[2] / 8);	// super simple filter

		previousMagFieldRaw[0] = magFieldRaw[0] ;
		previousMagFieldRaw[1] = magFieldRaw[1] ;
		previousMagFieldRaw[2] = magFieldRaw[2] ;

		udb_magFieldBody[0] = MAG_X_SIGN((__builtin_mulsu((magFieldRaw[MAG_X_AXIS]), magGain[MAG_X_AXIS] ))>>14)-(udb_magOffset[0]>>1) ;
		udb_magFieldBody[1] = MAG_Y_SIGN((__builtin_mulsu((magFieldRaw[MAG_Y_AXIS]), magGain[MAG_Y_AXIS] ))>>14)-(udb_magOffset[1]>>1) ;
		udb_magFieldBody[2] = MAG_Z_SIGN((__builtin_mulsu((magFieldRaw[MAG_Z_AXIS]), magGain[MAG_Z_AXIS] ))>>14)-(udb_magOffset[2]>>1) ;

		AD1_Raw[xmag] = FLT_Value[mag_x] = udb_magFieldBody[0];
		AD1_Raw[ymag] = FLT_Value[mag_y] = udb_magFieldBody[1];
		AD1_Raw[zmag] = FLT_Value[mag_z] = udb_magFieldBody[2];
//		I2C_state = &I2C_idle ;
		if ( ( abs(previousMagFieldRaw[0]) < MAGNETICMAXIMUM ) &&
			 ( abs(previousMagFieldRaw[1]) < MAGNETICMAXIMUM ) &&
			 ( abs(previousMagFieldRaw[2]) < MAGNETICMAXIMUM ) )
		{
			//dcm_flags._.mag_drift_req = 1 ;
			udb_magnetometer_callback_data_available();
		}
		else
		{
			CD[magCDindex].iResult = MAG_DREAD1 ;	// invalid reading, reset the magnetometer
			MAG_INTe = 0;							// int disabled
		}
	break;
	case MAG_CAL_PROCESS:	// sure we have cal data
		for ( vectorIndex = 0 ; vectorIndex < 3 ; vectorIndex++ )
		{
			rawMagCalib[vectorIndex] = magFieldRaw[vectorIndex] ;
			if (  ( magFieldRaw[vectorIndex] > MAGNETICMINIMUM ) && ( magFieldRaw[vectorIndex] < MAGNETICMAXIMUM ) )
			{
				magGain[vectorIndex] = __builtin_divud( ((long) ( 700.0*RMAX)), magFieldRaw[vectorIndex] ) ;
			}
			else
			{
				magGain[vectorIndex] = RMAX;
				CD[magCDindex].iResult = MAG_DREAD1;	// invalid reading, reset the magnetometer
//				MAG_INTe = 0;							// int disabled
			}
		}
		CD[magCDindex].iResult++;							// good cal so next step
	break;
	}

	return ;
}

// function triggers reading the mag in response to it raising DRDY
// FIX: DRDY does not work from chip
void __attribute__((__interrupt__,__no_auto_psv__)) _INT1Interrupt(void)
{
    indicate_loading_inter ;
	MAG_INTe = 0;
//	MAG_INTpo = ~iMAG_DR1;						// flip polarity each time
//	_INT1IF = 0;
//	MAG_INTe = 1;
	if ( (CD[magCDindex].iResult >= MAG_NORMAL) && iMAG_DR1 )
	{
		if ( I2C_flags.bInUse )					// bus running
			I2C_flags.bMagReady = 1;			// mark it
		else rxMagnetometer();					// start old way
	};
}

unsigned char accreg[8] ;  // accel read-write buffer, 6 bytes data + 2 status

const I2C_Action accRead[] = {  
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0xA6},		// start command with address
	{.F.uCmd = TX, .F.uCount = 1 - 1},			// send 1 bytes,
		{.uChar[0] = 0x32, .uChar[1] = 0}, 		// first byte address
	{.F.uCmd = RESTART, .F.uCount = 0xA7}, 		// start command with address
	{.F.uCmd = RX_ACK, .F.uCount = 8 - 1}, 		// receive 8 bytes,
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, copy + inc + call
			.F.uCount = sizeof(accreg), 
			.F.uResult = CCPY, .F.uACK = 1, .F.uBuf = 1}
 };

const I2C_Action accCal[] = { // self test, doesn't have cal function
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0xA6},		// start command with address
	{.F.uCmd = TX, .F.uCount = 2 - 1},			// send 2 bytes,
		{.uChar[0] = 0x31, .uChar[1] = 0x8e}, 		// first byte address then DATA_FORMAT
														// = 0b10001110 = 0x0e
														// 7   0 = self test off, 
														// 6    0 = SPI 3 or 4 bit - N/A, 
														// 5     0 = int_invert off means active high
														// 4      0 = not used, 
														// 3       1 = full res on, 
														// 2        1 = left (MSB) justify on
														// 1&0       10 = rang +- 8g
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, copy + inc + call
			.F.uACK = 1}
 };

const I2C_Action accReset[] = {	// force reset by changing mode
	{.uChar[0] = 0}, 	// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 15 - 1},			// send 15 bytes,
		{.uChar[0] = 0x1d, .uChar[1] = 0xff}, 		// first byte address then THRESH_TAP = MAX 
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// OFSX, OFSY = 0
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// OFSZ = 0, DUR = 0 (disable)
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// Latest = Window = 0 (disable)
		{.uChar[0] = 0x7f, .uChar[1] = 0x7f},			// THRESH_ACT / INACT = 0x7F (MAX)
		{.uChar[0] = 0x7f, .uChar[1] = 0x00},			// TIME_INACT = 0x7F (MAX)
														// ACT_INACT_CTL = 0, all disable
		{.uChar[0] = 0x7f, .uChar[1] = 0x7f},			// THRESH_FF = TIME_FF = 0x7F (MAX)
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// TAP_AXES = 0 (disable)
	{.F.uCmd = RESTART, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 5 - 1},			// send 5 bytes,
		{.uChar[0] = 0x2c, .uChar[1] = 0x0e}, 			// first byte address then LOW_POWER = 0
														// BW_RATE = 1110 = 1600Hz
		{.uChar[0] = 0x00, .uChar[1] = 0x80},			// POWER_CTL = 0b00000000 = off mode
														// INT_ENABLE = 0b10000000 = DATA_READY
		{.uChar[0] = 0x7f, .uChar[1] = 0x00},			// INT_MAP = 0b01111111 = INT1 = DATA_READY
	{.F.uCmd = RESTART, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 2 - 1},			// send 1 bytes,
		{.uChar[0] = 0x31, .uChar[1] = 0x0e}, 		// first byte address then DATA_FORMAT
														// = 0b00001110 = 0x0e
														// 7   0 = self test off, 
														// 6    0 = SPI 3 or 4 bit - N/A, 
														// 5     0 = int_invert off means active high
														// 4      0 = not used, 
														// 3       1 = full res on, 
														// 2        1 = left (MSB) justify on
														// 1&0       10 = rang +- 8g
	{.F.uCmd = RESTART, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 2 - 1},			// send 1 bytes,
		{.uChar[0] = 0x38, .uChar[1] = 0xbf},		// first byte address then FIFO_CTRL
														// = 0b10111111 = 0x7f
														// 7&6 10 = STREAM mode on
														// 5     1 = trigger = int2
														// 4-0    11111 = samples max
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished
			.F.uACK = 1}						// inc
 };

const I2C_Action accCfg[] = {
	{.uChar[0] = 0}, 	// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 15 - 1},			// send 15 bytes,
		{.uChar[0] = 0x1d, .uChar[1] = 0xff}, 		// first byte address then THRESH_TAP = MAX 
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// OFSX, OFSY = 0
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// OFSZ = 0, DUR = 0 (disable)
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// Latest = Window = 0 (disable)
		{.uChar[0] = 0x7f, .uChar[1] = 0x7f},			// THRESH_ACT / INACT = 0x7F (MAX)
		{.uChar[0] = 0x7f, .uChar[1] = 0x00},			// TIME_INACT = 0x7F (MAX)
														// ACT_INACT_CTL = 0, all disable
		{.uChar[0] = 0x7f, .uChar[1] = 0x7f},			// THRESH_FF = TIME_FF = 0x7F (MAX)
		{.uChar[0] = 0x00, .uChar[1] = 0x00},			// TAP_AXES = 0 (disable)
	{.F.uCmd = RESTART, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 5 - 1},			// send 5 bytes,
		{.uChar[0] = 0x2c, .uChar[1] = 0x0e}, 			// first byte address then LOW_POWER = 0
														// BW_RATE = 1110 = 1600Hz
//		{.uChar[0] = 0x2c, .uChar[1] = 0x0c}, 			// first byte address then LOW_POWER = 0
//														// BW_RATE = 1100 = 400Hz
		{.uChar[0] = 0x08, .uChar[1] = 0x02},			// POWER_CTL = 0b00001000 = normal mode
														// INT_ENABLE = 0b00000010 = Watermark
		{.uChar[0] = 0xfd, .uChar[1] = 0x00},			// INT_MAP = 0b11111101 = INT1 = Watermark
	{.F.uCmd = RESTART, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 2 - 1},			// send 2 bytes,
		{.uChar[0] = 0x31, .uChar[1] = 0x0e}, 		// first byte address then DATA_FORMAT
														// = 0b00001110 = 0x0e
														// 7   0 = self test off, 
														// 6    0 = SPI 3 or 4 bit - N/A, 
														// 5     0 = int_invert off means active high
														// 4      0 = not used, 
														// 3       1 = full res on, 
														// 2        1 = left (MSB) justify on
														// 1&0       10 = rang +- 8g
	{.F.uCmd = RESTART, .F.uCount = 0xA6}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 2 - 1},			// send 2 bytes,
		{.uChar[0] = 0x38, .uChar[1] = 0xa1},		// first byte address then FIFO_CTRL
														// = 0b10100001 = 0xa1
														// 7&6 10 = STREAM mode on
														// 5     1 = trigger = int2
														// 4-0    00001 = 1 sample
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished
			.F.uACK = 1}						// inc
};

// read's call doneMagReadData() & inc, others just increment CD[magCDindex].iResult

int I2_ADone = 0;

#define accReadStart magReadStart - (((sizeof accRead)/2) + 1)

#define SETUP_I2C_AMSG( x ) I2C_flags.bInUse = 1;							\
			CC = CD[accCDindex];											\
			I2_ADone = ((sizeof x)>>1) - 1;									\
			for ( accregIndex = 0 ; accregIndex <= I2_ADone; accregIndex++ )	\
				uI2C_Commands[accregIndex] = x[accregIndex]

void __attribute__((__no_auto_psv__)) accSetupRead( void )	// setup a device read
{
//	int accregIndex ;
//	interrupt_save_extended_state ;

	I2C_flags.bInUse = 1;
	I2C_flags.bReadAcc = 1;					// mark as in progress
	I2C_flags.bAccReady = 0;				// mark as started
//	SETUP_I2C_AMSG( accRead );
	CC = CD[accCDindex];
	I2C_Timeout = 4;
	CC.I2C_Subcode = NOTHING, CC.I2C_Tail = 0, CC.I2C_Head = 0;		// reset everything
	CC.I2CERROR = CC.I2CERROR_CON = CC.I2CERROR_STAT = NOTHING;		// store
	CC.I2C_Index = accReadStart;
//	interrupt_restore_extended_state ;
}

void rxAccel(void)  // service the ACC
{
	int accregIndex ;
	if (oLED1 == LED_OFF)
		oLED1 = LED_ON;
	else oLED1 = LED_OFF;

	if ( CD[accCDindex].Ident != accCDindex )			// do one time init of structure
	{
		CD[accCDindex].Ident = accCDindex;
//		CD[accCDindex].iResult = ACC_DREAD1;			// start it up
		CD[accCDindex].iResult = ACC_SEND_CFG;			// start it up
		CD[accCDindex].pcResult = &accreg[0];			// set destination
		I2C_call_back[accCDindex] = &doneReadAccData;	// set call back
		CD[accCDindex].I2C_Subcode = FINISHED;
		I2_ADone = ((sizeof accRead)>>1) - 1;			// pre-copy most used
		for ( accregIndex = 0 ; accregIndex <= I2_Done; accregIndex++ )
			uI2C_Commands[accregIndex+accReadStart] = accRead[accregIndex];
	}

	if ( (CD[accCDindex].I2C_Subcode == FINISHED) || CD[accCDindex].I2CERROR || (CD[accCDindex].I2C_Index == I2_ADone) || (I2C_Timeout == 0) )
	{
		if ( CD[accCDindex].iResult >= ACC_NORMAL )
			CD[accCDindex].iResult = ACC_NORMAL ;
		else ;
		switch ( CD[accCDindex].iResult )
		{ 
		case ACC_WAIT:
		break;
		case ACC_DREAD1:	// read the accel in case it is still sending data, so as to NACK it
			if ( (I2C_flags.bInUse == 0) )	// not running right now
			{
				accSetupRead();
				I2C_Start( -1 );
			}
			break ;
		case  ACC_RESET:	// put accel into the power up defaults on a reset
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_AMSG( accReset );
				I2C_Start( 0 );
			}
			break ;
		case  ACC_DREAD2:  // clear out any data that is still there
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				accSetupRead();
				I2C_Start( -1 );
			}
		break ;
		case  ACC_CAL:  // enable the self test process
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_AMSG( accCal );
				I2C_Start( 0 );
			}
		break ;
		case  ACC_CAL_DOREAD :  // read the calibration data
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				accSetupRead();
				I2C_Start( -1 );
			}
		break ;
		case  ACC_CAL_PROCESS:	// enable normal continuous readings
		break ;
		case  ACC_SEND_CFG:		// enable normal continuous readings
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				SETUP_I2C_AMSG( accCfg );
				I2C_Start( 0 );
				ACC_INTe = 1;	// int enabled
			}
		break ;
		case ACC_NORMAL:		// read the accel data
		case ACC_NORMAL+1:		// read the accel data
		case ACC_NORMAL+2:		// read the accel data
			if (I2C_flags.bInUse == 0)	// not running right now
			{
				accSetupRead();
				I2C_Start( -1 );
			} else I2C_flags.bReadAcc = 1;		// mark as needing
			break ;
		default  :
		break ;
		}
	}
	return ;
}

int previousAccFieldRaw[3] = { 0 , 0 , 0 } ;
int accSameReadings = 0;

void doneReadAccData(void)
{

//	int vectorIndex ;
	int AccFieldRaw[3] ;
	AccFieldRaw[0] = (accreg[1]<<8)+accreg[0] ;
	AccFieldRaw[1] = (accreg[3]<<8)+accreg[2] ;
	AccFieldRaw[2] = (accreg[5]<<8)+accreg[4] ;

	// check to see if Magnetometer is stuck in the single reading mode:
	if ( (CD[accCDindex].iResult >= 7) && ( AccFieldRaw[0] == previousAccFieldRaw[0] )
		&& ( AccFieldRaw[1] == previousAccFieldRaw[1] )
		&& ( AccFieldRaw[2] == previousAccFieldRaw[2] ) )
	{
		if ( accSameReadings++ > 5)			// make sure its actually stuck
			CD[accCDindex].iResult = ACC_SEND_CFG ;
	} else accSameReadings = 0;
	previousAccFieldRaw[0] = AccFieldRaw[0] ;
	previousAccFieldRaw[1] = AccFieldRaw[1] ;
	previousAccFieldRaw[2] = AccFieldRaw[2] ;

	if ( CD[accCDindex].iResult >= ACC_NORMAL )	// was 7, read auto increments this
	{
		CD[accCDindex].iResult = ACC_NORMAL;
		AD1_Raw[xaccel] = AccFieldRaw[0];
		AD1_Raw[yaccel] = AccFieldRaw[1];
		AD1_Raw[zaccel] = AccFieldRaw[2];
		AD1_Filt[0][accel_x][iI2C_Head] = AD1_Raw[xaccel];	// buffer the results
		AD1_Filt[0][accel_y][iI2C_Head] = AD1_Raw[yaccel];
		AD1_Filt[0][accel_z][iI2C_Head] = AD1_Raw[zaccel];
		if ( ++iI2C_Head > 64 )
			iI2C_Head = 0;
		else ;

		I2C_flags.bReadAcc = 0;					// mark as done

//		udb_magFieldBodyInput[0] = MAG_X_SIGN((__builtin_mulsu((AccFieldRaw[MAG_X_AXIS]), magGain[MAG_X_AXIS] ))>>14)-(udb_magOffset[0]>>1) ;
//		udb_magFieldBodyInput[1] = MAG_Y_SIGN((__builtin_mulsu((AccFieldRaw[MAG_Y_AXIS]), magGain[MAG_Y_AXIS] ))>>14)-(udb_magOffset[1]>>1) ;
//		udb_magFieldBodyInput[2] = MAG_Z_SIGN((__builtin_mulsu((AccFieldRaw[MAG_Z_AXIS]), magGain[MAG_Z_AXIS] ))>>14)-(udb_magOffset[2]>>1) ;
//		udb_magFieldBody[0] = (udb_magFieldBody[0] / 2) + (udb_magFieldBodyInput[0] / 2);	// super simple filter
//		udb_magFieldBody[1] = (udb_magFieldBody[1] / 2) + (udb_magFieldBodyInput[1] / 2);	// super simple filter
//		udb_magFieldBody[2] = (udb_magFieldBody[2] / 2) + (udb_magFieldBodyInput[2] / 2);	// super simple filter
//		I2C_state = &I2C_idle ;
//		if ( ( abs(udb_magFieldBody[0]) < MAGNETICMAXIMUM ) &&
//			 ( abs(udb_magFieldBody[1]) < MAGNETICMAXIMUM ) &&
//			 ( abs(udb_magFieldBody[2]) < MAGNETICMAXIMUM ) )
//		{
//			//dcm_flags._.mag_drift_req = 1 ;
//			udb_magnetometer_callback_data_available();
//		}
//		else
//		{
//			CD[accCDindex].iResult = 1 ; // invalid reading, reset the magnetometer
//		}
	}
	else if ( CD[accCDindex].iResult == ACC_CAL_PROCESS ) // TODO: do self test and check results
	{
//		for ( vectorIndex = 0 ; vectorIndex < 3 ; vectorIndex++ )
//		{
//			rawMagCalib[vectorIndex] = accFieldRaw[vectorIndex] ;
//			if (  ( accFieldRaw[vectorIndex] > MAGNETICMINIMUM ) && ( accFieldRaw[vectorIndex] < MAGNETICMAXIMUM ) )
//			{
//				magGain[vectorIndex] = __builtin_divud( ((long) ( 700.0*RMAX)), accFieldRaw[vectorIndex] ) ;
//			}
//			else
//			{
//				magGain[vectorIndex] = RMAX ;
//				CD[accCDindex].iResult = 1 ;  // invalid calibration, reset the magnetometer
//			}
//		}
//		I2C_state = &I2C_idle ;
	}
	return ;

}


// function triggers reading the ACC in response to it raising its INT1, pic's INT2
void __attribute__((__interrupt__,__no_auto_psv__)) _INT2Interrupt(void)
{
    indicate_loading_inter ;
	_INT2IF = 0;
	I2C_flags.bAccReady = 1;
	if ( !I2C_flags.bInUse )
		rxAccel();
}
#endif
