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

// nothing, start, slave, tx(8), address(2 = 0) + "ASPG V0.0\0", stop, finished
const I2C_Action writeEEtest[] = {
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0xAE}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 12 - 1},			// send 12 bytes,
	{.uChar[0] = 0, .uChar[1] = 0},				// first 2 bytes are address
		{.uChar[0] = 'A', .uChar[1] = 'S'}, 	// next 2 are "AS"
		{.uChar[0] = 'P', .uChar[1] = 'G'}, 	// next 2 are "PF"
		{.uChar[0] = ' ', .uChar[1] = 'V'}, 	// next 2 are "G "
		{.uChar[0] = '0', .uChar[1] = '.'}, 	// next 2 are "G "
		{.uChar[0] = '0', .uChar[1] = 0}, 		// next 2 are "G "
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED}						// finished
};
const I2C_Action readEEtest[] = {  
	{.uChar[0] = 0},							// empty to make Index step
	{.F.uCmd = START, .F.uCount = 0xAE}, 		// start command with address
	{.F.uCmd = TX, .F.uCount = 2 - 1}, 			// send 2 bytes,
	{.uChar[0] = 0x0, .uChar[1] = 0x0}, 		// 2 bytes are address (MSB first)
	{.F.uCmd = RESTART, .F.uCount = 0xAF}, 		// start command with address
	{.F.uCmd = RX_ACK, .F.uCount = 10 - 1},		// receive 10 bytes,
	{.F.uCmd = STOP},							// bus stop
	{.F.uCmd = FINISHED}						// finished
};

int EE_Write_Timer = 0;

#endif
