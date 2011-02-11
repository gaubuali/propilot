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
// This 40000 value also gives a very handy 1mSec timer rate

#define USEC_DIV 40
#define FRAME_40HZ_CNT 25
#define FRAME_40HZ_PR 40000
#define FRAME_50HZ_CNT 20
#define FRAME_50HZ_PR 40000
#define FRAME_20HZ_CNT 50
#define FRAME_20HZ_PR 40000
#define FRAME_ROLL (100*4)
#define FRAME_CNT FRAME_40HZ_CNT
#define FRAME_PRE FRAME_40HZ_PR
#define SERVO_OUT_OFFSET 1

// this define sets the allowance for interrupt latency in PPM outputs
// the 4017 clk input does not care how long the signal is high for
// it only cares about rising edges, and we get the complete interrupt
// on the falling edge of the signal - in order to make the outputs be
// the actual time we want we have to start the following pulse at exactly
// the right time, therefore we must end the previous one in time to
// do all the calculations for the following one before that happens.
// unlikely to work below 100.
#define PPM_LATENCY 200
// set sync length, 18000 counts = 3.6ms
#define PPM_SYNC_COUNTS 18000

#define TMR3_PERIOD FRAME_PRE

#include "libUDB_internal.h"

#if (BOARD_TYPE == ASPG_BOARD)

int IMPORTANT udb_pwOut[65] = {0}; // pulse widths for servo outputs

int twentyHertzCounter = 0;
int iFrameCounter = 0;
union longlongww tagUSec; // top 10 bits come from else were ie gps or gcs
union longlongww tagUSec_x40; // this + t3 = cpu cyles
DWORD dwMilliSec; // milliseconds counter, roll over ~= 49.7 days

#define DO_INT_PRI 5

extern LEDCTRL GreenLED;
int LED_Update(LPLEDCTRL, int);

void udb_init_pwm(void) // initialize the PWM
{
	int i;
	for (i = 1; i < 65; i++)
		udb_pwOut[i] = 0;

	for (i = 9; i <= 16; i++)
		udb_pwOut[i] = 7700 + i;

#if (NORADIO == 1)
	udb_flags._.radio_on = 1;
#endif

	// does not use PWM module, uses the output compare module instead
	// control enabled else were - just config to T2, no fault, disable in idle mode
	OC1CON = 0, OC2CON = 0, OC3CON = 0, OC4CON = 0;
	OC5CON = 0, OC6CON = 0, OC7CON = 0, OC8CON = 0; // disable

	OC1R = OC2R = OC3R = OC4R = OC5R = OC6R = OC7R = OC8R = 0; // no first pulse
	OC1RS = OC2RS = OC3RS = OC4RS = OC5RS = OC6RS = OC7RS = OC8RS = 0; // initial pulse

	IPC0bits.OC1IP = DO_INT_PRI; // Set Output Compare 1 Interrupt Priority Level
	IFS0bits.OC1IF = 0; // Clear Output Compare 1 Interrupt Flag
	IEC0bits.OC1IE = 1; // Enable Output Compare 1 interrupt

	IPC1bits.OC2IP = DO_INT_PRI; // Set Output Compare 2 Interrupt Priority Level
	IFS0bits.OC2IF = 0; // Clear Output Compare 2 Interrupt Flag
	IEC0bits.OC2IE = 1; // Enable Output Compare 2 interrupt

	IPC6bits.OC3IP = DO_INT_PRI; // Set Output Compare 3 Interrupt Priority Level
	IFS1bits.OC3IF = 0; // Clear Output Compare 3 Interrupt Flag
	IEC1bits.OC3IE = 1; // Enable Output Compare 3 interrupt

	IPC6bits.OC4IP = DO_INT_PRI; // Set Output Compare 4 Interrupt Priority Level
	IFS1bits.OC4IF = 0; // Clear Output Compare 4 Interrupt Flag
	IEC1bits.OC4IE = 1; // Enable Output Compare 4 interrupt

	IPC10bits.OC5IP = DO_INT_PRI; // Set Output Compare 5 Interrupt Priority Level
	IFS2bits.OC5IF = 0; // Clear Output Compare 5 Interrupt Flag
	IEC2bits.OC5IE = 1; // Enable Output Compare 5 interrupt

	IPC10bits.OC6IP = DO_INT_PRI; // Set Output Compare 6 Interrupt Priority Level
	IFS2bits.OC6IF = 0; // Clear Output Compare 6 Interrupt Flag
	IEC2bits.OC6IE = 1; // Enable Output Compare 6 interrupt

	IPC10bits.OC7IP = DO_INT_PRI; // Set Output Compare 7 Interrupt Priority Level
	IFS2bits.OC7IF = 0; // Clear Output Compare 7 Interrupt Flag
	IEC2bits.OC7IE = 1; // Enable Output Compare 7 interrupt

	IPC11bits.OC8IP = DO_INT_PRI; // Set Output Compare 8 Interrupt Priority Level
	IFS2bits.OC8IF = 0; // Clear Output Compare 8 Interrupt Flag
	IEC2bits.OC8IE = 1; // Enable Output Compare 8 interrupt

	TMR3 = 0; // initialize timer
	PR3 = TMR3_PERIOD; // set period register
	T3CONbits.TCKPS = 0; // prescaler = 0 option, counts at Tcy
	T3CONbits.TCS = 0; // use the internal clock
	_T3IP = DO_INT_PRI; // Interrupt Priority Level
	_T3IF = 0; // clear the interrupt
	_T3IE = 1; // enable the interrupt
	T3CONbits.TON = 1; // turn on timer 3

	return;
}

