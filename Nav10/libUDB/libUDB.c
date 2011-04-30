// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
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
#include "defines.h"
#include <string.h>

#if (BOARD_IS_CLASSIC_UDB)
#if ( CLOCK_CONFIG == CRYSTAL_CLOCK )
_FOSC( CSW_FSCM_OFF & HS ) ;		// external high speed crystal
#elif ( CLOCK_CONFIG == FRC8X_CLOCK ) 
_FOSC(CSW_FSCM_OFF & FRC_PLL8);
#endif
_FWDT( WDT_OFF ) ;					// no watchdog timer
_FBORPOR( 	PBOR_OFF &				// brown out detection off
			MCLR_EN &				// enable MCLR
			RST_PWMPIN &			// pwm pins as pwm
			PWMxH_ACT_HI &			// PWMH is active high
			PWMxL_ACT_HI ) ;		// PMWL is active high
_FGS( CODE_PROT_OFF ) ;				// no protection
_FICD( 0xC003 ) ;					// normal use of debugging port

#elif (BOARD_TYPE == UDB4_BOARD)
_FOSCSEL(FNOSC_FRCPLL) ;			// fast RC plus PLL
_FOSC(	FCKSM_CSECMD &
		OSCIOFNC_ON &
		POSCMD_NONE ) ;
_FWDT(	FWDTEN_OFF &
		WINDIS_OFF ) ;
_FGS(	GSS_OFF &
		GCP_OFF &
		GWRP_OFF ) ;
_FPOR(	FPWRT_PWR1 ) ;
_FICD(	JTAGEN_OFF &
		ICS_PGD2 ) ;
#elif (BOARD_TYPE == ASPG_BOARD)
_FBS( BWRP_WRPROTECT_OFF );		// no boot segments or write protect
_FSS ( SWRP_WRPROTECT_OFF );	// no secure sections
_FGS( GSS_OFF &					// no code protect
		GCP_OFF &
		GWRP_OFF );
_FOSCSEL( FNOSC_FRC &			// external clock + PLL enabled in code
		IESO_OFF );				// include file is WRONG
_FOSC(	FCKSM_CSECMD &			// clocks and monitor enabled
		OSCIOFNC_OFF &			// no Fcy output on OSC2
		POSCMD_EC );
_FWDT(	FWDTEN_OFF &			// wdt's disabled
		WINDIS_OFF ) ;
_FPOR(	FPWRT_PWR32 ) ;			// fast powerup, will need to change for ext osc
_FICD(	JTAGEN_OFF &			// jtag off and use 2nd set for ICSP
		ICS_PGD2 ) ;
//_FUID0( 0xffff )
//_FUID1( 0xffff )
//_FUID2( 0xffff )
//_FUID3( 0xffff )
#endif


union udb_fbts_byte udb_flags ;

//boolean timer_5_on = 0 ;
int needSaveExtendedState IMPORTANTz;
int defaultCorcon IMPORTANTz;
volatile int trap_flags __attribute__ ((persistent,section(".Persistant")));
volatile long trap_source __attribute__ ((persistent,section(".Persistant")));

/*
WORD wSP_Save;
typedef struct tagRESETS {
unsigned int StackError:1;
unsigned int ACA_OVAERR:1;
unsigned int ACA_COVAERR:1;
unsigned int ACB_OVBERR:1;
unsigned int ACB_COVBERR:1;
unsigned int DIV0_Err:1;
unsigned int STF_Err:1;
unsigned int MATH_Err:1;
unsigned int DMA_Err:1;
unsigned int OSC_Err:1;
unsigned int ADDR_Err:1;
} NMI;
NMI	SaveNMI = {0}; // clear

void __attribute__((__interrupt__,__no_auto_psv__)) _DefaultInterrupt(void)
{
	WORD wSP_Temp = WREG15;
	if ( _STKERR )
		SaveNMI.StackError = 1;
	if ( _OVAERR )
		SaveNMI.ACA_OVAERR = 1;
	if ( _COVAERR )
		SaveNMI.ACA_COVAERR = 1;
	if ( _OVBERR )
		SaveNMI.ACB_OVBERR = 1;
	if ( _COVBERR )
		SaveNMI.ACB_COVBERR = 1;
	if ( _SFTACERR )
		SaveNMI.STF_Err = 1;
	if ( _MATHERR )
		SaveNMI.MATH_Err = 1;
	if ( _DMACERR )
		SaveNMI.DMA_Err = 1;
	if ( _OSCFAIL || _CF )
		SaveNMI.OSC_Err = 1;
	if ( _ADDRERR )
		SaveNMI.ADDR_Err = 1;
	
	wSP_Save = wSP_Temp;
	__asm__("RESET");
}
*/

