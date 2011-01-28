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


#include "libDCM_internal.h"
#include "../libUDB/FIR_Filter.h"
#include "../libUDB/filter_aspg.h"

extern int averageSample( int *, int );

union dcm_fbts_byte dcm_flags ;
boolean dcm_has_calibrated = false ;

//#if (MAG_YAW_DRIFT == 1)
char dcm_fourHertzCounter = 0 ;
//#endif


#if ( HILSIM == 1 )
unsigned char SIMservoOutputs[] = {	0xFF, 0xEE,		//sync
									0x03, 0x04,		//S1
									0x05, 0x06,		//S2
									0x07, 0x08,		//S3
									0x09, 0x0A,		//S4
									0x0B, 0x0C,		//S5
									0x0D, 0x0E,		//S6
									0x0F, 0x10,		//S7
									0x11, 0x12,		//S8
									0x13, 0x14		//checksum
									};

#define HILSIM_NUM_SERVOS 8

void send_HILSIM_outputs( void ) ;
#endif


void dcm_init( void )
{
	dcm_flags.B = 0 ;
	dcm_flags._.first_mag_reading = 1 ;
	
	dcm_init_rmat() ;
	
	return ;
}


// Called at 40Hz
void udb_servo_callback_prepare_outputs(void)
{
//#if (MAG_YAW_DRIFT == 1)
	// This is a simple counter to do stuff at 4hz
		// Approximate time passing between each telemetry line, even though
		// we may not have new GPS time data each time through.
		/*	if (tow.WW > 0) */ tow.WW += 25 ;
	dcm_fourHertzCounter++ ;
	if ( dcm_fourHertzCounter >= 10 )
	{
		rxMagnetometer() ;	// now actually all interrupt driven but this will kickstart
		rxAccel() ;			// now actually all interrupt driven but this will kickstart
		dcm_fourHertzCounter = 0 ;
	}
//#endif

	int	iNumSamples;
	int iIndex;

	iAnalog_Tail = iAnalog_Head&0x3f;	// should actually be iAnalog_Head
	udb_setDSPLibInUse(true) ;

	if ( iAnalog_Tail > 10 )
	{
		MDSFIR( iAnalog_Tail, &AD1_Filt[1][1][0], &AD1_Filt[0][1][0], &filter_aspgFilterX);
		MDSFIR( iAnalog_Tail, &AD1_Filt[1][2][0], &AD1_Filt[0][2][0], &filter_aspgFilterY);
		MDSFIR( iAnalog_Tail, &AD1_Filt[1][3][0], &AD1_Filt[0][3][0], &filter_aspgFilterZ);
		_DI();										// have to run this int disabled - should be fast
		iNumSamples = iAnalog_Head - iAnalog_Tail;	// get any during FIR ?
		if ( iNumSamples )							// copy those samples to begin of buffer
		{
			for ( iIndex = 0; iIndex < iNumSamples; iIndex++ )
			{
				AD1_Filt[0][1][iIndex] = AD1_Filt[0][1][iAnalog_Tail + iIndex];
				AD1_Filt[0][2][iIndex] = AD1_Filt[0][2][iAnalog_Tail + iIndex];
				AD1_Filt[0][3][iIndex] = AD1_Filt[0][3][iAnalog_Tail + iIndex];
			};
			iAnalog_Head = iIndex;
		} else iAnalog_Head = 0;
		_EI();
		FLT_Value[1] = averageSample( &AD1_Filt[1][1][0], iAnalog_Tail );
		FLT_Value[2] = averageSample( &AD1_Filt[1][2][0], iAnalog_Tail );
		FLT_Value[3] = averageSample( &AD1_Filt[1][3][0], iAnalog_Tail );
//		FLT_Value[1] = 0;
//		FLT_Value[2] = 0;
//		FLT_Value[3] = 0;
		lastGyroSamples = iAnalog_Tail;
	};

	iI2C_Tail = iI2C_Head&0x3f;	// should actually be iI2C_Head
	if ( iI2C_Tail > 10 )
	{
		MDSFIR( iI2C_Tail, &AD1_Filt[1][4][0], &AD1_Filt[0][4][0], &filter_aspg_I2CX_Filter);
		MDSFIR( iI2C_Tail, &AD1_Filt[1][5][0], &AD1_Filt[0][5][0], &filter_aspg_I2CY_Filter);
		MDSFIR( iI2C_Tail, &AD1_Filt[1][6][0], &AD1_Filt[0][6][0], &filter_aspg_I2CZ_Filter);
		_DI();										// have to run this int disabled - should be fast
		iNumSamples = iI2C_Head - iI2C_Tail;		// get any during FIR ?
		if ( iNumSamples )							// copy those samples to begin of buffer
		{
			for ( iIndex = 0; iIndex < iNumSamples; iIndex++ )
			{
				AD1_Filt[0][4][iIndex] = AD1_Filt[0][4][iI2C_Tail + iIndex];
				AD1_Filt[0][5][iIndex] = AD1_Filt[0][5][iI2C_Tail + iIndex];
				AD1_Filt[0][6][iIndex] = AD1_Filt[0][6][iI2C_Tail + iIndex];
			};
			iI2C_Head = iIndex;
		} else iI2C_Head = 0;
		_EI();
		FLT_Value[4] = averageSample( &AD1_Filt[1][4][0], iI2C_Tail );
		FLT_Value[5] = averageSample( &AD1_Filt[1][5][0], iI2C_Tail );
		FLT_Value[6] = averageSample( &AD1_Filt[1][6][0], iI2C_Tail );
		lastAccelSamples = iI2C_Tail;

	};

	udb_setDSPLibInUse(false) ;
//		udb_xaccel.value = udb_xaccel.value + (( (udb_xaccel.input>>1) - (udb_xaccel.value>>1) )>> FILTERSHIFT ) ;
//		udb_xrate.value = udb_xrate.value + (( (udb_xrate.input>>1) - (udb_xrate.value>>1) )>> FILTERSHIFT ) ;
//		udb_yaccel.value = udb_yaccel.value + (( ( udb_yaccel.input>>1) - (udb_yaccel.value>>1) )>> FILTERSHIFT ) ;
//		udb_yrate.value = udb_yrate.value + (( (udb_yrate.input>>1) - (udb_yrate.value>>1) )>> FILTERSHIFT ) ;
//		udb_zaccel.value = udb_zaccel.value + (( (udb_zaccel.input>>1) - (udb_zaccel.value>>1) )>> FILTERSHIFT ) ;

	udb_xrate.value = FLT_Value[gyro_x];
	udb_yrate.value = FLT_Value[gyro_y];
	udb_zrate.value = FLT_Value[gyro_z];

	udb_xaccel.value = FLT_Value[accel_x]*2;
	udb_yaccel.value = FLT_Value[accel_y]*2;
	udb_zaccel.value = FLT_Value[accel_z]*2;

	if (dcm_has_calibrated) {
		dcm_run_imu_step() ;
	}
	
	dcm_servo_callback_prepare_outputs() ;
	
#if ( HILSIM == 1)
	send_HILSIM_outputs() ;
#endif
	
	return ;
}


