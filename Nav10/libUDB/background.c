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

#if (BOARD_IS_CLASSIC_UDB == 1)
#if ( CLOCK_CONFIG == CRYSTAL_CLOCK )
#define CPU_LOAD_PERCENT	16*400   // = (100 / (8192 * 2)) * (256**2)
#elif ( CLOCK_CONFIG == FRC8X_CLOCK )
#define CPU_LOAD_PERCENT	16*109   // = ((100 / (8192 * 2)) * (256**2))/3.6864
#endif
#elif ( BOARD_TYPE == ASPG_BOARD )
#define tmr1_period 		15625 // sets time period for timer 1 interrupt to 0.025 seconds
#define CPU_LOAD_PERCENT	40000	// cpu% in 1/10% = counts / (40MHz/1000) = counts / 40000
#elif (BOARD_TYPE == UDB4_BOARD)
#define CPU_LOAD_PERCENT	16*100
#endif


int timer1_counts = 0;
unsigned int cpu_timer = 0 ;
unsigned long cpu_counter = 0, old_cpu_counter = 0;

unsigned int udb_heartbeat_counter = 0 ;
#define HEARTBEAT_MAX	57600		// Evenly divisible by many common values: 2^8 * 3^2 * 5^2

unsigned int gps_timeout = 0; 
int iDCMframe = 0;
// FRAME_40HZ_CNT number of T4 interrupts at FRAME_40HZ_PR to get 25 mSec (40Hz frame rate)
// FRAME_50HZ_CNT number of T4 interrupts at FRAME_50HZ_PR to get 20 mSec (50Hz frame rate)
// FRAME_20HZ_CNT number of T4 interrupts at FRAME_20HZ_PR to get 50 mSec (20Hz count rate)
// FRAME_CNT is the roll over and clear of iFrameCounter
// FRAME_PRE is the T4 pre-load value
// FRAME_ROLL is the roll over for iDCMframe - used to be driven on servo timer
// This 40000 value also gives a very handy 1mSec timer rate

#define FRAME_40HZ_CNT 25
#define FRAME_40HZ_PR 40000
#define FRAME_50HZ_CNT 20
#define FRAME_50HZ_PR 40000
#define FRAME_20HZ_CNT 50
#define FRAME_20HZ_PR 40000
#define FRAME_ROLL 100
#define FRAME_CNT FRAME_40HZ_CNT
#define FRAME_PRE FRAME_40HZ_PR

#if ( BOARD_TYPE == ASPG_BOARD )
#define _TTRIGGERIP _T4IP
#define _TTRIGGERIF _T4IF
#define _TTRIGGERIE _T4IE
#define _TTRIGGERPR PR4
#define _TTRIGGERPv FRAME_40HZ_PR
#elif ( BOARD_TYPE == UDB4_BOARD )
#define _TTRIGGERIP _T7IP
#define _TTRIGGERIF _T7IF
#define _TTRIGGERIE _T7IE
#else
#define _TTRIGGERIP _T3IP
#define _TTRIGGERIF _T3IF
#define _TTRIGGERIE _T3IE
#endif


void udb_init_clock(void)	/* initialize timers */
{
//	TRISF = 0b1111111111101100 ;	// FIX:

	TMR1 = 0 ; 				// initialize timer
	PR1 = tmr1_period ;		// set period register
	T1CONbits.TCKPS = 2 ;	// prescaler = 64 option
	T1CONbits.TCS = 0 ;		// use the crystal to drive the clock
	_T1IP = 6 ;				// Set to 3 to improve accuracy of cpu timing
	_T1IF = 0 ;				// clear the interrupt
	_T1IE = 1 ;				// enable the interrupt
	
	T1CONbits.TON = 1 ;		// turn on timer 1

#if ( BOARD_TYPE == ASPG_BOARD )
	// Timer 5 is used to measure time spent per second in interrupt routines
	// which enables the calculation of the CPU loading.
	TMR5 = 0 ; 				// initialize timer
	PR5 = 0xffff ; 			// initialize timer - 0 not valid for PR in these timers
	T5CONbits.TCKPS = 0 ;	// prescaler = 1 option, no lost counts this way
	T5CONbits.TCS = 0 ;	    // use the crystal to drive the clock
	_T5IE = 1 ;				// enable the interrupt
	// Timer 5 will be turned on in interrupt routines and turned off in main()
	T5CONbits.TON = 0 ;		// turn off timer 5
//	timer_5_on = 0;

	TMR4 = 0 ; 				// initialize timer
	_TTRIGGERPR = _TTRIGGERPv;	// set period register
	T4CONbits.TCKPS = 0 ;	// prescaler = 0 option, counts at Tcy
	T4CONbits.TCS = 0 ;		// use the internal clock
	T4CONbits.TON = 1 ;		// turn on timer 3


#else
	// Timer 5 is used to measure time spent per second in interrupt routines
	// which enables the calculation of the CPU loading.
	TMR5 = 0 ; 				// initialize timer
	T5CONbits.TCKPS = 3 ;	// prescaler = 256 option
	T5CONbits.TCS = 0 ;	    // use the crystal to drive the clock
	_T5IE = 0 ;				// disable the interrupt
	
	// Timer 5 will be turned on in interrupt routines and turned off in main()
	T5CONbits.TON = 0 ;		// turn off timer 5
	timer_5_on = 0;
#endif
	// The TTRIGGER interrupt (T3, T4 or T7 depending on the board) is used to
	// trigger background tasks such as navigation processing after binary data
	// is received from the GPS.
	_TTRIGGERIP = 2 ;		// priority 2
	_TTRIGGERIF = 0 ;		// clear the interrupt
	_TTRIGGERIE = 1 ;		// enable the interrupt
	
	return ;
}

