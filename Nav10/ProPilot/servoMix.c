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


#include "defines.h"

//	Perform control based on the airframe type.
//	Use the radio to determine the baseline pulse widths if the radio is on.
//	Otherwise, use the trim pulse width measured during power up.
//
//	Mix computed roll and pitch controls into the output channels for the compiled airframe type


const int aileronbgain = (int)(8.0*AILERON_BOOST) ;
const int elevatorbgain = (int)(8.0*ELEVATOR_BOOST) ;
const int rudderbgain = (int)(8.0*RUDDER_BOOST) ;

#define pfgMix

#ifdef pfgMix
#define MIX_PER_CHANNEL 8

// for now the following file defines pMixers and fills with data
#include "Mixer.h"

// not counting AP_MODE
#define NUM_AP_COMMANDS 7

// int	iInputs[1 + NUM_AP_COMMANDS + MIX_NUM_INPUTS]; 	// using udb_Pwin now
// int iOutputs[MIX_NUM_OUTPUTS+1];						// using udb_Pwout now

// Cleaned up mixer does one channel, called from servoMix with a pointer to mixer bank and returns output
int bankMix( LPMIXER pThisMixer, LPWORD ticks )
{
	int	temp, temp1, iFactor, iInputCH, iInputSSI;
	union longbbbb tempA, tempB;
	long OutA, OutB;
	unsigned int iMix, uiType;

	for ( OutA = OutB = iMix = 0; iMix < (MIX_PER_CHANNEL); iMix++, pThisMixer++ )
	{
		if ( iMix == (MIX_PER_CHANNEL - 2) )	// 2nd to last mixer is always hardware scale
			uiType = 16;
		else if ( iMix == (MIX_PER_CHANNEL - 1) ) // last mixer is always per channel hardware limit
			uiType = 17;
		else uiType = pThisMixer->nType.iType;
		if ( uiType != 0 )
		{
			if ( pThisMixer->nType.iInpCH )
				iInputCH = udb_pwIn[pThisMixer->nType.iInpCH];		// get these in one spot to save code space
			else iInputCH = 0;
			if ( pThisMixer->nType.iInpSSI )
				iInputSSI = udb_pwIn[pThisMixer->nType.iInpSSI];
			else iInputSSI = 0;
			iFactor = pThisMixer->nType.iFactor;

			switch ( uiType )
			{
				case 0: // unused, skip
				break;
				case 1: // Out += Inputs[InputCH] * Factor * (1.0-Balance) + Inputs[InputSSI] * Factor * Balance
					temp = udb_pwIn[pThisMixer->pType.iInpTSI]; // calc balance = fx(-1.0,1.0) -> (0,1.0)
					if ( temp < 0 )
					{	temp &= 0x7fff; // kill sign bit;
						if ( temp != 0 ) // check for special case of -32768 = botom of range so the now 0 works
							temp = temp >> 3; // fast /4
					} else {
							temp = temp >> 3; // fast /4
							temp += 0x1000; // get into top half of range
					}
					if ( temp >= 0x2000 ) temp = 0x1fff; // fix range
					temp = temp << 2;
					temp1 = toQ15(1.0) - temp; // get the other side
					iFactor &= 0xffc0; // kill third input channel bits
					tempA.WW = __builtin_mulss( temp1 , iFactor );
					tempA.WW = __builtin_mulss( tempA._.W1, iInputCH );
					tempB.WW = __builtin_mulss( temp , iFactor );
					tempB.WW = __builtin_mulss( tempB._.W1, iInputSSI );
					OutA += tempA._.W1 + tempB._.W1;
				break;
				case 2: // Out += Inputs[InputCH] * (1.0-Balance) + Inputs[InputSSI] * Balance
					temp = udb_pwIn[pThisMixer->pType.iInpTSI]; // calc balance = fx(-1.0,1.0) -> (0,1.0)
					if ( temp < 0 )
					{	temp &= 0x7fff; // kill sign bit;
						if ( temp != 0 ) // check for special case of -32768 = botom of range so the now 0 works
							temp = temp >> 3; // fast /4
					} else {
							temp = temp >> 3; // fast /4
							temp += 0x1000; // get into top half of range
					}
					if ( temp >= 0x2000 ) temp = 0x1fff; // fix range
					temp = temp << 2;
					temp1 = toQ15(1.0) - temp; // get the other side
					iFactor &= 0xffc0; // kill third input channel bits
					tempA.WW = __builtin_mulss( temp1 , iInputCH );
					tempB.WW = __builtin_mulss( temp , iInputSSI );
					OutA += tempA._.W1 + tempB._.W1;
				break;
				case 3: // Out += Inputs[InputCH] * (1.0-Balance) + Inputs[InputSSI] * Factor * Balance
					temp = udb_pwIn[pThisMixer->pType.iInpTSI]; // calc balance = fx(-1.0,1.0) -> (0,1.0)
					if ( temp < 0 )
					{	temp &= 0x7fff; // kill sign bit;
						if ( temp != 0 ) // check for special case of -32768 = botom of range so the now 0 works
							temp = temp >> 3; // fast /4
					} else {
							temp = temp >> 3; // fast /4
							temp += 0x1000; // get into top half of range
					}
					if ( temp >= 0x2000 ) temp = 0x1fff; // fix range
					temp = temp << 2;
					temp1 = toQ15(1.0) - temp; // get the other side
					iFactor &= 0xffc0; // kill third input channel bits
					tempA.WW = __builtin_mulss( temp1 , iInputCH );
					tempB.WW = __builtin_mulss( temp , iFactor );
					tempB.WW = __builtin_mulss( tempB._.W1, iInputSSI );
					OutA += tempA._.W1 + tempB._.W1;
				break;
				case 4: // not used yet
				break;
				case 5: // Out = Out + (Inputs[InputCH] * Factor)
					tempA.WW = __builtin_mulss( iFactor, iInputCH );
					OutA += tempA._.W1;
				break;
				case 6: // Out = Out + (Inputs[InputCH] * Factor * Inputs[InputSSI])
					tempA.WW = __builtin_mulss( iFactor, iInputCH );
					tempA.WW = __builtin_mulss( tempA._.W1, iInputSSI );
					OutA += tempA._.W1;
				break;
				case 7: // IF MANUAL Out = Out + (Inputs[InputCH] * Factor)
					if ( udb_pwIn[0] == 0 )
					{
						tempA.WW = __builtin_mulss( iFactor, iInputCH );
						OutA += tempA._.W1;
					};
				break;
				case 8: //IF MANUAL Out = Out + (Inputs[InputCH] * Factor * Inputs[InputSSI])
					if ( udb_pwIn[0] == 0 )
					{
						tempA.WW = __builtin_mulss( iFactor, iInputCH );
						tempA.WW = __builtin_mulss( tempA._.W1, iInputSSI );
						OutA += tempA._.W1;
					};
				break;
				case 9: // IF ASSIST (manual + autopilot) Out = Out + IF (Inputs[InputCH] * Factor)
					if ( (udb_pwIn[0] > 0) && (udb_pwIn[0] < 255))
					{
						tempA.WW = __builtin_mulss( iFactor, iInputCH );
						OutA += tempA._.W1;
					};
				break;
				case 10: // IF ASSIST (manual + autopilot) Out = Out + (Inputs[InputCH] * Factor * Inputs[InputSSI])
					if ( (udb_pwIn[0] > 0) && (udb_pwIn[0] < 255))
					{
						tempA.WW = __builtin_mulss( iFactor, iInputCH );
						tempA.WW = __builtin_mulss( tempA._.W1, iInputSSI );
						OutA += tempA._.W1;
					};
				break;
				case 11: // IF AUTO (rtl or waypoint) Out = Out + IF (Inputs[InputCH] * Factor)
					if ( udb_pwIn[0] == 255 )
					{
						tempA.WW = __builtin_mulss( iFactor, iInputCH );
						OutA += tempA._.W1;
					};
				break;
				case 12: // IF AUTO (rtl or waypoint) Out = Out + (Inputs[InputCH] * Factor * Inputs[InputSSI])
					if ( udb_pwIn[0] == 255 )
					{
						tempA.WW = __builtin_mulss( iFactor, iInputCH );
						tempA.WW = __builtin_mulss( tempA._.W1, iInputSSI );
						OutA += tempA._.W1;
					};
				break;
				case 13: // IF iInputCH positive Out -= Out * Factor
					if ( (iInputCH > 0) || (iInputSSI > 0) )
						OutA  -= (((long)iFactor * OutA));
					else ;
				break;
				case 14: // IF iInputCH negative Out -= Out * Factor
					if ( (iInputCH < 0) || (iInputSSI < 0)  )
						OutA  -= (((long)iFactor * OutA));
					else ;
				break;
				case 15: // Out = Factor
					OutA = iFactor;
				break;
				case 16: // overide "type" for output scale Ticks = Out * Scale + Offset.
					if ( OutA > toQ15(1.0) ) OutA = toQ15(1.0);
					if ( OutA < toQ15(-1.0) ) OutA = toQ15(-1.0);
					OutB  = ((((long)iFactor * OutA) >> 13)) + pThisMixer->iScales[0];
				break;
				case 17: // overide "type" for per channel limit later
					temp = (WORD)OutB;
					if ( temp > iFactor )
						temp = iFactor;
					else
					if ( temp < pThisMixer->iScales[0] )
						temp = pThisMixer->iScales[0];
					*ticks = (WORD)temp;
				break;
			}; // end of switch ( uiType )
		}; // end of if ( uiType != 0 )
	}; // end of for ( iMix = 0; iMix < (MIX_PER_CHANNEL); iMix++ )
	return( (int)OutA );
}

