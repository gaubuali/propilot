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

// #define	ADCON2CONFIG 0b0010010000011000 ; //?

#define XRATE_SIGN -
#define YRATE_SIGN -
#define ZRATE_SIGN -

#define XACCEL_SIGN +
#define YACCEL_SIGN +
#define ZACCEL_SIGN +

//#define VREF

#define SCALEGYRO 4.95
//#define SCALEACCEL 2.64
#define SCALEACCEL 2.49
//#define SCALEACCEL 3.64

// Max inputs and outputs
#define MAX_INPUTS	8
#define MAX_OUTPUTS	8

// There are no hardware toggle switches on the UDB4, so use values of 0
#define HW_SWITCH_1			0
#define HW_SWITCH_2			0
#define HW_SWITCH_3			0

#define FAR_BUF __attribute__ ((far, section("FarBuffers")))
#define NEAR_BUF __attribute__ ((near, section("NearBuffers")))
#define IMPORTANT __attribute__ ((near, section("Important")))
#define PARAMETER __attribute__ ((near, section("Parameters")))

/* Pin structure notes:
	Failsafe is a health check on the system. For inputs (see note on types below) it is cleared
	by the interrupt routine when a valid pulse in received and incremented by the main DCM
	routine. For outputs its incremented by the interrupt routine and cleared by the DCM. When
	the count hits 17 ie FS_ON changes state, the two routines start using values based on FS_CMD.
	FS_CMD = 0 use current or basically ignore the condition, = 1 use -1 or min, = 2 use +1 or max,
	3 = use 0 for values ie center controls, 4 = use -70%, 5 = use +70%, 6 = use recorded trim,
	7 still needs to be defined.

	Type defines usage for this pin - not all types are valid for all pins and setting a non-possible
	type for a pin will produce at best garbage and at worst a lockup. Used during init to set tris
	registers etc - be careful with this. The Port and Pin values are used to address the correct
	config registers and need to be correct. Initially these would only apply to the servo output
	and rc input pins but could be used for the extra pins that are going to be available with the
	new boards.
	0	unused, don't do anything
	1	Analog input, makes sure the AdxPCFG are cleared - nominally they should be on powerup
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
	18	Digital input counts / mSec, only available on ITx pins - 0 ~ 64MHz ( 64k counts in 1 mSec, 1kHz update)
	19	Digital input counts / 20 mSec, only available on ITx pins - 0 ~ 3.2MHz (64k counts in 20 mSec, 50Hz update)
	20	Digital input counts / 25 mSec, only available on ITx pins - 0 ~ 2.6MHz (64k counts in 25 mSec, 40Hz update)
	21	Digital input counts / 100 mSec, only available on ITx pins - 0 ~ 650kHz (64k counts in 100 mSec, 10Hz update)
	22	to  31 undefined, same treatment as 0

	Current index is used to keep track of the current location in the Data array. For single channel
	inputs and outputs its going to show were in the history the current value got placed, for
	multiple input or output pins its going to point to the last one input or output.

	Global is the index into global Inputs or Outputs depending on type. Glen 0 = 1, 1 = 8, 2 = 12,
	3 = 16. TODO: Index is checked against these values to not overwrite other data.

	Private + Buffer: These variables are for the interrupt routine to do housekeeping, keep track
	of were it is in a sequence etc and to have live values available on switch in and out of
	fail safe mode when the RC system is in range and on but mode has been switched to assist or
	way point.
 */

