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
#include <stdio.h>

#if (BOARD_TYPE == ASPG_BOARD)

//	Measure the pulse widths of the servo channel inputs from the radio.
//	The dsPIC makes this rather easy to do using its capture feature.
//	One of the channels is also used to validate pulse widths to detect loss of radio.
//	The pulse width inputs can be directly converted to units of pulse width outputs to control
//	the servos by simply dividing by 2. ** CHANGED ** now Q15

int IMPORTANTz udb_pwIn[65]; 		// pulse widths of radio inputs ** CHANGED ** now Q15
int IMPORTANTz udb_pwTrim[65];		// initial pulse widths for trimming ** CHANGED ** now Q15

int failSafePulses = 0 ;
WORD	T2_OF;						// count of T2 wraps
// unsigned char ucPWMTest[30];

extern LEDCTRL	GreenLED;			// radio state - set in states.c

// in the macro below T=Pin type, P=Port number, B=Bit, G=Global index, L=Length, S=Spare, LP0=.iPrivate[0], LP1=.iPrivate[1]
// what these should do is described in the first page of Mixer.xls - work in progress
#define RC_PIN( T, P, B, G, L)      { 0, 0, 0, 6, ((FAILSAFE_INPUT_CHANNEL-1) == (G-RC_START) ? 1 : 0), 0, 0, T, P, B, G, L }
#define RC_SERVO( T, P, B, G, L, S) { 0, 0, 0, 0, 0,                                                    0, 0, T, P, B, G, L, S }
#define ANALOG( T, P, B, G, P0, P1, P2, P3) { 0, 0, 0, 0, 0, 0, 0, T, P, B, G, 0, 0, {.iPrivate = { P0, P1, P2, P3 }} }
PIN NEAR_BUF DIO[48] = {
		RC_PIN(0,0,0,0,0),				// unused
		RC_PIN(12,3,8,RC_START+0,0),	//  1 - RC1
		RC_PIN(12,3,9,RC_START+1,0),	//  2 - RC2
		RC_PIN(12,3,10,RC_START+2,0),	//  3 - RC3
		RC_PIN(12,3,11,RC_START+3,0),	//  4 - RC4
		RC_PIN(12,3,12,RC_START+4,0),	//  5 - RC5
		RC_PIN(12,3,13,RC_START+5,0),	//  6 - RC6
		RC_PIN(12,3,14,RC_START+6,0),	//  7 - RC7
		RC_PIN(16,3,15,RC_START+7,1),	//  8 - RC8
		RC_SERVO( 6,3, 0,1,0,1),		//  9 - SERVO1
		RC_SERVO( 6,3, 1,2,0,1),		// 10 - SERVO2
		RC_SERVO( 6,3, 2,3,0,1),		// 11 - SERVO3
		RC_SERVO( 6,3, 3,4,0,1),		// 12 - SERVO4
		RC_SERVO( 6,3, 4,5,0,1),		// 13 - SERVO5
		RC_SERVO( 6,3, 5,6,0,1),		// 14 - SERVO6
		RC_SERVO( 6,3, 6,7,0,1),		// 15 - SERVO7
		RC_SERVO(10,3, 7,8,1,1),		// 16 - SERVO8
		RC_PIN(19,2,4,AUX_START+8,0),	// 17 - IT1 - nominally going to put these in the pwmIn array
		RC_PIN(19,2,3,AUX_START+9,0),	// 18 - IT2
		RC_PIN(19,2,2,AUX_START+10,0),	// 19 - IT3
		RC_PIN(19,2,1,AUX_START+11,0),	// 20 - IT4
		RC_PIN(3,2,5,0,0),	// 21 - BUZZER
		RC_PIN(3,6,15,0,0),	// 22 - OUT1
		RC_PIN(3,0,14,0,0),	// 23 - ISCP1_AUX1
		RC_PIN(3,0,15,0,0),	// 24 - ISCP1_AUX2
		ANALOG(1,1,6,0, 0x0672, 0x0672, 0x0672, 0x0672),	// 25 - SAmps - TODO factor converts 0-4096 to 0-3300 mA
		ANALOG(1,1,7,0, 0x2805, 0x2805, 0x2805, 0x2805),	// 26 - SVolt - factor converts 0-4096 to 0-20500 mV
		ANALOG(1,1,0,0, 0x0672, 0x0672, 0x0672, 0x0672),	// 27 - AUX_AN1 - factor converts 0-4096 to 0-3300 mV
		ANALOG(1,1,1,0, 0x0672, 0x0672, 0x0672, 0x0672),	// 28 - AUX_AN2 - factor converts 0-4096 to 0-3300 mV
		ANALOG(1,1,3,0, 0x0672, 0x0672, 0x0672, 0x0672),	// 29 - AUX_AN3 - factor converts 0-4096 to 0-3300 mV
		ANALOG(1,1,4,0, 0x0672, 0x0672, 0x0672, 0x0672),	// 30 - AUX_AN4 - factor converts 0-4096 to 0-3300 mV
		ANALOG(1,4,2,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 31 - gyro X - eventually these scale factors will be read from EE
		ANALOG(1,0,7,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 32 - gyro Y
		ANALOG(1,4,7,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 33 - gyro Z
		ANALOG(1,0,3,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 34 - accel X
		ANALOG(1,0,3,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 35 - accel Y
		ANALOG(1,0,3,0, 0x08A0, 0x08A0, 0x08A0, 0x08A0),	// 36 - accel Z
		ANALOG(1,0,3,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 37 - mag X
		ANALOG(1,0,3,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 38 - mag Y
		ANALOG(1,0,3,0, 0x0800, 0x0800, 0x0800, 0x0800),	// 39 - mag Z
};

#define RC_INT_PRI 6

void udb_init_capture(void)
{
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		udb_pwIn[i] = udb_pwTrim[i] = 0 ;
	
	T2CON = 0;				// clear
	TMR2 = 0 ; 				// initialize timer
	PR2 = 0xffff;			// 0 not a valid value for PR on these timers
	T2CONbits.TCKPS = 1 ;	// prescaler = 8 option, count = .2 uSec
	T2CONbits.TCS = 0 ;		// use the internal clock
	T2CONbits.TON = 1 ;		// turn on timer 2
	
	_T2IP = RC_INT_PRI, _T2IF = 0, _T2IE = 1;	// enable T2 interrupt

	//	configure the capture pins
	IC1CON = 0;				// clear all
	IC1CONbits.ICTMR = 1;	// use timer 2
	IC1CONbits.ICM = 1;		// capture every edge
	
	IC8CON = IC7CON = IC6CON = IC5CON = IC4CON = IC3CON = IC2CON = IC1CON ;
	
	tRC1 = 1, tRC2 = 1, tRC3 = 1, tRC4 = 1;		// set them all as inputs
	tRC5 = 1, tRC6 = 1, tRC7 = 1, tRC8 = 1;
	
	//	set the interrupt priorities to 6, same as timer
	_IC1IP = RC_INT_PRI, _IC2IP = RC_INT_PRI, _IC3IP = RC_INT_PRI, _IC4IP = RC_INT_PRI;
	_IC5IP = RC_INT_PRI, _IC6IP = RC_INT_PRI, _IC7IP = RC_INT_PRI, _IC8IP = RC_INT_PRI ;
	
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

// Input type digital pins - see servoOut for digital output pin handler
void rc_pin( WORD wCounts, int iState, LPPIN lpTag )
{
	DWORD	dwTemp;
	WORD	wTemp;
	switch( lpTag->iType ) {
	case 13:	// 13	Single channel 50Hz PWM input, negative logic
	case 15:	// 15	Single channel 450Hz PWM input, negative logic
		if ( iState == 1)	// NOTE: invert bit and fall through
			iState = 0;
		else iState = 1;
	case 12:	// 12	Single channel 50Hz PWM input, positive logic
	case 14:	// 14	Single channel 450Hz PWM input, positive logic
		if ( iState == 1)	// pin changed to high -> start of pulse
		{
			lpTag->wPrivate[0] = wCounts;					// save value
			lpTag->wPrivate[1] = T2_OF;						// save value
		} else {		// pin changed to low -> end of pulse
			lpTag->wPrivate[2] = wCounts;					// save value
			lpTag->wPrivate[3] = T2_OF;						// save value
			dwTemp = lpTag->lPrivate[1] - lpTag->lPrivate[0];
			if ( dwTemp > 0x10000 )							// presume we have good data
				dwTemp -= 0x10000;							// because the timer is only 16 bit
			if ( dwTemp < 0 )								// and the overflow interrupt is
				dwTemp += 0x10000;							// async to counter and capture

			if (dwTemp > RC_PWM_MAX)						// limit values
				wTemp = RC_PWM_MAX;
			else if (dwTemp < RC_PWM_MIN)
					wTemp = RC_PWM_MIN;
				else {										// normal range pulse
					wTemp = dwTemp;							// only actual valid range pulse lengths
					if (lpTag->bFS_ON)
					{
						if ( --lpTag->iFS_Count == 0)
							lpTag->bFS_ON = 0, lpTag->iFS_Count = 8;
					}
				}
			if ( lpTag->bFS_ON )							// failsafe activated
			{
				switch (lpTag->iFS_CMD) {
				case 0: // ignore / not configured
				break;
				case 1: // use min
					wTemp = RC_PWM_MIN;
				break;
				case 2: // use max
					wTemp = RC_PWM_MAX;
				break;
				case 3: // center the control
					wTemp = RC_PWM_CENTER;
				break;
				case 4: // use -70%
					wTemp = RC_PWM_CENTER - ((RC_PWM_CENTER - RC_PWM_MIN) * 0.7);
				break;
				case 5: // use +70%
					wTemp = RC_PWM_CENTER + ((RC_PWM_MAX - RC_PWM_CENTER) * 0.7);
				break;
				case 6: // use recorded trim or center
					if ( lpTag->iGlobal != 0)
					{
						wTemp = (udb_pwIn[lpTag->iGlobal]/RC_PWM_Q15) + RC_PWM_CENTER;
					} else wTemp = RC_PWM_CENTER;
				break;
				case 7: // undefined - use ignore
				break;
				}
			} else lpTag->iFS_Count++;
			wTemp -= RC_PWM_CENTER;							// turn value into quasi Q15
#if (RC_PWM_Q15 == 8)
			wTemp = wTemp << 3;
#else
			wTemp *= RC_PWM_Q15;
#endif
			lpTag->qValue = wTemp;							// record it
//			if ( lpTag->bFS_EN )							// just print this one
//			{	sprintf( ucPWMTest, "%6ld, %6d\r\n", dwTemp, lpTag->qValue );
//				udb_serial_send_string( &ucPWMTest[0] );
//			};
			lpTag->iBuffer[lpTag->iIndex++] = wTemp;		// record it for history
//			if ( lpTag->iIndex > 16) lpTag->iIndex = 0; 	// wrap history (forgot its bitfield, autowrap)
			lpTag->iUpdate++;								// mark as updated
			if ( lpTag->bFS_EN )							// do old fail safe check
				if ( (lpTag->qValue > FAILSAFE_INPUT_MIN) && (lpTag->qValue < FAILSAFE_INPUT_MAX ) )
				{	failSafePulses++ ;
				} else {
					if ( udb_flags._.radio_on )
					{
						failSafePulses = 0 ;
						udb_flags._.radio_on = 0 ;
						LED_GREEN = LED_OFF ;
					};
				}
			else ;
			if ( lpTag->iGlobal != 0)
			{	udb_pwIn[lpTag->iGlobal] = wTemp;			// store in global controls too
			} else ;
		}
	break; // case 12, 13, 14 and 15
	case 17:	// 17	Multi channel 50Hz PWM input, negative logic (PPM encoders, direct connect to receivers etc)
		if ( iState == 1)	// NOTE: invert bit and fall through
			iState = 0;
		else iState = 1;
	case 16:	// 16	Multi channel 50Hz PWM input, positive logic (PPM encoders, direct connect to receivers etc)
		if ( iState == 1)	// pin changed to high -> start of pulse
		{
			lpTag->wPrivate[0] = wCounts;					// save value
			lpTag->wPrivate[1] = T2_OF;						// save value
			dwTemp = lpTag->lPrivate[0] - lpTag->lPrivate[1]; // calc space between pulses
			if ( (dwTemp > RC_PPM_SYNC) && (dwTemp < RC_PPM_MAX) )	// good sync values
				lpTag->iIndex = 1;							// also accepted as re-syncs
		} else {		// pin changed to low -> end of pulse
			lpTag->wPrivate[2] = wCounts;					// save value
			lpTag->wPrivate[3] = T2_OF;						// save value
			dwTemp = lpTag->lPrivate[1] - lpTag->lPrivate[0];
			if ( dwTemp > 0x10000 )							// presume we have good data
				dwTemp -= 0x10000;							// because the timer is only 16 bit
			if ( dwTemp < 0 )								// and the overflow interrupt is
				dwTemp += 0x10000;							// async to counter and capture

			// DONE: add checks for sync pulse, has to get index into range to store
			if ( (dwTemp > RC_PPM_SYNC) && (dwTemp < RC_PPM_MAX) )	// good sync values
				lpTag->iIndex = 1;
			else {
				if (dwTemp > RC_PWM_MAX)						// limit values
					wTemp = RC_PWM_MAX;
				else if (dwTemp < RC_PWM_MIN)
						wTemp = RC_PWM_MIN;
					else {										// normal range pulse
						wTemp = dwTemp;
						lpTag->bFS_ON = 0, lpTag->iFS_Count = 0;
					}
				wTemp -= RC_PWM_CENTER;							// turn value into quasi Q15
	#if (RC_PWM_Q15 == 8)
				wTemp = wTemp << 3;
	#else
				wTemp *= RC_PWM_Q15;
	#endif
				lpTag->qValue = wTemp;							// record it
				if ( (lpTag->iIndex >= 1) && (lpTag->iIndex <= 8) )	// must set in DIO array
				{	lpTag->iBuffer[lpTag->iIndex] = wTemp;		// record this channel
					lpTag->iUpdate++;							// mark as updated
					if ( lpTag->bFS_EN )						// do old fail safe check
						if ( (wTemp > FAILSAFE_INPUT_MIN) && (wTemp < FAILSAFE_INPUT_MAX ) )
						{	failSafePulses++ ;					// slow turn on
						} else {
							failSafePulses = 0 ;				// instant turn off
							udb_flags._.radio_on = 0 ;
							LED_GREEN = LED_OFF ;
						}
					else ;
					if ( lpTag->iGlobal != 0)					// store in global controls too
						udb_pwIn[lpTag->iGlobal + lpTag->iIndex - 1] = wTemp; // both of these 1 based
					else ;
					lpTag->iIndex++;							// next one
				}; // end of in range to store
			} // end of check for SYNC pulse
		}
	break; // end case 16 & 17
	}
}
// Timer 2 interrupt
void __attribute__((__interrupt__,__no_auto_psv__)) _T2Interrupt(void)
{
	_T2IF = 0; 	// clear the interrupt, happens .2uSec x 0x10000 = 13.1072 mSec
	T2_OF++;	// overflow's every 858.9934592 seconds (~14 minutes)
	return ;
}

// Input Channel 1
void __attribute__((__interrupt__,__no_auto_psv__)) _IC1Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC1CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC1BUF, iRC1, &DIO[RC_PIN_START + 0] );
#else
		unsigned int time ;
		time = IC1BUF;	// just need to read it
#endif
	}
	_IC1IF = 0 ; // clear the interrupt
	return ;
}


// Input Channel 2
void __attribute__((__interrupt__,__no_auto_psv__)) _IC2Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC2CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC2BUF, iRC2, &DIO[RC_PIN_START + 1] );
#else
		unsigned int time ;
		time = IC2BUF;	// just need to read it
#endif
	}
	_IC2IF = 0 ; // clear the interrupt
	return ;
}


// Input Channel 3
void __attribute__((__interrupt__,__no_auto_psv__)) _IC3Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC3CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC3BUF, iRC3, &DIO[RC_PIN_START + 2] );
#else
		unsigned int time ;
		time = IC3BUF;	// just need to read it
#endif
	}
	_IC3IF = 0 ; // clear the interrupt
	return ;
}


