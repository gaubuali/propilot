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
#define _ADDED_C_LIB 1 // Needed to get vsnprintf()
#include <stdio.h>
#include <stdarg.h>

#if (BOARD_TYPE == ASPG_BOARD)

// note this is a write address, add 1 for read
#define EEDEV 0xAE
#if !defined(EESIZE) || ((EESIZE != 256) && (EESIZE != 512))
#waring EESIZE not defined or not supported.
#elif EESIZE == 256
#define EEPAGE 64
#elif EESIZE == 512
#define EEPAGE 128
#else
#waring EESIZE not defined or not supported.
#endif
#define EEMASK (EEPAGE-1)

// I2C pseudo code drivers - see I2C_aspg.c for docs
// copy this to I2C_Commands, set the 6th byte to number of bytes to write (max 128 for 64k devices,
// plus 2 for the address) then put the address in the first two bytes of I2C_buffer followed by data
const I2C_Action writeEE[] = {
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = EEDEV}, 		// start command with address
	{.F.uCmd = TX, .F.uBuf = 1, .F.uCount = 0},	// send x bytes, .uCount set in function call
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED}						// finished
};

// copy this to I2C_Commands, set the 9th byte to number of bytes to read (max 256), put 2 address
// in the first two bytes of I2C_buffer, data overwrites these two as read happens
const I2C_Action readEE[] = {
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = EEDEV}, 		// start command with address
	{.F.uCmd = TX, .F.uBuf = 1, .F.uCount = 2-1},	// send 2 bytes, the address
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = START, .F.uCount = EEDEV+1}, 	// start command with address
	{.F.uCmd = RX_ACK, .F.uCount = 1 - 1},		// receive x bytes, .uCount set in function call
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED,						// finished, copy + no call - if we set call here
			.F.uCount = 0,						// nothing else will get serviced so we wait and
			.F.uResult = HCPY, .F.uACK = 0, .F.uBuf = 0} // gets called anyway if nothing else to do
};

#define WReeCDindex 3
#define REeeCDindex 4
int EE_Active NEAR_BUF = 0;
int EE_Write_Timer NEAR_BUF = 0;
unsigned int EE_Address NEAR_BUF = 0;			// keeps track of current address in EE
unsigned int EE_End NEAR_BUF = 0;
unsigned char *pData NEAR_BUF = 0;
char cEEpresent NEAR_BUF = 0;

// These variables along with the linker script bracket the persistant variables - these are saved to and restored
// from the EE on startup. In order to detect changes that would invalidate the saved variables the first 3 words
// have to match in the EE and runtime image, and the checksum must be valid, before this "image" is restored to
// memory. 
//
//  .Parameters 0x850 :
//  {
//    *(ParametersStart);
//    *(Parameters);
//    *(ParametersEnd);
//  } > data
//
// This section of the linker script forces the start address and order to allow this to work by placing all
// variables the a section("Parameters") attribute to be placed between these variables. The start address is
// set to 0x850 intentially to allow for the space used by the debugger. Unfortunatly this is not foolproof but
// there is simply no tools to ensure the exact same variables are placed in the same order beyond the 
// presumtion the linker will allocate in a predictable manner. If there is a question change the first number
// and that will force a re-save of all variables in the new order with the unfortunate side affect of replacing
// all the values with the rom image defaults.

WORD ParameterEnd __attribute__ ((near, section("ParametersEnd"))) = 0;
WORD ParameterStart[4] __attribute__ ((near, section("ParametersStart"), address(0x850))) = {
	0x0001,		// version number - eeprom must match or no read - change this forces a store
	(WORD)&ParameterStart[0],	// size must match or no read
	(WORD)&ParameterEnd,		// calculate size
	0x0			// simple add checksum calculated and stored in EE, checks ee data ok
};