void servoMix( void )
{
	unsigned int iCH, iPulse, iOut, uiTemp;
//	LPMIXER pThisChannel;

	// this would all change, just keeping for now

	// If radio is off, use udb_pwTrim values instead of the udb_pwIn values
	// test radio once, a good compiler will produce less and faster code
	if (udb_flags._.radio_on == 0)
	{	for (iCH = 1; iCH <= 64; iCH++)
		if ( iCH != (MODE_SWITCH_INPUT_CHANNEL + 7))
			udb_pwIn[iCH] = udb_pwTrim[iCH];		// is Q15
	}

	udb_pwIn[1] = roll_control + waggle;
	udb_pwIn[2] = pitch_control;
	udb_pwIn[3] = yaw_control - waggle;
	udb_pwIn[4] = throttle_control;
// TODO: mass changes to camera outputs - they are tied to the old pwm rates

	if (udb_flags._.radio_on && flags._.pitch_feedback)
		udb_pwIn[0] = 127; // mid scale value, autopilot helping
	else if ( flags._.home_req || flags._.auto_req )
		udb_pwIn[0] = 255; // full scale value - autopilot in control
	else udb_pwIn[0] = 0; // low value, no autopilot input

//	for ( iCH = 1, pThisChannel = &pMixers[0][0]; iCH <= NUM_OUTPUTS; iCH++, pThisChannel += MIX_PER_CHANNEL )
// TODO: this will need major mods to work for multi-channel outputs
	for ( iCH = 1; iCH < NUM_OUTPUTS; iCH++ )
	{
		iOut = bankMix( &pMixers[iCH-1][0], &iPulse );
		udb_pwOut[iCH] = iPulse;
		uiTemp = iCH + SERVO_PIN_START - 1;						// both one based
		DIO[uiTemp].qValue = iOut;								// save
		if ( DIO[uiTemp].iType < 10 )
			DIO[uiTemp].iBuffer[DIO[uiTemp].iIndex++] = iOut;	// record it for history
//		else DIO[uiTemp].iBuffer[DIO[uiTemp].iIndex] = iOut;	// record it for history
//		DIO[iCH + SERVO_PIN_START - 1].iBuffer[DIO[iCH + SERVO_PIN_START - 1].iIndex++] = udb_pwOut[iCH];	// record it for history
	}; // end of for ( iCH = 1; iCH <= NUM_OUTPUTS; iCH++ )
}