// Input Channel 4
void __attribute__((__interrupt__,__no_auto_psv__)) _IC4Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC4CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC4BUF, iRC4, &DIO[RC_PIN_START + 3] );
#else
		unsigned int time ;
		time = IC4BUF;	// just need to read it
#endif
	}
	_IC4IF =  0 ; // clear the interrupt
	return ;
}


// Input Channel 5
void __attribute__((__interrupt__,__no_auto_psv__)) _IC5Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC5CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC5BUF, iRC5, &DIO[RC_PIN_START + 6] );
#else
		unsigned int time ;
		time = IC5BUF;	// just need to read it
#endif
	}
	_IC5IF =  0 ; // clear the interrupt
	return ;
}


// Input Channel 6
void __attribute__((__interrupt__,__no_auto_psv__)) _IC6Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC6CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC6BUF, iRC6, &DIO[RC_PIN_START + 7] );
#else
		unsigned int time ;
		time = IC6BUF;	// just need to read it
#endif
	}
	_IC6IF =  0 ; // clear the interrupt
	return ;
}


// Input Channel 7
void __attribute__((__interrupt__,__no_auto_psv__)) _IC7Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC7CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC7BUF, iRC7, &DIO[RC_PIN_START + 5] );
#else
		unsigned int time ;
		time = IC7BUF;	// just need to read it