void doneEE( void )
{
	int	iIdx, iCnt;
	if ( EE_Write_Timer )
	{
		I2C_flags.bInUse = 0;						// release lock, part is busy
		return;
	} else
	if ( EE_Active > 0)	// read mode
	{
		if ( EE_Address >= EE_End )	// finished ?
		{	EE_Active = 0, I2C_flags.bInUse = 0;	// release lock, part is busy;
		} else {
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
			udb_serial_send_string( (unsigned char *)"." );
#endif
			EE_Active++;							// can watch progress till done
			iCnt = ((sizeof readEE)>>1) - 1;
			for ( iIdx = 0 ; iIdx <= iCnt; iIdx++ )
				uI2C_Commands[iIdx] = readEE[iIdx];
			iCnt = EE_End - EE_Address;
			if (iCnt > EEPAGE)
				iCnt = EEPAGE;							// this sets the max it will read each time
			uI2C_Commands[5].F.uCount = (unsigned int)(iCnt-1) & 0xff; // technically = 0 for a 256 byte read
			CD[REeeCDindex].pcResult = pData;		// driver will copy the bytes here
			I2C_buffer[1] = EE_Address & 0xff;
			I2C_buffer[0] = (EE_Address>>8) & 0xff;	// address within ee prom
			pData += iCnt, EE_Address += iCnt;		// done this far
			CC = CD[REeeCDindex];					// do it
			I2C_Start( 3+(iCnt/44) );				// large xfer's actually take time
		}
	} else
	if ( EE_Active < 0)	// write mode
	{
		if ( EE_Address >= EE_End )	// finished ?
		{	EE_Active = 0, I2C_flags.bInUse = 0;	// release lock, part is busy;
		} else {
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
			udb_serial_send_string( (unsigned char *)"." );
#endif
			EE_Active--;							// can watch progress till done
			iCnt = ((sizeof writeEE)>>1) - 1;
			for ( iIdx = 0 ; iIdx <= iCnt; iIdx++ )
				uI2C_Commands[iIdx] = writeEE[iIdx];
			iCnt = EE_End - EE_Address;
			if ( iCnt > EEPAGE) iCnt = EEPAGE;		// this sets the max it will write each time
			if ( ((iCnt-1) + (EE_Address&EEMASK)) > EEMASK ) // check if it writes over a page boundry
				iCnt = EEPAGE - (EE_Address & EEMASK); // reduce to page boundry
			uI2C_Commands[2].F.uCount = (unsigned int)(iCnt+1) & 0xff; // 2 for address - 1 for 0 base sends 1
			for ( iIdx = 0 ; iIdx < iCnt; iIdx++ )
				I2C_buffer[iIdx+2] = pData[iIdx];
			I2C_buffer[1] = EE_Address & 0xff;
			I2C_buffer[0] = (EE_Address>>8) & 0xff;	// address within ee prom
			pData += iCnt, EE_Address += iCnt;		// done this far
			CC = CD[WReeCDindex];					// do it
			EE_Write_Timer = 6;						// has to wait for this to count down to 0
			I2C_Start( 3+(iCnt/44) );				// large xfer's actually take time
		}
	} else I2C_flags.bInUse = 0;				// release lock
}


int EE_Write( unsigned int uiLen, unsigned int uiAddress, unsigned char *vpData  )
{

	if ( CD[WReeCDindex].Ident != WReeCDindex )			// do one time init of structure
	{
		CD[WReeCDindex].Ident = WReeCDindex;
		CD[WReeCDindex].iResult = 0;					// starting
		CD[WReeCDindex].pcResult = &I2C_buffer[0];		// set destination
		I2C_call_back[WReeCDindex] = &doneEE;			// set call back
		CD[WReeCDindex].I2C_Subcode = FINISHED;
	}

	if ( EE_Active || EE_Write_Timer || (uiLen > 4096) || (vpData > (unsigned char *)0x7800))	// sanity checks
		return EE_Active;								// pass back active code
//		return CD[WReeCDindex].iResult;					// pass back completion code
	else {												// setup actual write
		EE_Address = uiAddress;
		EE_End = EE_Address + uiLen;
		pData = vpData;
		EE_Active = -1;									// turn on in write mode
		_DI10();
		if (I2C_flags.bInUse == 0)	// not running right now
		{	I2C_flags.bInUse = 1;						// lock it
			doneEE();									// dummy call to start it
		}
	}
	return EE_Active;
}