// This high priority interrupt is the Heartbeat of libUDB.
// excute whatever needs to run in the background, once every 0.025 seconds
void __attribute__((__interrupt__,__no_auto_psv__)) _T1Interrupt(void) 
{
	// interrupt_save_extended_state ;
	_T1IF = 0 ;			// clear the interrupt
	
	indicate_loading_inter ;

	// capture cpu_timer once per second.
	if (udb_heartbeat_counter % 40 == 0)
	{
#if ( BOARD_TYPE == ASPG_BOARD )
		_DI();
		cpu_counter += TMR5 ;			// add last bit + calc %
		cpu_timer = (int)((cpu_counter / CPU_LOAD_PERCENT));
		old_cpu_counter = cpu_counter;
		cpu_counter = 0;				// clear it after
		T5CONbits.TON = 0 ;		// turn off timer 5 
		TMR5 = 0 ;				// reset timer 5 to 0
		T5CONbits.TON = 1 ;		// turn on timer 5
		_EI();
#else
		T5CONbits.TON = 0 ;             // turn off timer 5
		cpu_timer = _cpu_timer ;// snapshot the load counter
		_cpu_timer = 0 ;                // reset the load counter
		T5CONbits.TON = 1 ;             // turn on timer 5
#endif
	}
	
	// Call the periodic callback at 2Hz
	if (udb_heartbeat_counter % 20 == 0)
	{
		udb_background_callback_periodic() ;
	}
	
	udb_heartbeat_counter = (udb_heartbeat_counter+1) % HEARTBEAT_MAX;
	
	// interrupt_restore_extended_state ;
	return ;
}

#if ( BOARD_TYPE == ASPG_BOARD )
void __attribute__((__interrupt__,__no_auto_psv__)) _T5Interrupt(void)
{
	_T5IF = 0 ;				// clear the interrupt
	cpu_counter += 0x10000;

}
#endif


#if (BOARD_TYPE == ASPG_BOARD )
void __attribute__((__interrupt__,__no_auto_psv__)) _T4Interrupt(void)
#elif ( BOARD_TYPE == UDB4_BOARD )
void __attribute__((__interrupt__,__no_auto_psv__)) _T7Interrupt(void) 
#else
void __attribute__((__interrupt__,__no_auto_psv__)) _T3Interrupt(void) 
#endif
//  process TRIGGER interrupt
{
	// interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	_TTRIGGERIF = 0 ;			// clear the interrupt
	
	iDCMframe++; // , gps_timeout++;

	if ( iDCMframe >= FRAME_ROLL )
		iDCMframe = 0;
	else ;

	if ( gps_timeout == 10000 )
			udb_background_callback_triggered(), gps_timeout = 0;
	else ;

	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.

	if ( !(iDCMframe % FRAME_40HZ_CNT) )	// has to == 0
	{
#if ( NORADIO == 0 )
#if (BOARD_TYPE == ASPG_BOARD)
// changed to run on T4 lower priority
		udb_servo_callback_prepare_outputs() ;
#endif
#endif
	}
	
	// interrupt_restore_extended_state ;
	return ;
}


void udb_background_trigger(void)
{
//	udb_background_callback_triggered() ;
	gps_timeout = 10000;	// will be called within one mS
	return ;
}


unsigned char udb_cpu_load(void)
{
#if ( BOARD_TYPE == ASPG_BOARD )
	return (unsigned char)cpu_timer/10;
#else
return (unsigned char)(__builtin_muluu(cpu_timer, CPU_LOAD_PERCENT) >> 16) ;
#endif
}