void udb_init(void)
{
	defaultCorcon = CORCON ;
	
#if (BOARD_TYPE == UDB4_BOARD)
	CLKDIVbits.PLLPRE = 1 ;
	PLLFBDbits.PLLDIV = 50 ; // FOSC = 32 MHz (FRC = 7.37MHz, N1=3, N2=4, M = 52)
#elif (BOARD_TYPE == ASPG_BOARD)
	RCONbits.SWDTEN = 0;		// make sure its disabled
	ClrWdt();

	OSCTUNbits.TUN = 21;		// boost speed up to 8MHz, FRC = 7.37MHz + 21*30kHz
	CLKDIVbits.PLLPRE = 1 ;		// pre devide = 3 (12MHz / 3 = 4MHz)
	PLLFBDbits.PLLDIV = 40-2 ; 	// Fvco = 160 MHz (4MHz x 40 = 160Mhz)
	CLKDIVbits.PLLPOST = 0;		// FOSC = Fvco / 2 = 80MHz

	// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x03);				// Initiate Clock Switch to
												// EC with PLL (NOSC=0b001)
	__builtin_write_OSCCONL(0x01);				// Start clock switching
	while(OSCCONbits.LOCK!=1) {};				// Wait for PLL to lock
//	oLED3 = LED_ON;

//	oLED1 = LED_ON;
	while (OSCCONbits.COSC != 0b011);			// Wait for Clock switch to occur
//	oLED2 = LED_ON;

#endif

	udb_flags.B = 0 ;
	
	udb_init_leds() ;
	udb_init_ADC() ;
	udb_init_clock() ;
	udb_init_capture() ;
	
#if (MAG_YAW_DRIFT == 1) || (BOARD_TYPE == ASPG_BOARD)
	udb_init_I2C2() ;
#endif
#if (BOARD_TYPE == ASPG_BOARD)
	rxAccel();
#endif
#if (MAG_YAW_DRIFT == 1)
	rxMagnetometer();
#endif
	
	udb_init_GPS() ;
	udb_init_USART() ; udb_serial_set_rate( SERIAL_OUTPUT_BAUD );
	udb_init_pwm() ;
#if (USE_OSD == 1)
	udb_init_osd() ;
#endif
	
	SRbits.IPL = 0 ;	// turn on all interrupt priorities

	udb_init_EE();
#if (FLIGHT_PLAN_TYPE == FP_WAYPOINTS) && (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( cEEpresent )
	{
		int ready, idx;
//		memset( &wpTemp, 0, sizeof(wpTemp) );	// clear so xlate will read
		for ( idx = 0; idx < 4; idx++ ) {
			ready = xlateWPbyIndex( idx, &wpTemp );
			while (EE_Active != 0)		// this forces a wait in this function
				indicate_loading_main;
			xlateWPbyIndex( idx, &wpTemp );
			injectWPatIndex( idx );
		}
	}
#endif

	
	return ;
}


void udb_run(void)
{
	//  nothing else to do... entirely interrupt driven
	while (1)
	{
		// pause cpu counting timer while not in an ISR
		indicate_loading_main ;
		// neither of these "return" till done but do keep the flag off while waiting
		if ( flags._.write_EE_wp )	// writes get priority
		{
			WriteEEWaypoint(); 
			flags._.write_EE_wp = 0;
		} else
		if ( flags._.write_EE_param )
		{
			WriteParameters();
			udb_serial_send_string( (unsigned char *)"done." );
			flags._.write_EE_param = 0;
		} else
		if ( flags._.read_EE_param && !flags._.write_EE_param )
		{
			ReadParameters();
			udb_serial_send_string( (unsigned char *)"done." );
			flags._.read_EE_param = 0;
		} else 
		if ( flags._.read_EE_wp && !flags._.write_EE_wp)
		{
			ReadEEWaypoint(); 
			flags._.read_EE_wp = 0;
		} 
	}
	// Never returns
}


void udb_init_leds( void )
{
	
#if (BOARD_IS_CLASSIC_UDB == 1)
	TRISFbits.TRISF0 = 0 ;
	
#elif (BOARD_TYPE == UDB4_BOARD )
	_TRISE1 = _TRISE2 = _TRISE3 = _TRISE4 = 0 ;
	_LATE1 = _LATE2 = _LATE3 = _LATE4 = LED_OFF ;
#elif ( BOARD_TYPE == ASPG_BOARD)
	tLED1 = tLED2 = tLED3 = tLED4 = 0 ;
	oLED1      = oLED2	  = oLED3	  = oLED4   = LED_OFF ;
	LED_ORANGE = LED_BLUE = LED_GREEN = LED_RED = LED_OFF ;
#endif
	
	return ;
}


