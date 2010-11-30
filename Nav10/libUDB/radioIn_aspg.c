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

#if (BOARD_TYPE == ASPG_BOARD)

//	Measure the pulse widths of the servo channel inputs from the radio.
//	The dsPIC makes this rather easy to do using its capture feature.

//	One of the channels is also used to validate pulse widths to detect loss of radio.

//	The pulse width inputs can be directly converted to units of pulse width outputs to control
//	the servos by simply dividing by 2.

int udb_pwIn[32] ;		// pulse widths of radio inputs
int udb_pwTrim[32] ;	// initial pulse widths for trimming

int failSafePulses = 0 ;
int	T2_OF;						// count of T2 wraps

unsigned int rise[NUM_INPUTS+1] ;	// rising edge clock capture for radio inputs

#define RC_PIN( T, P, B, G, L) { 0, 0, 0, 0, 0, 0, T, P, B, 0, G, L }
#define RC_START 8

PIN DIO[32] __attribute__ ((section(".myDataSection"),address(0x1300))) = {
		RC_PIN(12,3,8,RC_START+0,0),	// RC1
		RC_PIN(12,3,9,RC_START+1,0),	// RC2
		RC_PIN(12,3,10,RC_START+2,0),	// RC3
		RC_PIN(12,3,11,RC_START+3,0),	// RC4
		RC_PIN(12,3,12,RC_START+4,0),	// RC5
		RC_PIN(12,3,13,RC_START+5,0),	// RC6
		RC_PIN(12,3,14,RC_START+6,0),	// RC7
		RC_PIN(12,3,15,RC_START+7,0),	// RC8
		RC_PIN(6,3,0,1,0),				// SERVO1
		RC_PIN(6,3,1,2,0),				// SERVO2
		RC_PIN(6,3,2,3,0),				// SERVO3
		RC_PIN(6,3,3,4,0),				// SERVO4
		RC_PIN(6,3,4,5,0),				// SERVO5
		RC_PIN(6,3,5,6,0),				// SERVO6
		RC_PIN(6,3,6,7,0),				// SERVO7
		RC_PIN(6,3,7,8,0),				// SERVO8
		RC_PIN(19,2,4,RC_START+8,0),	// IT1 - nominally going to put these in the pwmIn array
		RC_PIN(19,2,3,RC_START+9,0),	// IT2
		RC_PIN(19,2,2,RC_START+10,0),	// IT3
		RC_PIN(19,2,1,RC_START+11,0),	// IT4
};

void udb_init_capture(void)
{
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		udb_pwIn[i] = udb_pwTrim[i] = 0 ;
	
	T2CON = 0;				// clear
	TMR2 = 0 ; 				// initialize timer
	T2CONbits.TCKPS = 1 ;	// prescaler = 8 option
	T2CONbits.TCS = 0 ;		// use the internal clock
	T2CONbits.TON = 1 ;		// turn on timer 2
	
	_T2IP = 1, _T2IF = 0, _T2IE = 1;	// enable T2 interrupt

	//	configure the capture pins
	IC1CON = 0;				// clear all
	IC1CONbits.ICTMR = 1;	// use timer 2
	IC1CONbits.ICM = 1;		// capture every edge
	
	IC8CON = IC7CON = IC6CON = IC5CON = IC4CON = IC3CON = IC2CON = IC1CON ;
	
	tRC1 = 1, tRC2 = 1, tRC3 = 1, tRC4 = 1;		// set them all as inputs
	tRC5 = 1, tRC6 = 1, tRC7 = 1, tRC8 = 1;
	
	//	set the interrupt priorities to 6
	_IC1IP = 6, _IC2IP = 6, _IC3IP = 6, _IC4IP = 6;
	_IC5IP = 6, _IC6IP = 6, _IC7IP = 6, _IC8IP = 6 ;
	
	//	clear the interrupts:
	_IC1IF = 0, _IC2IF = 0, _IC3IF = 0, _IC4IF = 0;
	_IC5IF = 0, _IC6IF = 0, _IC7IF = 0, _IC8IF = 0 ;
	
	//	enable the interrupts:
	if (NUM_INPUTS > 0) _IC1IE = 1 ;
	if (NUM_INPUTS > 1) _IC2IE = 1 ; 
	if (NUM_INPUTS > 2) _IC3IE = 1 ; 
	if (NUM_INPUTS > 3) _IC4IE = 1 ; 
	if (NUM_INPUTS > 4) _IC5IE = 1 ; 
	if (NUM_INPUTS > 5) _IC6IE = 1 ; 
	if (NUM_INPUTS > 6) _IC7IE = 1 ; 
	if (NUM_INPUTS > 7) _IC8IE = 1 ;
	
	return ;
}