void dcm_calibrate(void)
{
	udb_a2d_record_offsets() ;
	dcm_has_calibrated = true ;
	return ;
}


void dcm_set_origin_location(long o_long, long o_lat, long o_alt)
{
	union longbbbb accum_nav ;
	
	lat_origin.WW = o_lat ;
	long_origin.WW = o_long ;
	alt_origin.WW = o_alt;
	
	//	scale the latitude from GPS units to gentleNAV units
	accum_nav.WW = __builtin_mulss( LONGDEG_2_BYTECIR , lat_origin._.W1 ) ;
	lat_cir = accum_nav.__.B2 ;
	//	estimate the cosine of the latitude, which is used later computing desired course
	cos_lat = cosine ( lat_cir ) ;
	
	return ;
}


struct relative3D dcm_absolute_to_relative(struct waypoint3D absolute)
{
	struct relative3D rel ;
	union longww accum_nav ;
	
	rel.z = absolute.z ;
	
	rel.y = (absolute.y - lat_origin.WW)/90 ; // in meters
	
	accum_nav.WW = ((absolute.x - long_origin.WW)/90) ; // in meters
	accum_nav.WW = ((__builtin_mulss ( cos_lat , accum_nav._.W0 )<<2)) ;
	rel.x = accum_nav._.W1 ;
	
	return rel ;
}


#if ( HILSIM == 1 )

void send_HILSIM_outputs( void )
{
	// Setup outputs for HILSIM
	int i ;
	unsigned char CK_A = 0 ;
	unsigned char CK_B = 0 ;
	union intbb TempBB ;
	
	for (i=1; i<=NUM_OUTPUTS; i++)
	{
		TempBB.BB = udb_pwOut[i] ;
		SIMservoOutputs[2*i] = TempBB._.B1 ;
		SIMservoOutputs[(2*i)+1] = TempBB._.B0 ;
	}
	
	for (i=2; i<HILSIM_NUM_SERVOS*2+2; i++)
	{
		CK_A += SIMservoOutputs[i] ;
		CK_B += CK_A ;
	}
	SIMservoOutputs[i] = CK_A ;
	SIMservoOutputs[i+1] = CK_B ;
	
	// Send HILSIM outputs
	for (i=0; i<HILSIM_NUM_SERVOS*2+4; i++)
	{
		udb_gps_send_char(SIMservoOutputs[i]) ;	
	}
	
	return ;
}

#endif