typedef struct tagPin {
			 int	qValue;			// latest value, careful of non-single use pins
	unsigned int	iFS_Count:4;	// fail safe counter
	unsigned int	bFS_ON:1;		// 0 = normal run, 1 = fail safe triggered
	unsigned int	iFS_CMD:3;		// action to take in fail safe.
	unsigned int	bFS_EN:1;		// old fail safe enabled
	unsigned int	iUpdate:7;		// needs / has update
	unsigned int	iIndex:4;		// keeps track of were it is in sequences
	unsigned int	iType:5;		// pin type, see comments
	unsigned int	iPort:3;		// cpu port, 0=A, 1=B etc
	unsigned int	iPin:4;			// pin within port
	unsigned int	iGlobal:6;		// Index into global data arrays, eg pwIn for radio rx etc
	unsigned int	iGlen:2;		// number of spots taken, 0=1, 1=8,
	unsigned int	iSpare:8;		// unused
	union {				// private use for type functions
		int iPrivate[4];
		long lPrivate[2];
		WORD wPrivate[4];
		DWORD dwPrivate[2];
	};
	union {
		int	iBuffer[16];	// globally available data, can be 16 history of 1 each or 16 x 1 each
		WORD wBuffer[16];
	};
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
	int				iScales[2];	// raw word access, used by final scale and limit function
	unsigned char 	cRaw[4];	// raw byte access to data
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

// all these counts below give 0.2 uSec resolution, 1:7000 or about 12.8 bits
#define RC_PWM_MIN 4000		// 0.8 mSec
#define RC_PWM_CENTER 7500	// 1.5 mSec
#define RC_PWM_MAX 11000	// 2.2 mSec
#define RC_PWM_Q15 8
#define RC_PPM_SYNC 17500	// 3.5 mSec
#define RC_PPM_MAX 125000	// 15.0 mSec

#define AN0 0x0001
#define AN1 0x0002
#define AN2 0x0004
#define AN3 0x0008
#define AN4 0x0010
#define AN5 0x0020
#define AN6 0x0040
#define AN7 0x0080
#define AN8 0x0100
#define AN9 0x0200
#define AN10 0x0400
#define AN11 0x0800
#define AN12 0x1000
#define AN13 0x2000
#define AN14 0x4000
#define AN15 0x8000
#define AN16 0x0001
#define AN17 0x0002
#define AN18 0x0004
#define AN19 0x0008
#define AN20 0x0010
#define AN21 0x0020
#define AN22 0x0040
#define AN23 0x0080
#define AN24 0x0100
#define AN25 0x0200
#define AN26 0x0400
#define AN27 0x0800
#define AN28 0x1000
#define AN29 0x2000
#define AN30 0x4000
#define AN31 0x8000

#define AUX_AN1 AN0
#define AUX_AN2 AN1
#define AUX_AN3 AN3
#define AUX_AN4 AN4

#define SAmps AN6
#define SVolt AN7

#define YRateH AN22
#define YRateL AN23
#define TempY AN24
#define VRef_Y AN25

#define XRateL AN26
#define XRateH AN27
#define TempXZ AN28
#define VRef_XZ AN29

#define ZRateH AN30
#define ZRateL AN31

// you have to know if the analog is in the high set or low set for these to work
#define LOW_ANALOGS (AUX_AN1 | AUX_AN2 | AUX_AN3 | AUX_AN4 | SAmps | SVolt)
#define HIGH_ANALOGS (YRateH | YRateL | TempY | VRef_Y | XRateH | XRateL | TempXZ | VRef_XZ | ZRateH | ZRateL )
// DMA buffer order is     0        1       2        3        4        5        6         7        8        9
// define the analogs in each scan list, AD1 module used for gyros (DO NOT ADD TO THIS LIST) all high
// this is critical, don't touch without mods in analog2digital_aspg.c
#define AD1_LIST HIGH_ANALOGS
#define NUM_AD1_LIST 10

#define	xrateBUFF	6
#define	yrateBUFF	2
#define	zrateBUFF	10

#define	xaccelBUFF	-1
#define	yaccelBUFF	-2
#define	zaccelBUFF	-3

// other analogs
#define AD2_LIST LOW_ANALOGS
#define NUM_AD2_LIST 6

// General purpose digital
#define iDIGITAL1 PORTGbits.RG12
#define oDIGITAL1 LATGbits.LATG12
#define tDIGITAL1 TRISGbits.TRISG12
#define iDIGITAL2 PORTGbits.RG13
#define oDIGITAL2 LATGbits.LATG13
#define tDIGITAL2 TRISGbits.TRISG13
#define iDIGITAL3 PORTGbits.RG14
#define oDIGITAL3 LATGbits.LATG14
#define tDIGITAL3 TRISGbits.TRISG14
#define iDIGITAL4 PORTGbits.RG15
#define oDIGITAL4 LATGbits.LATG15
#define tDIGITAL4 TRISGbits.TRISG15
#define iDIGITAL5 PORTAbits.RA0
#define oDIGITAL5 LATAbits.LATA0
#define tDIGITAL5 TRISAbits.TRISA0
#define iDIGITAL6 PORTAbits.RA1
#define oDIGITAL6 LATAbits.LATA1
#define tDIGITAL6 TRISAbits.TRISA1
#define iDIGITAL7 PORTAbits.RA4
#define oDIGITAL7 LATAbits.LATA4
#define tDIGITAL7 TRISAbits.TRISA4
#define iDIGITAL8 PORTAbits.RA5
#define oDIGITAL8 LATAbits.LATA5
#define tDIGITAL8 TRISAbits.TRISA5
#define iDIGITAL9 PORTAbits.RA14
#define oDIGITAL9 LATAbits.LATA14
#define tDIGITAL9 TRISAbits.TRISA14
#define iDIGITAL10 PORTAbits.RA15
#define oDIGITAL10 LATAbits.LATA15
#define tDIGITAL10 TRISAbits.TRISA15

// These are used in the code
#define oAZ_Y oDIGITAL1
#define tAZ_Y tDIGITAL1
#define oAZ_XZ oDIGITAL2
#define tAZ_XZ tDIGITAL2
#define oOUT1 oDIGITAL4
#define oICSP1_AUX1 oDIGITAL9
#define oICSP1_AUX2 oDIGITAL10
#define iBUZZER1 PORTBbits.RB5
#define oBUZZER1 LATBbits.LATB5
#define tBUZZER1 TRISBbits.TRISB5

// Servo outputs
#define iSERVO1 PORTDbits.RD0
#define oSERVO1 LATDbits.LATD0
#define tSERVO1 TRISDbits.TRISD0
#define iSERVO2 PORTDbits.RD1
#define oSERVO2 LATDbits.LATD1
#define tSERVO2 TRISDbits.TRISD1
#define iSERVO3 PORTDbits.RD2
#define oSERVO3 LATDbits.LATD2
#define tSERVO3 TRISDbits.TRISD2
#define iSERVO4 PORTDbits.RD3
#define oSERVO4 LATDbits.LATD3
#define tSERVO4 TRISDbits.TRISD3
#define iSERVO5 PORTDbits.RD4
#define oSERVO5 LATDbits.LATD4
#define tSERVO5 TRISDbits.TRISD4
#define iSERVO6 PORTDbits.RD5
#define oSERVO6 LATDbits.LATD5
#define tSERVO6 TRISDbits.TRISD5
#define iSERVO7 PORTDbits.RD6
#define oSERVO7 LATDbits.LATD6
#define tSERVO7 TRISDbits.TRISD6
#define iSERVO8 PORTDbits.RD7
#define oSERVO8 LATDbits.LATD7
#define tSERVO8 TRISDbits.TRISD7

// RC inputs
#define iRC1 PORTDbits.RD8
#define oRC1 LATDbits.LATD8
#define tRC1 TRISDbits.TRISD8
#define iRC2 PORTDbits.RD9
#define oRC2 LATDbits.LATD9
#define tRC2 TRISDbits.TRISD9
#define iRC3 PORTDbits.RD10
#define oRC3 LATDbits.LATD10
#define tRC3 TRISDbits.TRISD10
#define iRC4 PORTDbits.RD11
#define oRC4 LATDbits.LATD11
#define tRC4 TRISDbits.TRISD11
#define iRC5 PORTDbits.RD12
#define oRC5 LATDbits.LATD12
#define tRC5 TRISDbits.TRISD12
#define iRC6 PORTDbits.RD13
#define oRC6 LATDbits.LATD13
#define tRC6 TRISDbits.TRISD13
#define iRC7 PORTDbits.RD14
#define oRC7 LATDbits.LATD14
#define tRC7 TRISDbits.TRISD14
#define iRC8 PORTDbits.RD15
#define oRC8 LATDbits.LATD15
#define tRC8 TRISDbits.TRISD15

// Inputs connected to timer modules
#define iIT1 PORTCbits.RC4
#define oIT1 LATCbits.LATC4
#define tIT1 TRISCbits.TRISC4
#define iIT2 PORTCbits.RC3
#define oIT2 LATCbits.LATC3
#define tIT2 TRISCbits.TRISC3
#define iIT3 PORTCbits.RC2
#define oIT3 LATCbits.LATC2
#define tIT3 TRISCbits.TRISC2
#define iIT4 PORTCbits.RC1
#define oIT4 LATCbits.LATC1
#define tIT4 TRISCbits.TRISC1

// System LED's
#define iLED1 PORTBbits.RB8
#define oLED1 LATBbits.LATB8
#define tLED1 TRISBbits.TRISB8
#define iLED2 PORTBbits.RB9
#define oLED2 LATBbits.LATB9
#define tLED2 TRISBbits.TRISB9
#define iLED3 PORTBbits.RB10
#define oLED3 LATBbits.LATB10
#define tLED3 TRISBbits.TRISB10
#define iLED4 PORTBbits.RB11
#define oLED4 LATBbits.LATB11
#define tLED4 TRISBbits.TRISB11

// LED pins
#define LED_ORANGE	oLED1
#define LED_BLUE	oLED2
#define LED_GREEN	oLED3
#define LED_RED		oLED4

// These are data ready inputs from I2C magnetometer and accelerometer
#define iMAG_DR1 PORTAbits.RA12
#define oMAG_DR1 LATAbits.LATA12
#define tMAG_DR1 TRISAbits.TRISA12
#define MAG_DR iMAG_DR1
#define MAG_DRt tMAG_DR1
#define MAG_INTe _INT1IE
#define MAG_INTf _INT1IF
#define MAG_INTpo _INT1EP
#define MAG_INTpr IPC5bits.INT1IP

#define iACC_DR1 PORTAbits.RA13
#define oACC_DR1 LATAbits.LATA13
#define tACC_DR1 TRISAbits.TRISA13
#define ACC_DR iACC_DR1
#define ACC_DRt tACC_DR1
#define ACC_INTe _INT2IE
#define ACC_INTf _INT2IF
#define ACC_INTpo _INT2EP
#define ACC_INTpr IPC7bits.INT2IP

struct tagI2C_flags {
	unsigned int bInUse:1;		// in use right now
	unsigned int bERROR:1;		// in use right now, restarting
	unsigned int bMagReady:1;	// mag needs to be read
	unsigned int bAccReady:1;	// Accelerometer needs to be read
	unsigned int bReadMag:1;	// reading mag
	unsigned int bReadAcc:1;	// reading Accelerometer
	unsigned int bReadEE1:1;	// reading EE Prom, stage 1
	unsigned int bReadEE2:1;	// reading EE Prom, stage 2
	unsigned int bReadEE3:1;	// reading EE Prom, stage 3 (done)
	unsigned int bWriteEE1:1;	// write EE Prom, stage 1
	unsigned int bWriteEE2:1;	// write EE Prom, stage 2
	unsigned int bWriteEE3:1;	// write EE Prom, stage 2 (done)
};

// Most all the other I/O is used by a smart peripheral or not connected to anything

typedef union tagI2C {
	unsigned char uChar[2];	// two bytes, one at a time
	unsigned int uInt;		// 16 bits all at once
		struct tagFields {	// field definitions to make easy to use / read
	unsigned int uCmd:3;	// 0=nothing, 1=start, 2=restart, 3=stop, 4=TX, 
							// 5=RX with ACK, 6=RX 1 with NACK, 7 = finished
	unsigned int uACK:1;	// 0=ACKSTAT must be 0, 1=ACKSTAT don't care
							// just for FINISHED command,
							//		0 = nothing,
							//		1 = iResult += 1;
	unsigned int uBuf:1;	// 0=data sent from uI2C_Commands, 1=I2C_buffer
							// I2C_Tail used as index on TX, I2C_Head on RX
							// just for FINISHED command,
							//		0 = no call back,
							//		1 = call I2C_call_back[CC.Ident&0x7]
	unsigned int uResult:3;	// FINISHED command, copies CC into result buffer ie
							// CD[CC.Ident&0x7] = CC at end, CD[0] reserved
							//	0 = nothing,
							//	RSET = 1 = iResult is set to .uCount,
							//	RADD = 2 = add .uCount to iResult
							//	PSET = 3 = *piResult is set to .uCount,
							//	PADD = 4 = add .uCount to *piResult
							//	CCPY = 5 = copy .uCount bytes from I2C_buffer to *pcResult,
							//	HCPY = 6 = copy I2C_Head bytes from I2C_buffer to *pcResult,
							//	7 = not implimented yet, *result could be a function call
	unsigned int uCount:8;	// 0=1, 1=2, 2=3 etc also depends on command
							// also used for slave address
				} F;
} I2C_Action, *LPI2C_Action;

// some commands have implied length, start is followed by 1 byte bus address (R/W bit must be what you need)
// wait till I2C_Command = 0 then fill uI2C_Commands with pseudo code then call I2C_Start, poll I2C_Command =
// expected end value for done or I2CERROR != 0 for error code. Make sure you set I2C_Command back to 0 so next
// use can happen otherwise its going to sit there forever.

// these enum's are the constants used in the switches
enum I2C_Cmd {NOTHING, START, RESTART, STOP, TX, RX_ACK, RX_NACK, FINISHED};
enum I2C_Sub {//NOTHING, START, RESTART, STOP, TX, RX_ACK, RX_NACK, FINISHED,
				START_ACK=11, START_NA,
				TX_LOW=41, TX_HIGH,
				RX_ACK_CLK=51, RX_NACK_CLK
};
enum I2C_ERR { // NOTHING,	// error codes in I2CERROR
				TIMEOUT = 1, NO_ACK, BUS, NO_REC, RUNAWAY };
enum I2C_FIN { // NOTHING,	// .uResult codes for FINISHED command
				RSET = 1, RADD, PSET, PADD, CCPY, HCPY };

// read's call doneMagReadData() & inc, others just increment CD[magCDindex].iResult
enum magSetup { MAG_WAIT,					// 0 value on c runtime startup
				MAG_DREAD1,					// dummy read 1 from buffer, read auto-inc
				MAG_RESET, MAG_DREAD2,		// send reset + read (puts in one shot mode)
				MAG_DELAY1,					// iResult only get inc in rxMag so its a delay
				MAG_CAL,					// send cal command + read it
				MAG_DELAY2,					// iResult only get inc in rxMag so its a delay
				MAG_CAL_DOREAD,
				MAG_CAL_PROCESS,			// iResult only get inc in rxMag so its a delay
				MAG_SEND_CFG,				// send config
				MAG_DELAY3,					// iResult only get inc in rxMag so its a delay
				MAG_NORMAL					// this value or higher is normal run mode
};


enum accSetup { ACC_WAIT,					// 0 value on c runtime startup
				ACC_DREAD1,					// dummy read 1 from buffer, read auto-inc
				ACC_RESET, ACC_DREAD2,		// send reset + read (puts in one shot mode)
				ACC_DELAY1,					// iResult only get inc in rxAcc so its a delay
				ACC_CAL, ACC_CAL_DOREAD,	// send cal command + read it
				ACC_CAL_PROCESS,			// iResult only get inc in rxMag so its a delay
				ACC_SEND_CFG,				// send config
				ACC_NORMAL					// this value or higher is normal run mode
};


typedef struct tagI2Ccommand {	// structure used in running I2C devices and saving results
	int	Ident;					// application layer use, low 3 bits = result buffer
	int I2C_Index;				// current command index into uI2C_Commands
	int I2C_Subcode;			// subcode driven by hardware status
	int I2C_Sublen;				// length is used in TX and RX
	int I2C_Slave;				// on a start condition saves the slave address
	unsigned int Messages;		// count of messages to this device
	int	I2C_Head;				// index into data buffer
	int I2C_Tail;
	int iResult;				// data add or set mode
	int *piResult;				// int pointer mode
	unsigned char *pcResult;	// pointer to string
	int I2CERROR, I2CERROR_CON, I2CERROR_STAT;	// record for errors
	I2C_Action I2C_Code;		// current action, also used to keep flags when data is in buffer
} I2CCMD, *LPI2CCMD;

// LED control structure - this is to make the LED's a little smarter and just on/off
// The driver routine LED_Update in servoOut_aspg.c is called at 1kHz from the T3 interrupt service.
// It uses uMode to determine what to do on each call - use the values from LED_ctrl enum.
// Basically there are 3 modes so far and all modes use the LED_ON and LED_OFF macros to return the
// correct pin state for what you want ie LED_OFF is actually 1 and LED_ON is actually 0.
// First mode is simply called ON_OFF were the low bit of uOnDuty selects the on or off state.
// Second mode is a duty cycle were you can set both the on to off time ratio and the time base.
// These are all labeled DUTY_xmS were the xmS is the time base. The time base determines the count
// rate so 1mS means it counts on each call, 2mS means count every other call etc. On each call that
// actually counts the wBits field is incremented and compared to the appropriate uOnDuty or uOffDuty
// value and if its larger the LED state is flipped and the counter reset. By using the different
// count rates and on and off values a very wide range of flash rate can be created.
// Third mode is ANALOG were the led state is updated on each call by using the low 4 bits of the
// system millisec timer as a bit index into wBits - this makes a somewhat analog glow. The routine
// updates this bit pattern from a table when uOnDuty != uOffDuty by using the low 4 bits of uOnDuty.
// You may set your own pattern by setting these equal and placing the pattern in wBits.
// Using an undefined mode just returns the current state.
typedef struct tagLedDisp {		// structure to control LED
	unsigned int uOnDuty:6;		// on cycle count
	unsigned int uOffDuty:6;	// off cycle count
	unsigned int uMode:4;		// see LED_ctrl enum
	WORD wBits;
} LEDCTRL, *LPLEDCTRL;

enum LED_ctrl {
	LED_DUTY_1mS = 0,	// count at base rate (1kHz), tick = 1mS
	LED_DUTY_2mS = 1,	// count rate = 500hz, tick = 2ms
	LED_ON_OFF   = 2,	// use low bit of uOnDuty for state, 1=ON 0=OFF
	LED_DUTY_4mS = 3,	// count rate = 250hz, tick = 4ms
	LED_ANALOG   = 4,	// output "glow" based on table and low 4 bits of uOnDuty
	LED_SPARE_05 = 5,	// not used yet
	LED_SPARE_06 = 6,	// not used yet
	LED_DUTY_8mS = 7,	// count rate = 125hz, tick = 8ms
	LED_DUTY_16mS = 15,	// count rate = 62.5hz, tick = 16ms
};

// "structure" of the 3 registers that control an output compare module.
typedef struct tagOCM {
	WORD OCRS;
	WORD OCR;
	WORD OCCON; // we only need the low 3 bits, the others are all default (0)
} OCM, *LPOCM;