// the compiler does not respect the resource used by the Microchip math
// library, so interrupts need to save and restore extended state, and
// reset CORCON if firing in the middle of a math lib call.
void udb_setDSPLibInUse(boolean inUse)
{
	if ( inUse )
		needSaveExtendedState += 1 ;
	else needSaveExtendedState -= 1 ;
	return ;
}


void udb_a2d_record_offsets(void)
{
	// almost ready to turn the control on, save the input offsets
#if (BOARD_TYPE == ASPG_BOARD)
	if ( udb_zrate.offset == 0 )	// detect first call
	{
		UDB_XACCEL.offset = UDB_XACCEL.value ;
		udb_xrate.offset = udb_xrate.value ;
		UDB_YACCEL.offset = UDB_YACCEL.value ;
		udb_yrate.offset = udb_yrate.value ;
		UDB_ZACCEL.offset = UDB_ZACCEL.value GRAVITY_SIGN ((int)(2*GRAVITY)) ;  // GRAVITY is measured in A-D/2 units
		udb_zrate.offset = udb_zrate.value ;									// The sign is for inverted boards
	} else {
//		UDB_XACCEL.offset = UDB_XACCEL.value - averageSample( &DIO[34].iBuffer[0], 16 );
//		udb_xrate.offset = udb_xrate.value - averageSample( &DIO[31].iBuffer[0], 16 );
//		UDB_YACCEL.offset = UDB_YACCEL.value - averageSample( &DIO[35].iBuffer[0], 16 );
//		udb_yrate.offset = udb_yrate.value - averageSample( &DIO[32].iBuffer[0], 16 );
//		UDB_ZACCEL.offset = UDB_ZACCEL.value GRAVITY_SIGN ((int)(2*GRAVITY)) ;  // GRAVITY is measured in A-D/2 units
//		UDB_ZACCEL.offset -= averageSample( &DIO[36].iBuffer[0], 16 );			// The sign is for inverted boards
//		udb_zrate.offset = udb_zrate.value - averageSample( &DIO[33].iBuffer[0], 16 );
		UDB_XACCEL.offset = averageSample( &DIO[34].iBuffer[0], 16 );
		udb_xrate.offset = averageSample( &DIO[31].iBuffer[0], 16 );
		UDB_YACCEL.offset = averageSample( &DIO[35].iBuffer[0], 16 );
		udb_yrate.offset = averageSample( &DIO[32].iBuffer[0], 16 );
//		UDB_ZACCEL.offset = UDB_ZACCEL.value GRAVITY_SIGN ((int)(2*GRAVITY)) ;  // GRAVITY is measured in A-D/2 units
		UDB_ZACCEL.offset = averageSample( &DIO[36].iBuffer[0], 16 ) GRAVITY_SIGN ((int)(2*GRAVITY));			// The sign is for inverted boards
		udb_zrate.offset = averageSample( &DIO[33].iBuffer[0], 16 );
	}
#else
	UDB_XACCEL.offset = UDB_XACCEL.value ;
	udb_xrate.offset = udb_xrate.value ;
	UDB_YACCEL.offset = UDB_YACCEL.value ;
	udb_yrate.offset = udb_yrate.value ;
	UDB_ZACCEL.offset = UDB_ZACCEL.value GRAVITY_SIGN ((int)(2*GRAVITY)) ;  // GRAVITY is measured in A-D/2 units
	udb_zrate.offset = udb_zrate.value ;									// The sign is for inverted boards
#endif
#ifdef VREF
	udb_vref.offset = udb_vref.value ;
#endif
	return ;
}


void udb_servo_record_trims(void)
{
//	int i;
//	for (i=0; i < 65; i++)
//		udb_pwTrim[i] = udb_pwIn[i] ;
	memcpy( &udb_pwTrim[0], &udb_pwIn[0], sizeof(udb_pwTrim)) ;
	
	return ;
}


// saturation logic to maintain pulse width within bounds
int udb_servo_pulsesat ( long pw )
{
	if ( pw > SERVOMAX ) pw = SERVOMAX ;
	if ( pw < SERVOMIN ) pw = SERVOMIN ;
	return (int)pw ;
}
