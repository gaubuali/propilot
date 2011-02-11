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


struct relative3D IMPORTANT GPSlocation 		= { 0 , 0 , 0 } ;
struct relative3D IMPORTANT GPSvelocity 		= { 0 , 0 , 0 } ;
struct relative2D IMPORTANT velocity_thru_air   = { 0 , 0 } ;

union longbbbb IMPORTANT lat_gps = {0};
union longbbbb IMPORTANT long_gps = {0};
union longbbbb IMPORTANT alt_sl_gps = {0};
union longbbbb IMPORTANT tow = {0};			// latitude, longitude, altitude
union intbb    IMPORTANT sog_gps = {0};
union intbb    IMPORTANT cog_gps = {0};
union intbb    IMPORTANT climb_gps = {0};
union intbb    IMPORTANT week_no = {0};		// speed over ground, course over ground, climb
unsigned char  IMPORTANT hdop = {0};		// horizontal dilution of precision

union longbbbb IMPORTANT lat_origin = {0};
union longbbbb IMPORTANT long_origin = {0};
union longbbbb IMPORTANT alt_origin = {0};

union longbbbb IMPORTANT xpg = {0};
union longbbbb IMPORTANT ypg = {0};
union longbbbb IMPORTANT zpg = {0};			// gps x, y, z position
union intbb    IMPORTANT xvg = {0};
union intbb    IMPORTANT yvg = {0};
union intbb    IMPORTANT zvg = {0};			// gps x, y, z velocity
unsigned char  IMPORTANT mode1 = 0;
unsigned char  IMPORTANT mode2 = 0;
unsigned char  IMPORTANT svs = 0;			// gps mode1, mode2, and number of satellites

unsigned char  IMPORTANT lat_cir = 0;
int			   IMPORTANT cos_lat = 0 ;

int IMPORTANT gps_data_age = 0;

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


// Got a character from the GPS
void udb_gps_callback_received_char(char rxchar)
{
	//bin_out ( rxchar ) ; // binary out to the debugging USART	
	(* msg_parse) ( rxchar ) ; // parse the input byte
	return ;
}


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