#else

void servoMix( void )
{
	long temp ;
	int pwManual[NUM_INPUTS+1] ;
	
	// If radio is off, use udb_pwTrim values instead of the udb_pwIn values
	for (temp = 1; temp <= NUM_INPUTS; temp++)
		if (udb_flags._.radio_on)
			pwManual[temp] = udb_pwIn[temp];
		else
			pwManual[temp] = udb_pwTrim[temp];
	
	
	// Apply boosts if in a stabilized mode
	if (udb_flags._.radio_on && flags._.pitch_feedback)
	{
		pwManual[AILERON_INPUT_CHANNEL] += ((pwManual[AILERON_INPUT_CHANNEL] - udb_pwTrim[AILERON_INPUT_CHANNEL]) * aileronbgain) >> 3 ;
		pwManual[ELEVATOR_INPUT_CHANNEL] += ((pwManual[ELEVATOR_INPUT_CHANNEL] - udb_pwTrim[ELEVATOR_INPUT_CHANNEL]) * elevatorbgain) >> 3 ;
		pwManual[RUDDER_INPUT_CHANNEL] += ((pwManual[RUDDER_INPUT_CHANNEL] - udb_pwTrim[RUDDER_INPUT_CHANNEL]) * rudderbgain) >> 3 ;
	}
	
	// Standard airplane airframe
	// Mix roll_control into ailerons
	// Mix pitch_control into elevators
	// Mix yaw control and waggle into rudder
#if ( AIRFRAME_TYPE == AIRFRAME_STANDARD )
		temp = pwManual[AILERON_INPUT_CHANNEL] + REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control + waggle) ;
		udb_pwOut[AILERON_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		udb_pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = 3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, udb_pwOut[AILERON_OUTPUT_CHANNEL] - 3000) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control) ;
		udb_pwOut[ELEVATOR_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] + REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control - waggle) ;
		udb_pwOut[RUDDER_OUTPUT_CHANNEL] =  udb_servo_pulsesat( temp ) ;
		
		if ( pwManual[THROTTLE_INPUT_CHANNEL] == 0 )
		{
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = 0 ;
		}
		else
		{	
			temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, throttle_control) ;
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		}
#endif
	
	
	// V-Tail airplane airframe
	// Mix roll_control and waggle into ailerons
	// Mix pitch_control and yaw_control into both elevator and rudder
