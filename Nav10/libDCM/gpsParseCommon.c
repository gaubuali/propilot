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


struct relative3D IMPORTANTz GPSlocation ;
struct relative3D IMPORTANTz GPSvelocity ;
struct relative2D IMPORTANTz velocity_thru_air ;

union longbbbb IMPORTANTz lat_gps ;
union longbbbb IMPORTANTz long_gps ;
union longbbbb IMPORTANTz alt_sl_gps ;
union longbbbb IMPORTANTz tow ;			// latitude, longitude, altitude
union intbb    IMPORTANTz sog_gps ;
union intbb    IMPORTANTz cog_gps ;
union intbb    IMPORTANTz climb_gps ;
union intbb    IMPORTANTz week_no ;		// speed over ground, course over ground, climb
unsigned char  IMPORTANTz hdop ;		// horizontal dilution of precision

union longbbbb IMPORTANTz lat_origin ;
union longbbbb IMPORTANTz long_origin ;
union longbbbb IMPORTANTz alt_origin ;

union longbbbb IMPORTANTz xpg ;
union longbbbb IMPORTANTz ypg ;
union longbbbb IMPORTANTz zpg ;			// gps x, y, z position
union intbb    IMPORTANTz xvg ;
union intbb    IMPORTANTz yvg ;
union intbb    IMPORTANTz zvg ;			// gps x, y, z velocity
unsigned char  IMPORTANTz mode1 ;
unsigned char  IMPORTANTz mode2 ;
unsigned char  IMPORTANTz svs ;			// gps mode1, mode2, and number of satellites

unsigned char  IMPORTANTz lat_cir ;
int			   IMPORTANTz cos_lat ;

int IMPORTANTz gps_data_age ;

extern void (* msg_parse ) ( unsigned char inchar ) ;

void gpsoutline(char message[]) // output one NMEA line to the GPS
{
	int index ;
	char outchar ;
	index = 0 ;
	while  (  (outchar = message[index++])  ) 
	{
		udb_gps_send_char(outchar) ;
	}
	return ;
}

void gpsoutbin(int length , const unsigned char msg[] )  // output a binary message to the GPS
{
	int index = 0 ;
	while ( index < length )
	{
		udb_gps_send_char( msg[index] ) ;
		index++;
	}
	return ;
}

#if ( GPS_TYPE == GPS_DEBUG )
void udb_gps_callback_received_char(char rxchar)
{
	udb_serial_send_char( rxchar );
	return ;
}
#else
// Got a character from the GPS
void udb_gps_callback_received_char(char rxchar)
{
	//bin_out ( rxchar ) ; // binary out to the debugging USART	
	(* msg_parse) ( rxchar ) ; // parse the input byte
	return ;
}
#endif

// Received a full set of GPS messages
void udb_background_callback_triggered(void) 
{
	union longbbbb accum_nav ;
	
	estYawDrift() ;
	
	if ( gps_nav_valid() )
	{
		gps_data_age = 0 ;
		
		accum_nav.WW = ((lat_gps.WW - lat_origin.WW)/90) ; // in meters, range is about 20 miles
		GPSlocation.y = accum_nav._.W0 ;
		
		//	multiply the longitude delta by the cosine of the latitude
		accum_nav.WW = ((long_gps.WW - long_origin.WW)/90) ; // in meters
		accum_nav.WW = ((__builtin_mulss ( cos_lat , accum_nav._.W0 )<<2)) ;
		GPSlocation.x = accum_nav._.W1 ;
		
		accum_nav.WW = ( alt_sl_gps.WW - alt_origin.WW)/100 ; // height in meters
		GPSlocation.z = accum_nav._.W0 ;
		
		dcm_callback_gps_location_updated() ;
		estimateWind() ;
	}
	else
	{
		gps_data_age = GPS_DATA_MAX_AGE+1 ;
	}
	
	return ;
}