void udb_set_action_state(boolean newValue) {
	_LATE4 = newValue;
}

// Output type digital pins - see radioIn for digital input pin handler
// 6	Single channel 50Hz PWM output, open drain disabled
// 7	Single channel 50Hz PWM output, open drain enabled (normally use this if you can)
// 8	Single channel 450Hz PWM output, open drain disabled
// 9	Single channel 450Hz PWM output, open drain enabled (normally use this)
// 10	Multi channel 50Hz PWM output, open drain disabled (4017's)
// 11	Multi channel 50Hz PWM output, open drain enabled (4017's normally use this)
//
// iState <= zero if called from OC interrupt, > zero called from T3 interrupt
//			T3 interrupt call used to re-start the sequence for multi-channel outputs
//			OR make sure 450Hz single channel is running (OCxCON != zero)
//			OR start the single pulse output for single channel 50Hz output
// iState = 1 for no assigned reset pin, supply exactly 10 pulses with last >3.5 mSec
//				this also means iGlen MUST be 10 and last length will be calculated
// iSpare contains the key for reset pin, = 1 for no reset pin
//			2 or -2 = IT1 (RCx) reset, 3 or -3 = IT2 (RCx) for reset,
//			4 or -4 = IT4 (RC1) reset, 5 or -5 = IT3 (RC2) for reset, 
//			6 or -6 = Digital9 (RA14), 7 or -7 = Digital10 (RA15) for reset, 
//			8 or -8 = OUT1 (RG15)    , 9 or -9 = BUZZER (RB5) for reset, 
//

