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


// used for the ASPG

#define FREQOSC 	32000000
#define CLK_PHASES	2

#define	ADCON2CONFIG 0b0010010000011000 ; //?

#define	xrateBUFF	3
#define	yrateBUFF	1
#define	zrateBUFF	2

#define	xaccelBUFF	5
#define	yaccelBUFF	6
#define	zaccelBUFF	4

#define XRATE_SIGN -
#define YRATE_SIGN -
#define ZRATE_SIGN -

#define XACCEL_SIGN +
#define YACCEL_SIGN +
#define ZACCEL_SIGN +

//#define VREF

#define SCALEGYRO 4.95
#define SCALEACCEL 2.64

// Max inputs and outputs
#define MAX_INPUTS	8
#define MAX_OUTPUTS	8

// LED pins
#define LED_ORANGE			LATEbits.LATE1
#define LED_BLUE			LATEbits.LATE2
#define LED_GREEN			LATEbits.LATE3
#define LED_RED				LATEbits.LATE4

// There are no hardware toggle switches on the UDB4, so use values of 0
#define HW_SWITCH_1			0
#define HW_SWITCH_2			0
#define HW_SWITCH_3			0

/* Pin structure notes:
	Failsafe is a health check on the system. For inputs (see note on types below) it is cleared
	by the interrupt routine when a valid pulse in received and incremented by the main DCM
	routine. For outputs its incremented by the interrupt routine and cleared by the DCM. When
	the count hits 33 ie FS_ON changes state, the two routines start using values based onFS_CMD.
	FS_CMD = 0 use 0 for values ie center controls, = 1 use -1 or min, = 2 use +1 or max,
	3 = use current or basically ignore the condition, 4 = use -0.7, 5 = use +0.7,
	6 and 7 still need to defined.

	Type defines usage for this pin – not all types are valid for all pins and setting a non-possible
	type for a pin will produce at best garbage and at worst a lockup. Used during init to set tris
	registers etc – be careful with this. The Port and Pin values are used to address the correct
	config registers and need to be correct. Initially these would only apply to the servo output
	and rc input pins but could be used for the extra pins that are going to be available with the
	new boards.
	0	unused, don't do anything
	1	Analog input, makes sure the AdxPCFG are cleared – nominally they should be on powerup
	2	Digital output, open drain disabled
	3	Digital output, open drain enabled (normally use this for CLR on 4017's)
	4	Digital input, pull up disabled
	5	Digital input, pull up enabled
	6	Single channel 50Hz PWM output, open drain disabled
	7	Single channel 50Hz PWM output, open drain enabled (normally use this)
	8	Single channel 450Hz PWM output, open drain disabled
	9	Single channel 450Hz PWM output, open drain enabled (normally use this)
	10	Multi channel 50Hz PWM output, open drain disabled (4017's)
	11	Multi channel 50Hz PWM output, open drain enabled (4017's normally use this)
	12	Single channel 50Hz PWM input, positive logic
	13	Single channel 50Hz PWM input, negative logic
	14	Single channel 450Hz PWM input, positive logic
	15	Single channel 450Hz PWM input, negative logic
	16	Multi channel 50Hz PWM input, positive logic (PPM encoders, direct connect to receivers etc)
	17	Multi channel 50Hz PWM input, negative logic (PPM encoders, direct connect to receivers etc)
	18	Digital input counter / timer, pull up disabled – only available on very select pins
	19	Digital input counter / timer, pull up enabled – only available on very select pins
	20
	21	to  31 undefined, same treatment as 0

	Current index is used to keep track of the current location in the Data array. For single channel
	inputs and outputs its going to show were in the history the current value got placed, for
	multiple input or output pins its going to point to the last one input or output.

	Global is the index into global Inputs or Outputs depending on type. Glen 0 = 1, 1 = 8, 2 = 12,
	3 = 16. Index is checked against these values to not overwrite other data.

	Private + Buffer: These variables are for the interrupt routine to do housekeeping, keep track
	of were it is in a sequence etc and to have live values available on switch in and out of
	fail safe mode when the RC system is in range and on but mode has been switched to assist or
	way point.
 */

typedef struct tagPin {
	int	qValue;			// latest value, carefull of non-single use pins
	int	iFS_Count:5;	// failsafe counter
	int	bFS_ON:1;		// 0 = normal run, 1 = failsafe trigered
	int	iFS_CMD:3;		// action to take in failsafe.
	int	bFS_EN:1;		// failsafe enabled
	int	iUpdate:6;		// needs / has update
	int	iType:5;		// pin type, see comments
	int	iPort:3;		// cpu port, 0=A, 1=B etc
	int	iPin:4;			// pin within port
	int	iIndex:4;		// keeps track of were it is in sequences
	int	iGlobal:6;		// Index into global data arrays, eg pwIn for radio rx etc
	int	iGlen:2;		// number of spots taken, 0=1, 1=8,
	int	iSpare:8;		// unused
	int iPrivate[4];	// private use for type functions
	int	iBuffer[16];	// globally available data, can be 16 history of 1 each or 16 x 1 each
} PIN, *LPPIN;

/* Mixer structure notes:
 *
 * Please see "Mixer.xls" available at TODO
 *
 * Type field, determines what exactly the mixer does
 * InpCH is nominally the RC manual input term, InpSSI is nominally the DCM output
 * InpTSI the third channel - All of these are indexes into the global Inputs array in Q15 format.
 * Factor specified in float and macro converted to Q15 format.
 * Scale and Offset convert the Q15 output format to timer units.
 *
 */
typedef union tagMixer {
	unsigned char 	cRaw[4];	// raw byte access to data
	int				iScales[2];	// raw word access, used by final scale function
	struct nTypes {
		int	iType:4;	// mixer type 0-15
		int	iInpCH:6;	// normal source channel from iInputs[] array
		int iInpSSI:6;	// second source input from iInputs[] array
		int	iFactor;	// Q15 format
	} nType;
	struct pTypes {
		int	iType:4;	// mixer type 0-15
		int	iInpCH:6;	// normal source channel from iInputs[] array
		int iInpSSI:6;	// second source input channel from iInputs[] array
		int	iInpTSI:6;	// third source input channel from iInputs[] array
		int	iFactor:10;	// Q15 format with bottom bits cleared
	} pType;
} MIXER, *LPMIXER;

#define toQ10(n) ((int)(n * 511))
#define toQ15(n) ((int)(n * 32767))
