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


//	routines to drive the PWM pins for the servos,
//	assumes the use of the 80MHz input.

// want to get 25 milliseconds timeout for 40Hz frame rate
//  and to get 20 milliseconds timeout for 50Hz frame rate later
// servos are all driven off T2 in this code (0.2uSec resolution)
//
// The interrupt handler creates the frame rate with a counter
//
// USEC_DIV is factor to divide 32bit tagUSec to get uSec's (0-64k)
// FRAME_40HZ_CNT number of T3 interrupts at FRAME_40HZ_PR to get 25 mSec (40Hz frame rate)
// FRAME_50HZ_CNT number of T3 interrupts at FRAME_50HZ_PR to get 20 mSec (50Hz frame rate)
// FRAME_20HZ_CNT number of T3 interrupts at FRAME_20HZ_PR to get 50 mSec (20Hz count rate)
// FRAME_CNT is the roll over and clear of iFrameCounter
// FRAME_PRE is the T3 pre-load value
// FRAME_ROLL is the roll over for iFrameCounter

#define USEC_DIV 40
#define FRAME_40HZ_CNT 20
#define FRAME_40HZ_PR 50000
#define FRAME_50HZ_CNT 16
#define FRAME_50HZ_PR 50000
#define FRAME_20HZ_CNT 40
#define FRAME_20HZ_PR 50000
#define FRAME_ROLL 80
#define FRAME_CNT FRAME_40HZ_CNT
#define FRAME_PRE FRAME_40HZ_PR

#define TMR3_PERIOD FRAME_PRE

#include "libUDB_internal.h"

#if (BOARD_TYPE == ASPG_BOARD)

int udb_pwOut[65] ;	// pulse widths for servo outputs

int twentyHertzCounter = 0 ;
int iFrameCounter = 0;
union longlongww tagUSec;		// top 10 bits come from else were ie gps or gcs
union longlongww tagUSec_x40;	// this + t3 = cpu cyles

void udb_init_pwm( void )	// initialize the PWM
{
	int i;
	for (i=0; i <= NUM_OUTPUTS; i++)
		udb_pwOut[i] = 0;
	
#if (NORADIO == 1)
	udb_flags._.radio_on = 1 ;
#endif
	
// does not use PWM module, uses the output compare module instead
// control enabled else were - just config to T2, no fault, disable in idle mode
	OC1CON = 0, OC2CON = 0, OC3CON = 0, OC4CON = 0;
	OC5CON = 0, OC6CON = 0, OC7CON = 0, OC8CON = 0 ;  // disable
	
	OC1R = OC2R = OC3R = OC4R = OC5R = OC6R = OC7R = OC8R = 0 ;  // no first pulse
	OC1RS = OC2RS = OC3RS = OC4RS = OC5RS = OC6RS = OC7RS = OC8RS = 0 ; // initial pulse
	
	IPC0bits.OC1IP = 0x05; // Set Output Compare 1 Interrupt Priority Level
	IFS0bits.OC1IF = 0; // Clear Output Compare 1 Interrupt Flag
	IEC0bits.OC1IE = 1; // Enable Output Compare 1 interrupt

	IPC1bits.OC2IP = 0x05; // Set Output Compare 2 Interrupt Priority Level
	IFS0bits.OC2IF = 0; // Clear Output Compare 2 Interrupt Flag
	IEC0bits.OC2IE = 1; // Enable Output Compare 2 interrupt

	IPC6bits.OC3IP = 0x05; // Set Output Compare 3 Interrupt Priority Level
	IFS1bits.OC3IF = 0; // Clear Output Compare 3 Interrupt Flag
	IEC1bits.OC3IE = 1; // Enable Output Compare 3 interrupt

	IPC6bits.OC4IP = 0x05; // Set Output Compare 4 Interrupt Priority Level
	IFS1bits.OC4IF = 0; // Clear Output Compare 4 Interrupt Flag
	IEC1bits.OC4IE = 1; // Enable Output Compare 4 interrupt

	IPC10bits.OC5IP = 0x05; // Set Output Compare 5 Interrupt Priority Level
	IFS2bits.OC5IF = 0; // Clear Output Compare 5 Interrupt Flag
	IEC2bits.OC5IE = 1; // Enable Output Compare 5 interrupt

	IPC10bits.OC6IP = 0x05; // Set Output Compare 6 Interrupt Priority Level
	IFS2bits.OC6IF = 0; // Clear Output Compare 6 Interrupt Flag
	IEC2bits.OC6IE = 1; // Enable Output Compare 6 interrupt

	IPC10bits.OC7IP = 0x05; // Set Output Compare 7 Interrupt Priority Level
	IFS2bits.OC7IF = 0; // Clear Output Compare 7 Interrupt Flag
	IEC2bits.OC7IE = 1; // Enable Output Compare 7 interrupt

	IPC11bits.OC8IP = 0x05; // Set Output Compare 8 Interrupt Priority Level
	IFS2bits.OC8IF = 0; // Clear Output Compare 8 Interrupt Flag
	IEC2bits.OC8IE = 1; // Enable Output Compare 8 interrupt

	TMR3 = 0 ; 				// initialize timer
	PR3 = TMR3_PERIOD ;		// set period register
	T3CONbits.TCKPS = 0 ;	// prescaler = 0 option, counts at Tcy
	T3CONbits.TCS = 0 ;		// use the internal clock
	_T3IP = 3 ;				//
	_T3IF = 0 ;				// clear the interrupt
	_T3IE = 1 ;				// enable the interrupt
	T3CONbits.TON = 1 ;		// turn on timer 3
	
	return ;
}