void do_pin(int iState, LPPIN lpTag, LPOCM lpOCModule) {
	DWORD dwTemp;
	WORD wTemp, wTemp2;
	indicate_loading_inter;

	wTemp2 = udb_pwOut[lpTag->iGlobal]; // get PWM on time
	if (wTemp2 == 0) // input invalid so don't do anything
		return;
	else;

	switch (lpTag->iType) {
		case 6: // 6	Single channel 50Hz PWM output, open drain disabled
		case 7: // 7	Single channel 50Hz PWM output, open drain enabled (normally use this if you can)
			lpOCModule->OCCON = 0; // turn off
			if (iState > 0) // only do it when called from t3 interrupt
			{
				_DI();
				wTemp = TMR2 + 5;
				lpOCModule->OCR = wTemp; // turn on 15 x 8 Tcy from now
				wTemp += wTemp2;
				lpOCModule->OCRS = wTemp; // turn off time
				lpOCModule->OCCON = 4; // delayed one shot mode
				_EI();
			};
			break; // end case 6 + 7
		case 8: // 8	Single channel 450Hz PWM output, open drain disabled
		case 9: // 9	Single channel 450Hz PWM output, open drain enabled (normally use this)
			// module not running or called from OC interrupt - ignore calls from T3 once started
			if ((lpOCModule->OCCON == 0) || (iState < 0)) { // delay calculated to make total PWM period at least 2222 uSec (450Hz)
				// that works out to 11111 T2 counts - just over the 2.2 mSec servo out max
				// techically it will always be a little slower because of interrupt latency
				lpOCModule->OCCON = 0; // turn off
				wTemp = 11111 - wTemp2; // total length, adjust this constant
				if (wTemp < 5) // to allow for interrupt latency
					wTemp = 5; // min delay time
				else;
				_DI(); // disable interrupts while
				wTemp += TMR2; // actually setting these registers
				lpOCModule->OCR = wTemp; // turn on time
				wTemp += wTemp2;
				lpOCModule->OCRS = wTemp; // turn off time
				lpOCModule->OCCON = 4; // delayed one shot mode
				_EI(); // re-enable
			};
			break; // end case 8 + 9
		case 10: // 10	Multi channel 50Hz PWM output, open drain disabled (4017's)
		case 11: // 11	Multi channel 50Hz PWM output, open drain enabled (4017's normally use this)
			switch (iState) { // depends on reset pin what we do
				case 0:
				case 1: // ppm output with no reset signal, once started keeps going
					if (lpOCModule->OCCON != 0) // module is running - so ignore's call from T3 once started
						break;
					else;
				case -1: // restart sequence at begining
					lpOCModule->OCCON = 0; // turn off
					if (lpTag->iIndex == 0) { // soft resync - as there is no reset pin this only happens one time
						wTemp2 = PPM_SYNC_COUNTS; // do a sync pulse
						wTemp = TMR2 + 20; // R - when we actually start pulse
						lpTag->wPrivate[0] = wTemp; // save absolute start time
						lpTag->wPrivate[1] = T2_OF; // save absolute start time
						lpTag->dwPrivate[1] = lpTag->dwPrivate[0] + wTemp2; // store absolute start time
						lpTag->dwPrivate[1] -= 100000L; // store absolute start time
						lpTag->wBuffer[0] = wTemp; // start time of next pulse = len this one
						goto PPM_NO_RESET; // start it up
					} else
						if (lpTag->iIndex == 9) { // variable length pulse to get us up to 20ms - sync pulse length
						lpTag->iIndex = 10;
						dwTemp = 100000L - (lpTag->dwPrivate[0] - lpTag->dwPrivate[1]);
						if (dwTemp < (PPM_SYNC_COUNTS + PPM_LATENCY)) // going to be a problem, not enough counts for delay
							dwTemp = PPM_LATENCY + 1; // use min possible
						else dwTemp -= PPM_SYNC_COUNTS; // leave this much time to calc delay
						lpTag->dwPrivate[0] += dwTemp; // add to start time
						wTemp = lpTag->wBuffer[0]; // R - get short version
						wTemp2 = wTemp + dwTemp; // add actual start time
						lpTag->wBuffer[0] = wTemp2; // start time of next pulse = len this one
						wTemp2 -= PPM_LATENCY; // RS value with grace for interrupt overhead
					} else
						if (lpTag->iIndex == 10) { // sync pulse length - should be exact unless the 9th did not have enough counts available
PPM_NO_RESET:
						lpTag->iIndex = 1; // and back to begining
						dwTemp = 100000L - (lpTag->dwPrivate[0] - lpTag->dwPrivate[1]); // 20mSec - duration so far
						if (dwTemp < PPM_SYNC_COUNTS) // going to be a problem, not enough counts for delay
							dwTemp = PPM_SYNC_COUNTS; // use min possible
						else; // leave this much time to calc delay
						lpTag->dwPrivate[0] += dwTemp; // add to start time - should make exactly 100k counts
						wTemp = lpTag->wBuffer[0]; // R - get short version
						wTemp2 = wTemp + dwTemp; // add actual start time
						lpTag->wBuffer[0] = wTemp2; // start time of next pulse = len this one
						wTemp2 -= PPM_LATENCY; // RS value with grace for interrupt overhead
						lpTag->dwPrivate[1] = lpTag->dwPrivate[0]; // store absolute start time
					} else {
						wTemp = lpTag->iGlobal + lpTag->iIndex - 1; // both 1 based
						wTemp2 = udb_pwOut[wTemp]; // get PWM on time
						lpTag->dwPrivate[0] += wTemp2; // add to start time
						wTemp = lpTag->wBuffer[0]; // R - get short version
						wTemp2 += wTemp; // add actual start time
						lpTag->wBuffer[0] = wTemp2; // start time of next pulse = len this one
						wTemp2 -= PPM_LATENCY; // RS value with grace for interrupt overhead
						lpTag->iIndex++; // point to next one
					}
					_DI(); // disable interrupts while
					lpOCModule->OCR = wTemp; // turn on time
					lpOCModule->OCRS = wTemp2; // turn off time
					lpOCModule->OCCON = 4; // delayed one shot mode
					_EI(); // re-enable
					break; // end case 1 & -1 (no reset pin)
				case 2: // IT1 reset pin
					oIT1 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oIT1 = 0; // release reset on 4017, restart index
				case -2:
					goto PPM_WITH_RESET;
					break; // end iState case 2 + -2
				case 3: // IT2 reset pin
					oIT2 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oIT2 = 0; // release reset on 4017
				case -3:
					goto PPM_WITH_RESET;
					break; // end iState case 3 + -3
				case 4: // IT3 reset pin
					oIT3 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oIT3 = 0; // release reset on 4017
				case -4:
					goto PPM_WITH_RESET;
					break; // end iState case 4 + -4
				case 5: // IT4 reset pin
					oIT4 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oIT4 = 0; // release reset on 4017
				case -5:
					goto PPM_WITH_RESET;
					break; // end iState case 5 + -5
				case 6: // DIGITAL9 reset pin
					oDIGITAL9 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oDIGITAL9 = 0; // release reset on 4017
				case -6:
					goto PPM_WITH_RESET;
					break; // end iState case 6 + -6
				case 7: // DIGITAL10 reset pin
					oDIGITAL10 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oDIGITAL10 = 0; // release reset on 4017
				case -7:
					goto PPM_WITH_RESET;
					break; // end iState case 7 + -7
				case 8: // OUT1 / Digital4 reset pin
					oDIGITAL4 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oDIGITAL4 = 0; // release reset on 4017
				case -8:
					goto PPM_WITH_RESET;
					break; // end iState case 8 + -8
				case 9: // Buzzer / AN5 reset pin
					oBUZZER1 = 1; // reset on 4017
					lpTag->iIndex = 1;
					oBUZZER1 = 0; // release reset on 4017
				case -9:
					PPM_WITH_RESET :
							lpOCModule->OCCON = 0; // turn off
					if (lpTag->iIndex == 1) {
						wTemp = TMR2 + 10; // R - when we actually start pulse
						lpTag->wPrivate[2] = wTemp; // save absolute start time
						lpTag->wPrivate[3] = T2_OF; // save absolute start time
						wTemp2 += wTemp; // add actual start time
						lpTag->wBuffer[0] = wTemp2; // start time of next pulse = len this one
						wTemp2 -= PPM_LATENCY; // RS value with grace for interrupt overhead
						lpTag->iIndex++;
						_DI(); // disable interrupts while
						lpOCModule->OCR = wTemp; // turn on time
						lpOCModule->OCRS = wTemp2; // turn off time
						lpOCModule->OCCON = 4; // delayed one shot mode
						_EI(); // re-enable
					} else
						if (lpTag->iIndex <= 8) {
						wTemp2 = udb_pwOut[lpTag->iGlobal + lpTag->iIndex - 1]; // get PWM on time
						wTemp = lpTag->wBuffer[0]; // start time of next pulse = len this one
						wTemp2 += wTemp; // add actual start time
						lpTag->wBuffer[0] = wTemp2; // start time of next pulse = len this one
						wTemp2 -= PPM_LATENCY; // RS value with grace for interrupt overhead
						lpTag->iIndex++;
						_DI(); // disable interrupts while
						lpOCModule->OCR = wTemp; // turn on time
						lpOCModule->OCRS = wTemp2; // turn off time
						lpOCModule->OCCON = 4; // delayed one shot mode
						_EI(); // re-enable
					};
					break; // end iState case 9 + -9
				default:
					break; // end iState default
			}
			break; // end case 10 + 11
	}
}