#if ( AIRFRAME_TYPE == AIRFRAME_VTAIL )
		long vtail_yaw_control = REVERSE_IF_NEEDED(ELEVON_VTAIL_SURFACES_REVERSED, yaw_control) ;
		
		temp = pwManual[AILERON_INPUT_CHANNEL] + REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control + waggle) ;
		udb_pwOut[AILERON_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		//	Reverse the polarity of the secondary aileron if necessary
		udb_pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = 3000 +
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, udb_pwOut[AILERON_OUTPUT_CHANNEL] - 3000) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control + vtail_yaw_control) ;
		udb_pwOut[ELEVATOR_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, pitch_control - vtail_yaw_control) ;
		udb_pwOut[RUDDER_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		if ( pwManual[THROTTLE_INPUT_CHANNEL] == 0 )
		{
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = 0 ;
		}
		else
		{	
			temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, throttle_control) ;
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		}
#endif
	
	
	// Delta-Wing airplane airframe
	// Mix roll_control, pitch_control, and waggle into aileron and elevator
	// Mix rudder_control into  rudder
#if ( AIRFRAME_TYPE == AIRFRAME_DELTA )
		long delta_roll_control = REVERSE_IF_NEEDED(ELEVON_VTAIL_SURFACES_REVERSED, roll_control) ;
		
		temp = pwManual[AILERON_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, -delta_roll_control + pitch_control - waggle) ;
		udb_pwOut[AILERON_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, delta_roll_control + pitch_control + waggle) ;
		udb_pwOut[ELEVATOR_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] + REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control) ;
		udb_pwOut[RUDDER_OUTPUT_CHANNEL] =  udb_servo_pulsesat( temp ) ;
		
		if ( pwManual[THROTTLE_INPUT_CHANNEL] == 0 )
		{
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = 0 ;
		}
		else
		{	
			temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, throttle_control) ;
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		}
#endif
	
	
	// Helicopter airframe
	// Mix half of roll_control and half of pitch_control into aileron channels
	// Mix full pitch_control into elevator
	// Ignore waggle for now
