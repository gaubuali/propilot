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

#if (BOARD_IS_CLASSIC_UDB)
_FOSC( CSW_FSCM_OFF & HS ) ;		// external high speed crystal
_FWDT( WDT_OFF ) ;					// no watchdog timer
_FBORPOR( 	PBOR_OFF &				// brown out detection off
			MCLR_EN &				// enable MCLR
			RST_PWMPIN &			// pwm pins as pwm
			PWMxH_ACT_HI &			// PWMH is active high
			PWMxL_ACT_HI ) ;		// PMWL is active high
_FGS( CODE_PROT_OFF ) ;				// no protection
_FICD( 0xC003 ) ;					// normal use of debugging port

#elif (BOARD_TYPE == UDB4_BOARD)
_FBS( BWRP_WRPROTECT_OFF );		// no boot segments or write protect
_FSS ( SWRP_WRPROTECT_OFF );	// no secure sections
_FGS( GSS_OFF &					// no code protect
		GCP_OFF &
		GWRP_OFF );
_FOSCSEL(FNOSC_FRCPLL); 			// fast RC plus PLL
_FOSC(	FCKSM_CSECMD &
		OSCIOFNC_ON &
		POSCMD_NONE );
_FWDT(	FWDTEN_OFF &
		WINDIS_OFF ) ;
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
		OSCIOFNC_OFF &			// Fcy output on OSC2
		POSCMD_EC );
_FWDT(	FWDTEN_OFF &			// wdt's disabled
		WINDIS_OFF ) ;
_FPOR(	FPWRT_PWR32 ) ;			// fast powerup, will need to change for ext osc
_FICD(	JTAGEN_OFF &			// jtag off and use 2nd set for ICSP
		ICS_PGD2 ) ;
#endif


union udb_fbts_byte udb_flags ;

boolean timer_5_on = 0 ;
boolean needSaveExtendedState = 0 ;
int defaultCorcon = 0 ;
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
	WORD wSP_Temp;
//	__asm__("mov WREG0,WREG15");
//	__asm__("mov wSP_Temp,WREG0");
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
	
#if (MAG_YAW_DRIFT == 1)
	udb_init_I2C2() ;
#endif
	
	udb_init_GPS() ;
	udb_init_USART() ;
	udb_init_pwm() ;
#if (USE_OSD == 1)
	udb_init_osd() ;
#endif
	
	SRbits.IPL = 0 ;	// turn on all interrupt priorities
	
	return ;
}


void udb_run(void)
{
	//  nothing else to do... entirely interrupt driven
	while (1)
	{
		// pause cpu counting timer while not in an ISR
		indicate_loading_main ;
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
	needSaveExtendedState = inUse ;
	return ;
}


void udb_a2d_record_offsets(void)
{
	// almost ready to turn the control on, save the input offsets
	UDB_XACCEL.offset = UDB_XACCEL.value ;
	udb_xrate.offset = udb_xrate.value ;
	UDB_YACCEL.offset = UDB_YACCEL.value ;
	udb_yrate.offset = udb_yrate.value ;
	UDB_ZACCEL.offset = UDB_ZACCEL.value GRAVITY_SIGN ((int)(2*GRAVITY)) ;  // GRAVITY is measured in A-D/2 units
	udb_zrate.offset = udb_zrate.value ;									// The sign is for inverted boards
#ifdef VREF
	udb_vref.offset = udb_vref.value ;
#endif
	return ;
}


void udb_servo_record_trims(void)
{
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		udb_pwTrim[i] = udb_pwIn[i] ;
	
	return ;
}


// saturation logic to maintain pulse width within bounds
int udb_servo_pulsesat ( long pw )
{
	if ( pw > SERVOMAX ) pw = SERVOMAX ;
	if ( pw < SERVOMIN ) pw = SERVOMIN ;
	return (int)pw ;
}