void udb_gyro_autoZero(void) {
	oAZ_Y = oAZ_XZ = 1; // turn on gyro AZ

}
LEDCTRL ThrottleLed;

// this interrupt runs every 1mSec with 80MHz osc and 40000 preload

void __attribute__((__interrupt__, __no_auto_psv__)) _T3Interrupt(void) {
	// interrupt_save_extended_state ;
	//	WORD	wTemp;

	indicate_loading_inter;
	_T3IF = 0; // clear the interrupt
	tagUSec_x40.WW += TMR3_PERIOD;

	dwMilliSec++, iFrameCounter++;

	if (oAZ_Y || oAZ_XZ)
		oAZ_Y = oAZ_XZ = 0; // turn off gyro AZ
	else;

	if (EE_Write_Timer) // simple counter that is decremented to 0 in T3 interrupt
		EE_Write_Timer--;
	if (I2C_Timeout > 0) // simple counter that is decremented to 0 in T3 interrupt
		if (--I2C_Timeout == 0)
			CC.I2CERROR = TIMEOUT; // set error status

	if (iFrameCounter >= FRAME_ROLL)
		iFrameCounter = 0;
	else;

	ThrottleLed.uMode = LED_ANALOG; // analog, duty set in servoMix.c
	ThrottleLed.uOnDuty = (udb_pwIn[8] / 2048) + 8;
	oLED1 = LED_Update(&ThrottleLed, oLED1);
	if (GreenLED.uMode == LED_ANALOG) // analog mode based on mode channel, more assist = brighter LED
		GreenLED.uOnDuty = (udb_pwIn[MODE_SWITCH_INPUT_CHANNEL + 7] / 2048) + 9;
	LED_GREEN = LED_Update(&GreenLED, LED_GREEN);

	if (dwMilliSec < 1000) // give radio a chance to insert values
		return;
	else;

	if ((iFrameCounter & 1)) // only start them on odd millisec counts 
	{
		switch ((iFrameCounter % FRAME_50HZ_CNT) >> 1) {
			case 1 + SERVO_OUT_OFFSET: // start OC1 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 0].iSpare, &DIO[SERVO_PIN_START + 0], (LPOCM) & OC1RS);
				break;
			case 2 + SERVO_OUT_OFFSET: // start OC2 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 1].iSpare, &DIO[SERVO_PIN_START + 1], (LPOCM) & OC2RS);
				break;
			case 3 + SERVO_OUT_OFFSET: // start OC3 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 2].iSpare, &DIO[SERVO_PIN_START + 2], (LPOCM) & OC3RS);
				break;
			case 4 + SERVO_OUT_OFFSET: // start OC4 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 3].iSpare, &DIO[SERVO_PIN_START + 3], (LPOCM) & OC4RS);
				break;
			case 5 + SERVO_OUT_OFFSET: // start OC5 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 4].iSpare, &DIO[SERVO_PIN_START + 4], (LPOCM) & OC5RS);
				break;
			case 6 + SERVO_OUT_OFFSET: // start OC6 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 5].iSpare, &DIO[SERVO_PIN_START + 5], (LPOCM) & OC6RS);
				break;
			case 7 + SERVO_OUT_OFFSET: // start OC7 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 6].iSpare, &DIO[SERVO_PIN_START + 6], (LPOCM) & OC7RS);
				break;
			case 8 + SERVO_OUT_OFFSET: // start OC8 - this will end up in a pin function
				do_pin(DIO[SERVO_PIN_START + 7].iSpare, &DIO[SERVO_PIN_START + 7], (LPOCM) & OC8RS);
				break;
		}
	};

	//	Executes whatever needs to be done every 20 milliseconds
	//	This is a good place to compute pulse widths for servos.
	if (!(iFrameCounter % FRAME_50HZ_CNT)) // has to == 0
	{
		if (CD[magCDindex].iResult >= MAG_NORMAL) // is in MAG_NORMAL mode
			I2C_flags.bMagReady = 1; // mark it
		if (CD[accCDindex].iResult >= ACC_NORMAL) // is in ACC_NORMAL mode
			I2C_flags.bAccReady = 1; // mark it
	}

	//	Executes whatever needs to be done every 25 milliseconds, using the PWM clock.
	//	This is a good place to run the A/D digital filters and compute pulse widths for servos.
	//	Also, this is used to wait a few pulses before recording input DC offsets.

	if (!(iFrameCounter % FRAME_40HZ_CNT)) // has to == 0
	{
#if ( NORADIO == 0 )
		twentyHertzCounter++;
		if (twentyHertzCounter >= 2) {
			if (failSafePulses == 0) // for all of this GreenLED will get
			{ // updated in next pass of states
				udb_flags._.radio_on = 0; // but transistion causes instant
				LED_GREEN = LED_OFF; // LED change
			} else if (failSafePulses >= 7) {
				if (!udb_flags._.radio_on) {
					udb_flags._.radio_on = 1;
					LED_GREEN = LED_ON;
				} else failSafePulses = 8;
			} else if (failSafePulses > 0)
				failSafePulses--;
			twentyHertzCounter = 0;

		}

#if (BOARD_TYPE != ASPG_BOARD)
		// changed to run on T4 lower priority
		udb_servo_callback_prepare_outputs();
#endif
#endif
	}

	// interrupt_restore_extended_state ;
	return;
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC1Interrupt(void) {
	IFS0bits.OC1IF = 0; // Clear Output Compare 1 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 0].iSpare * -1, &DIO[SERVO_PIN_START + 0], (LPOCM) & OC1RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC2Interrupt(void) {
	IFS0bits.OC2IF = 0; // Clear Output Compare 2 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 1].iSpare * -1, &DIO[SERVO_PIN_START + 1], (LPOCM) & OC2RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC3Interrupt(void) {
	IFS1bits.OC3IF = 0; // Clear Output Compare 3 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 2].iSpare * -1, &DIO[SERVO_PIN_START + 2], (LPOCM) & OC3RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC4Interrupt(void) {
	IFS1bits.OC4IF = 0; // Clear Output Compare 4 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 3].iSpare * -1, &DIO[SERVO_PIN_START + 3], (LPOCM) & OC4RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC5Interrupt(void) {
	IFS2bits.OC5IF = 0; // Clear Output Compare 5 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 4].iSpare * -1, &DIO[SERVO_PIN_START + 4], (LPOCM) & OC5RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC6Interrupt(void) {
	IFS2bits.OC6IF = 0; // Clear Output Compare 6 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 5].iSpare * -1, &DIO[SERVO_PIN_START + 5], (LPOCM) & OC6RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC7Interrupt(void) {
	IFS2bits.OC7IF = 0; // Clear Output Compare 7 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 6].iSpare * -1, &DIO[SERVO_PIN_START + 6], (LPOCM) & OC7RS);
}

void __attribute__((__interrupt__, __no_auto_psv__)) _OC8Interrupt(void) {
	IFS2bits.OC8IF = 0; // Clear Output Compare 8 Interrupt Flag
	do_pin(DIO[SERVO_PIN_START + 7].iSpare * -1, &DIO[SERVO_PIN_START + 7], (LPOCM) & OC8RS);

	//	OC8CON = 0;			// TODO: need to write actual pin handler
}
const WORD LED_Table[16] = {
	0x0000, 0x0100, 0x1010, 0x2104, 0x1111, 0x4924, 0x5252, 0x54aa,
	0x5555, 0x55d5, 0x5d75, 0x7775, 0x7777, 0x7f77, 0x7f7f, 0xffff
};

int LED_Update(LPLEDCTRL tagLED, int LED) {
	switch (tagLED->uMode) {
		case LED_ON_OFF:
			return (tagLED->uOnDuty & 1) ? LED_ON : LED_OFF;
			break;
		case LED_ANALOG:
			//			if ((iFrameCounter & 0x1))
			//				return LED_OFF;
			//			else
			if (tagLED->uOffDuty != tagLED->uOnDuty) {
				tagLED->wBits = LED_Table[tagLED->uOnDuty & 0xf];
				tagLED->uOffDuty = tagLED->uOnDuty;
			};
			//			return (tagLED->wBits & (1 << ((iFrameCounter >> 1) & 0xf))) ? LED_ON : LED_OFF;
			return (tagLED->wBits & (1 << ((iFrameCounter) & 0xf))) ? LED_ON : LED_OFF;
			break;
		case LED_DUTY_1mS: //  1mSec - variable time base - must be "&" power of 2
		case LED_DUTY_2mS: //  2mSec - variable time base - must be "&" power of 2
		case LED_DUTY_4mS: //  4mSec - variable time base - must be "&" power of 2
		case LED_DUTY_8mS: //  8mSec - variable time base - must be "&" power of 2
		case LED_DUTY_16mS: // 16mSec - variable time base - must be "&" power of 2
			if (!(iFrameCounter & tagLED->uMode)) // all bits have to be 0
			{
				tagLED->wBits++; // inc counter
				if (LED == LED_ON) //
				{
					if (tagLED->wBits > tagLED->uOnDuty) {
						tagLED->wBits = 0;
						return LED_OFF;
					} else return LED_ON;
				} else {
					if (tagLED->wBits > tagLED->uOffDuty) {
						tagLED->wBits = 0;
						return LED_ON;
					} else return LED_OFF;
				}
			} else return LED;
			break;
	}
	return LED;
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