#if ( AIRFRAME_TYPE == AIRFRAME_HELI )
		temp = pwManual[AILERON_INPUT_CHANNEL] +
			REVERSE_IF_NEEDED(AILERON_CHANNEL_REVERSED, roll_control/2 + pitch_control/2) ;
		udb_pwOut[AILERON_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		temp = pwManual[ELEVATOR_INPUT_CHANNEL] + REVERSE_IF_NEEDED(ELEVATOR_CHANNEL_REVERSED, pitch_control) ;
		udb_pwOut[ELEVATOR_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		temp = pwManual[AILERON_SECONDARY_OUTPUT_CHANNEL] + 
			REVERSE_IF_NEEDED(AILERON_SECONDARY_CHANNEL_REVERSED, -roll_control/2 + pitch_control/2) ;
		udb_pwOut[AILERON_SECONDARY_OUTPUT_CHANNEL] = temp ;
		
		temp = pwManual[RUDDER_INPUT_CHANNEL] /*+ REVERSE_IF_NEEDED(RUDDER_CHANNEL_REVERSED, yaw_control)*/ ;
		udb_pwOut[RUDDER_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		
		if ( pwManual[THROTTLE_INPUT_CHANNEL] == 0 )
		{
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = 0 ;
		}
		else
		{	
			temp = pwManual[THROTTLE_INPUT_CHANNEL] + REVERSE_IF_NEEDED(THROTTLE_CHANNEL_REVERSED, throttle_control) ;
			udb_pwOut[THROTTLE_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp ) ;
		}
#endif
		
		udb_pwOut[PASSTHROUGH_A_OUTPUT_CHANNEL] = udb_servo_pulsesat( pwManual[PASSTHROUGH_A_INPUT_CHANNEL] ) ;
		udb_pwOut[PASSTHROUGH_B_OUTPUT_CHANNEL] = udb_servo_pulsesat( pwManual[PASSTHROUGH_B_INPUT_CHANNEL] ) ;
		udb_pwOut[PASSTHROUGH_C_OUTPUT_CHANNEL] = udb_servo_pulsesat( pwManual[PASSTHROUGH_C_INPUT_CHANNEL] ) ;
		udb_pwOut[PASSTHROUGH_D_OUTPUT_CHANNEL] = udb_servo_pulsesat( pwManual[PASSTHROUGH_D_INPUT_CHANNEL] ) ;
}

#endif
void cameraServoMix( void )
{
	long temp ;
	int pwManual[NUM_INPUTS+1] ;
	
	// If radio is off, use udb_pwTrim values instead of the udb_pwIn values
	for (temp = 0; temp <= NUM_INPUTS; temp++)
		if (udb_flags._.radio_on)
			pwManual[temp] = udb_pwIn[temp];
		else
			pwManual[temp] = udb_pwTrim[temp];

	temp = ( pwManual[CAMERA_PITCH_INPUT_CHANNEL] - 3000 ) + REVERSE_IF_NEEDED(CAMERA_PITCH_CHANNEL_REVERSED, 
					cam_pitch_servo_pwm_delta ) ;
	temp = cam_pitchServoLimit(temp) ;
	udb_pwOut[CAMERA_PITCH_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp + 3000 ) ;

	temp = ( pwManual[CAMERA_YAW_INPUT_CHANNEL] - 3000 ) + REVERSE_IF_NEEDED(CAMERA_YAW_CHANNEL_REVERSED, 
					cam_yaw_servo_pwm_delta ) ;
	temp = cam_yawServoLimit(temp) ;
	udb_pwOut[CAMERA_YAW_OUTPUT_CHANNEL] = udb_servo_pulsesat( temp + 3000 ) ;
}