int EE_Read( unsigned int uiLen, unsigned int uiAddress, unsigned char *vpData )
{

	if ( CD[REeeCDindex].Ident != REeeCDindex )			// do one time init of structure
	{
		CD[REeeCDindex].Ident = REeeCDindex;
		CD[REeeCDindex].iResult = 0;					// starting
		CD[REeeCDindex].pcResult = &I2C_buffer[0];		// set destination
		I2C_call_back[REeeCDindex] = &doneEE;			// set call back
		CD[REeeCDindex].I2C_Subcode = FINISHED;
	}

	if ( EE_Active || EE_Write_Timer || (uiLen > 4096) || (vpData > (unsigned char *)0x7800))	// sanity checks
		return CD[REeeCDindex].iResult;					// pass back completion code
	else {												// setup actual write
		EE_Address = uiAddress;
		EE_End = EE_Address + uiLen;
		pData = vpData;
		EE_Active = 1;									// turn on in read mode
		_DI10();
		if (I2C_flags.bInUse == 0)	// not running right now
		{	I2C_flags.bInUse = 1;						// lock it
			doneEE();									// dummy call to start it
		}
	}
	return EE_Active;
}

void ReadParameters( void )
{
	WORD wParamSize[2];
	WORD EE_Params[4];			// read here and then compare
	int iCnt, iIdx;
	unsigned char *pvData;

	while (EE_Read( sizeof(EE_Params), EE_PARAMETER_START, (unsigned char *)&EE_Params[0] ) < 1)
		indicate_loading_main;
	wParamSize[0] = ParameterStart[2] - ParameterStart[1];
	while (EE_Active != 0)		// this forces a wait in this function
		indicate_loading_main;
	wParamSize[1] = EE_Params[2] - EE_Params[1];
	if ( (EE_Params[0] != ParameterStart[0]) || (wParamSize[1] != wParamSize[0]) )
		WriteParameters();	// no match so store
	else {
		ParameterStart[3] = 0;
		wParamSize[1] = 0;
		iIdx = 8;				// skip 4 control words in first read of checksum calc
		do {
			iCnt = wParamSize[0] - wParamSize[1];
			if ( iCnt > sizeof(serial_buffer))
				iCnt = sizeof(serial_buffer);
			if ( iCnt > 128)
				iCnt = 128;
			while (EE_Read( iCnt, EE_PARAMETER_START+wParamSize[1], (unsigned char *)&serial_buffer[0] ) < 1)
				indicate_loading_main;
			wParamSize[1] += iCnt;
			while (EE_Active != 0)		// this forces a wait in this function
				indicate_loading_main;
			for ( ; iIdx < iCnt; iIdx++ )
				ParameterStart[3] += serial_buffer[iIdx];
			iIdx = 0;
		} while( wParamSize[0] > wParamSize[1] );
		if ( ParameterStart[3] != EE_Params[3])
			WriteParameters();	// checksum mismatch so store again
		else {
			ParameterStart[3] = 0;
			wParamSize[1] = 0;
//			iIdx = 8;				// skip 4 control words in first read of checksum calc
			pvData = (unsigned char*)&ParameterStart[0];
			do {
				iCnt = wParamSize[0] - wParamSize[1];
				if ( iCnt > sizeof(serial_buffer))
					iCnt = sizeof(serial_buffer);
				if ( iCnt > 128)					// we can actually read more at a time but this is to
					iCnt = 128;						// reduce latency on other I2C bus users
				while (EE_Read( iCnt, EE_PARAMETER_START+wParamSize[1], (unsigned char *)&serial_buffer[0] ) < 1)
					indicate_loading_main;
				wParamSize[1] += iCnt;
				while (EE_Active != 0)		// this forces a wait in this function
					indicate_loading_main;
				for ( iIdx = 0; iIdx < iCnt; iIdx++ )
				{
					_DI10();				// disable interuppts while its overwriting data
					*pvData = serial_buffer[iIdx], pvData++;
				}
			} while( wParamSize[0] > wParamSize[1] );
		}
	}

}