// Timer 2 interrupt
void __attribute__((__interrupt__,__no_auto_psv__,__shadow__)) _T2Interrupt(void)
{
	_T2IF = 0 ; // clear the interrupt
	T2_OF++;
	return ;
}

// Input Channel 1
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	unsigned int time ;	
	_IC1IF = 0 ; // clear the interrupt
	while ( IC1CONbits.ICBNE )
	{
		time = IC1BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD8)
	{
		 rise[1] = time ;
	}
	else
	{
		udb_pwIn[1] = time - rise[1] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 1 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif

	return ;
}


// Input Channel 2
void __attribute__((__interrupt__,__no_auto_psv__)) _IC2Interrupt(void)
{
	unsigned int time ;
	_IC2IF = 0 ; // clear the interrupt
	while ( IC2CONbits.ICBNE )
	{
		time = IC2BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD9)
	{
		 rise[2] = time ;
	}
	else
	{
		udb_pwIn[2] = time - rise[2] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 2 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}	
#endif
	
	return ;
}


// Input Channel 3
void __attribute__((__interrupt__,__no_auto_psv__)) _IC3Interrupt(void)
{
	unsigned int time ;
	_IC3IF = 0 ; // clear the interrupt
	while ( IC3CONbits.ICBNE )
	{
		time = IC3BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD10)
	{
		 rise[3] = time ;
	}
	else
	{
		udb_pwIn[3] = time - rise[3] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 3 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 4
void __attribute__((__interrupt__,__no_auto_psv__)) _IC4Interrupt(void)
{
	unsigned int time ;
	_IC4IF =  0 ; // clear the interrupt
	while ( IC4CONbits.ICBNE )
	{
		time = IC4BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD11)
	{
		 rise[4] = time ;
	}
	else
	{
		udb_pwIn[4] = time - rise[4] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 4 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 5
void __attribute__((__interrupt__,__no_auto_psv__)) _IC5Interrupt(void)
{
	unsigned int time ;
	_IC5IF =  0 ; // clear the interrupt
	while ( IC5CONbits.ICBNE )
	{
		time = IC5BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD12)
	{
		 rise[5] = time ;
	}
	else
	{
		udb_pwIn[5] = time - rise[5] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 5 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 6
void __attribute__((__interrupt__,__no_auto_psv__)) _IC6Interrupt(void)
{
	unsigned int time ;
	_IC6IF =  0 ; // clear the interrupt
	while ( IC6CONbits.ICBNE )
	{
		time = IC6BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD13)
	{
		 rise[6] = time ;
	}
	else
	{
		udb_pwIn[6] = time - rise[6] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 6 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 7
void __attribute__((__interrupt__,__no_auto_psv__)) _IC7Interrupt(void)
{
	unsigned int time ;
	_IC7IF =  0 ; // clear the interrupt
	while ( IC7CONbits.ICBNE )
	{
		time = IC7BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD14)
	{
		 rise[7] = time ;
	}
	else
	{
		udb_pwIn[7] = time - rise[7] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 7 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}


// Input Channel 8
void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
{
	unsigned int time ;
	_IC8IF =  0 ; // clear the interrupt
	while ( IC8CONbits.ICBNE )
	{
		time = IC8BUF ;
	}
	
#if ( NORADIO == 0 )
	if (PORTDbits.RD15)
	{
		 rise[8] = time ;
	}
	else
	{
		udb_pwIn[8] = time - rise[8] ;
		
#if ( FAILSAFE_INPUT_CHANNEL == 8 )
		if ( (udb_pwIn[FAILSAFE_INPUT_CHANNEL] > FAILSAFE_INPUT_MIN) && (udb_pwIn[FAILSAFE_INPUT_CHANNEL] < FAILSAFE_INPUT_MAX ) )
		{
			failSafePulses++ ;
		}
		else
		{
			failSafePulses = 0 ;
			udb_flags._.radio_on = 0 ;
			LED_GREEN = LED_OFF ;
		}
#endif
	
	}
#endif
	
	return ;
}



#endif