void udb_set_action_state(boolean newValue)
{
	_LATE4 = newValue ;
}


void __attribute__((__interrupt__,__no_auto_psv__)) _T3Interrupt(void) 
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	_T3IF = 0 ;		// clear the interrupt
	tagUSec_x40.WW += TMR3_PERIOD;

	if ( iFrameCounter++ >= FRAME_ROLL )
		iFrameCounter = 0;
	else ;

	//	Executes whatever needs to be done every 20 milliseconds
	//	This is a good place to compute pulse widths for servos.
	if ( !(iFrameCounter % FRAME_50HZ_CNT) )	// has to == 0
	{
		OC1RS = udb_pwOut[1] ;
		OC2RS = udb_pwOut[2] ;
		OC3RS = udb_pwOut[3] ;
		OC4RS = udb_pwOut[4] ;
		OC5RS = udb_pwOut[5] ;
		OC6RS = udb_pwOut[6] ;
		OC7RS = udb_pwOut[7] ;
		OC8RS = udb_pwOut[8] ;
	}

	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.

	if ( !(iFrameCounter % FRAME_40HZ_CNT) )	// has to == 0
	{
#if ( NORADIO == 0 )
		twentyHertzCounter++ ;
		if ( twentyHertzCounter >= 2 )
		{
			if ( failSafePulses == 0 )
			{
				udb_flags._.radio_on = 0 ;
				LED_GREEN = LED_OFF ;
			}
			else if ( failSafePulses >= 2 )
			{
				udb_flags._.radio_on = 1 ;
				LED_GREEN = LED_ON ;
			}
			twentyHertzCounter = 0 ;
			failSafePulses = 0 ;
		}

		udb_servo_callback_prepare_outputs() ;
#endif
	}
	
	// interrupt_restore_extended_state ;
	return ;
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC1Interrupt(void)
{
	IFS0bits.OC1IF = 0; // Clear Output Compare 1 Interrupt Flag
	OC1CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC2Interrupt(void)
{
	IFS0bits.OC2IF = 0; // Clear Output Compare 2 Interrupt Flag
	OC2CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC3Interrupt(void)
{
	IFS1bits.OC3IF = 0; // Clear Output Compare 3 Interrupt Flag
	OC3CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC4Interrupt(void)
{
	IFS1bits.OC4IF = 0; // Clear Output Compare 4 Interrupt Flag
	OC4CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC5Interrupt(void)
{
	IFS2bits.OC5IF = 0; // Clear Output Compare 5 Interrupt Flag
	OC5CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC6Interrupt(void)
{
	IFS2bits.OC6IF = 0; // Clear Output Compare 6 Interrupt Flag
	OC6CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC7Interrupt(void)
{
	IFS2bits.OC7IF = 0; // Clear Output Compare 7 Interrupt Flag
	OC7CON = 0;			// TODO: need to write actual pin handler
}

void __attribute__((__interrupt__,__no_auto_psv__)) _OC8Interrupt(void)
{
	IFS2bits.OC8IF = 0; // Clear Output Compare 8 Interrupt Flag
	OC8CON = 0;			// TODO: need to write actual pin handler
}

#endif

/* does not use PWM module, uses the output compare module instead
	OC1CONbits.OCM =
	OC2CONbits.OCM =
	OC3CONbits.OCM =
	OC4CONbits.OCM =
	OC5CONbits.OCM =
	OC6CONbits.OCM =
	OC7CONbits.OCM =
	OC8CONbits.OCM = 0 ;  // disable

	OC1R = OC2R = OC3R = OC4R = OC5R = OC6R = OC7R = OC8R = 0 ;  // no first pulse
	OC1RS = OC2RS = OC3RS = OC4RS = OC5RS = OC6RS = OC7RS = OC8RS = 0 ; // initial pulse

	OC1CONbits.OCM =
	OC2CONbits.OCM =
	OC3CONbits.OCM =
	OC4CONbits.OCM =
	OC5CONbits.OCM =
	OC6CONbits.OCM =
	OC7CONbits.OCM =
	OC8CONbits.OCM = 6 ;  // enable

	OC1CONbits.OCTSEL =
	OC2CONbits.OCTSEL =
	OC3CONbits.OCTSEL =
	OC4CONbits.OCTSEL =
	OC5CONbits.OCTSEL =
	OC6CONbits.OCTSEL =
	OC7CONbits.OCTSEL =
	OC8CONbits.OCTSEL = 1 ;  // timer 3
*/