void WriteParameters( void )
{
	int iCnt, iIdx;
	unsigned char *pvData;

	ParameterStart[3] = 0;
	pvData = (unsigned char*)&ParameterStart[0];
	pvData += 8;									// skip over control data
	iCnt = (ParameterStart[2] - ParameterStart[1]) - 8;
	for ( iIdx = 0; iIdx < iCnt; iIdx++ )
		ParameterStart[3] += *pvData, pvData++;
	iCnt = (ParameterStart[2] - ParameterStart[1]);	// write whole thing
	pvData = (unsigned char*)&ParameterStart[0];
	while (EE_Write( iCnt, EE_PARAMETER_START, pvData ) > -1)
		indicate_loading_main;
	while (EE_Active != 0)		// this forces a wait in this function
		indicate_loading_main;
	iIdx = iCnt;
}

int udb_init_EE()
{
	int iReturnCode = 0;

	while (EE_Read( 16, 0, (unsigned char *)&serial_buffer[0] ) < 1)
		indicate_loading_main;
	while (EE_Active != 0)		// this forces a wait in this function
		indicate_loading_main;
	if ( serial_buffer[0] == 'A' && serial_buffer[1] == 'S' && \
		serial_buffer[2] == 'P' && serial_buffer[3] == 'G' )
	{	iReturnCode = 1;		// ee exists and possibly has an image
		ReadParameters();		// so check and read if possible
	} else {
		iReturnCode = sprintf( (char *)&serial_buffer[0], "ASPG V%d.%d", 1, 0 );
		while (EE_Write( iReturnCode+1, 0, (unsigned char *)&serial_buffer[0] ) > -1)
			indicate_loading_main;
		while (EE_Active != 0)		// this forces a wait in this function
			indicate_loading_main;
		serial_buffer[0] = 0;
		while (EE_Read( 16, 0, (unsigned char *)&serial_buffer[0] ) < 1)
			indicate_loading_main;
		while (EE_Active != 0)		// this forces a wait in this function
			indicate_loading_main;
		if ( serial_buffer[0] == 'A' && serial_buffer[1] == 'S' && \
			serial_buffer[2] == 'P' && serial_buffer[3] == 'G' )
		{	iReturnCode = 1;	// ee exists so write out new image
			WriteParameters();
		} else iReturnCode = 0;	// data returned not valid so no ee
	}
	if ( iReturnCode )
		cEEpresent = (EESIZE/256);
	else cEEpresent = 0;
	return iReturnCode;
}
#endif
//// nothing, start, slave, tx(12), address x 2(0) + "ASPG V0.0\0", stop, finished
//const I2C_Action writeEEtest[] = {
//	{.uChar[0] = 0},							// empty to make Index step
//	{.F.uCmd = START, .F.uCount = EEDEV}, 		// start command with address
//	{.F.uCmd = TX, .F.uCount = 12 - 1},			// send 12 bytes,
//	{.uChar[0] = 0, .uChar[1] = 0},				// first 2 bytes are address
//		{.uChar[0] = 'A', .uChar[1] = 'S'}, 	// next 2 are "AS"
//		{.uChar[0] = 'P', .uChar[1] = 'G'}, 	// next 2 are "PF"
//		{.uChar[0] = ' ', .uChar[1] = 'V'}, 	// next 2 are " V"
//		{.uChar[0] = '0', .uChar[1] = '.'}, 	// next 2 are "0."
//		{.uChar[0] = '0', .uChar[1] = 0}, 		// next 2 are "0" + NULL
//	{.F.uCmd = STOP},							// bus stop
//	{.F.uCmd = FINISHED}						// finished
//};
//const I2C_Action readEEtest[] = {  
//	{.uChar[0] = 0},							// empty to make Index step
//	{.F.uCmd = START, .F.uCount = EEDEV}, 		// start command with address
//	{.F.uCmd = TX, .F.uCount = 2 - 1}, 			// send 2 bytes,
//	{.uChar[0] = 0x0, .uChar[1] = 0x0}, 		// 2 bytes are address (MSB first)
//	{.F.uCmd = RESTART, .F.uCount = EEDEV+1}, 		// start command with address
//	{.F.uCmd = RX_ACK, .F.uCount = 10 - 1},		// receive 10 bytes,
//	{.F.uCmd = STOP},							// bus stop
//	{.F.uCmd = FINISHED}						// finished
//};
//