#endif
	}
	_IC7IF =  0 ; // clear the interrupt
	return ;
}


// Input Channel 8
void __attribute__((__interrupt__,__no_auto_psv__)) _IC8Interrupt(void)
{
	indicate_loading_inter ;
	while ( IC8CONbits.ICBNE )
	{
#if ( NORADIO == 0 )
		rc_pin( IC8BUF, iRC8, &DIO[RC_PIN_START + 4] );
#else
		unsigned int time ;
		time = IC8BUF;	// just need to read it
#endif
	}
	_IC8IF =  0 ; // clear the interrupt
	return ;
}

/* save example of old code
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

*/
/*
			if ( T2_OF == lpTag->iPrivate[1] )				// check overflow
			{
				dwTemp = wCounts - lpTag->wPrivate[0];		// simple case
				if (dwTemp < 0)								// expressly presume we have good data
					dwTemp += 0x10000;						// because this called before T2_OF
			} else {										// complex case of T2 has wrapped
				if ( T2_OF > lpTag->wPrivate[1])			// T2_OF wrap
				{
					dwTemp = (((DWORD)T2_OF << 16) + wCounts) - lpTag->lPrivate[0];
					if (dwTemp < 0)							// expressly presume we have good data
						dwTemp += 0x10000;					// because this called before T2_OF
				} else {
					wTemp = T2_OF - lpTag->wPrivate[1];		// this just works
					dwTemp = (((DWORD)wTemp << 16)+ wCounts) - lpTag->wPrivate[0];
					if (dwTemp < 0)							// expressly presume we have good data
						dwTemp += 0x10000;					// because this called before T2_OF
				}
			}
*/

#endif
