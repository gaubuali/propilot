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

#if (FLIGHT_PLAN_TYPE == FP_WAYPOINTS)

#include "../libUDB/libUDB_internal.h"

#include <string.h>
#include "waypoints.h"

#define NUMBER_POINTS (( sizeof waypoints ) / sizeof ( struct waypointDef ))
#define NUMBER_RTL_POINTS (( sizeof rtlWaypoints ) / sizeof ( struct waypointDef ))
//#define EE_WAYPOINTS_NUM ((EE_WAYPOINTS_END - EE_WAYPOINTS_START)/sizeof(struct waypointDef))

int waypointIndex IMPORTANTz ;

struct waypointDef *currentWaypointSet IMPORTANT = (struct waypointDef*)waypoints ;
int numPointsInCurrentSet PARAMETER = NUMBER_POINTS ;
int EE_wp_pos PARAMETER = -1 ;	
struct waypointDef wp_inject[4] IMPORTANTz;
struct waypointDef udb_default IMPORTANT = // temp storage 
	{ {0,0,0}, F_NORMAL, { 0, 0, 0 }, DEFAULT_WAYPOINT_RADIUS };

unsigned char wp_inject_pos IMPORTANTz ;
#define WP_INJECT_READY 255
const unsigned char wp_inject_byte_order[] = {3, 2, 1, 0, 7, 6, 5, 4, 9, 8, 11, 10, 15, 14, 13, 12, 19, 18, 17, 16, 21, 20 } ;

// For a relative waypoint, wp_to_relative() just passes the relative
// waypoint location through unchanged.
// For an absolute waypoint, wp_to_relative() converts the waypoint's
// location from absolute to relative.
struct relWaypointDef wp_to_relative(struct waypointDef wp)
{
	struct relWaypointDef rel ;
	
	if ( wp.flags & F_ABSOLUTE )
	{
		rel.loc = dcm_absolute_to_relative(wp.loc) ;
		rel.viewpoint = dcm_absolute_to_relative(wp.viewpoint) ;
		
		rel.flags = wp.flags - F_ABSOLUTE ;
	}
	else
	{
		rel.loc.x = wp.loc.x ;
		rel.loc.y = wp.loc.y ;
		rel.loc.z = wp.loc.z ;
		
		rel.viewpoint.x = wp.viewpoint.x ;
		rel.viewpoint.y = wp.viewpoint.y ;
		rel.viewpoint.z = wp.viewpoint.z ;
		
		rel.flags = wp.flags ;
	}
	
	return rel;
}


// In the future, we could include more than 2 waypoint sets...
// flightplanNum is 0 for main waypoints, and 1 for RTL waypoints
// pfg: changed for 0 = RTL (always have), 1 = rom list, 2 = ee list
void init_flightplan ( int flightplanNum )
{
//	numPointsInCurrentSet = 0;
	if ( (flightplanNum >= 1) && (EE_wp_pos >= 0) ) // EE waypoint set
	{
		currentWaypointSet = (struct waypointDef*)&wp_inject[0] ;
//		if ( wp_inject[0].loc.z >= (int)HEIGHT_TARGET_MIN )	// negative z value is illegal
//		{
//			numPointsInCurrentSet = 1;	// figure out as we go
//			EE_wp_pos = 1;
//			if ( wp_inject[1].loc.z >= (int)HEIGHT_TARGET_MIN ) 
//				numPointsInCurrentSet = 2;
//			if ( wp_inject[2].loc.z >= (int)HEIGHT_TARGET_MIN )
//				numPointsInCurrentSet = 3;
//			if ( wp_inject[3].loc.z >= (int)HEIGHT_TARGET_MIN )
//				numPointsInCurrentSet = 4;
//		} else numPointsInCurrentSet = 0;
    } else numPointsInCurrentSet = 0;
	if ( (flightplanNum == 1) && numPointsInCurrentSet == 0 ) // Main waypoint set
	{
		currentWaypointSet = (struct waypointDef*)waypoints ;
    	numPointsInCurrentSet = NUMBER_POINTS ;
    }
	else // use this if others failed - if ( flightplanNum == 0 ) // RTL waypoint set
	if ( numPointsInCurrentSet == 0 ) // use RTL waypoint set
	{
		currentWaypointSet = (struct waypointDef*)rtlWaypoints ;
		numPointsInCurrentSet = NUMBER_RTL_POINTS ;
	}
	
	waypointIndex = 0 ;
	struct relWaypointDef current_waypoint = wp_to_relative(currentWaypointSet[0]) ;
	set_goal( GPSlocation , current_waypoint.loc ) ;
	set_camera_view(current_waypoint.viewpoint) ;
	setBehavior(current_waypoint.flags) ;
	
	// udb_background_trigger() ;			// trigger navigation immediately
	
	return ;
}


boolean use_fixed_origin( void )
{
#if ( USE_FIXED_ORIGIN == 1 )
	return 1 ;
#else
	return 0 ;
#endif
}


struct absolute3D get_fixed_origin( void )
{
	struct fixedOrigin3D origin = FIXED_ORIGIN_LOCATION ;
	
	struct absolute3D standardizedOrigin ;
	standardizedOrigin.x = origin.x ;
	standardizedOrigin.y = origin.y ;
	standardizedOrigin.z = (long)(origin.z * 100) ;
	
	return standardizedOrigin ;
}

int SetWaypointToIndex( int wp_idx )
{
	int temp = waypointIndex;
	waypointIndex = wp_idx;
	return temp;
}

void checkWaypoint()	// function checks current and next waypoint is available if comming from EE
{
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( (EE_wp_pos < 0) || (EE_Active != 0) )
		return;
	else 
	{
		if ( waypointIndex != currentWaypointSet[2].seq )	// check case of ML changed waypoint
		{
			if ( currentWaypointSet[2].seq == -1 )
				wpTemp.type = 0;
			else ;
			if ( xlateWPbyIndex( waypointIndex, &wpTemp ) == waypointIndex )	// read and decoded
			{
				wp_inject[2].loc.x = GPSlocation.x;	// set previous to current
				wp_inject[2].loc.y = GPSlocation.y;	// set previous to current
				wp_inject[2].loc.z = GPSlocation.z;	// set previous to current
				wp_inject[3] = udb_default;		// xlate puts results in this buffer
				if ( udb_default.radius < 1 ) udb_default.radius = DEFAULT_WAYPOINT_RADIUS;
				waypointRadius = udb_default.radius;
				set_waypoint_by_index( waypointIndex );
			}
		} else 
		if ( waypointIndex+1 != currentWaypointSet[3].seq )	// check case just used up a waypoint
		{
			if ( currentWaypointSet[3].seq == -1 )
				wpTemp.type = 0;
			else ;
			if ( xlateWPbyIndex( waypointIndex+1, &wpTemp ) == waypointIndex+1 )	// read and decoded
			{
				wp_inject[3] = udb_default;		// xlate puts results in this buffer
				if ( udb_default.radius < 1 ) udb_default.radius = DEFAULT_WAYPOINT_RADIUS;
			}
		}
	}
#else
		return;
#endif
}

int set_waypoint_by_index( int wp_idx )
{
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( EE_wp_pos >= 0 )
	{
		if ( wp_idx < 2 )
			waypointIndex = wp_idx, EE_wp_pos = wp_idx;	// will be pre-read and usable
		else 	// we need to read from EE
		{	
			if ( currentWaypointSet[3].seq == wp_idx )
			{
				wp_inject[1] = wp_inject[2];
				wp_inject[2] = wp_inject[3];
				wp_inject[3].seq = -1;	// mark as invalid but keep existing values
				EE_wp_pos = wp_idx, waypointIndex = 2;
				if ( (wp_inject[2].loc.z < (int)HEIGHT_TARGET_MIN) || (EE_wp_pos > EE_WAYPOINTS_MAX) )
					EE_wp_pos = 0, waypointIndex = 0;
				else ;
			} else return -1;
		}
	} else {
		waypointIndex = wp_idx;
		if ( waypointIndex >= numPointsInCurrentSet ) waypointIndex = 0 ;
	}
#else
		waypointIndex = wp_idx;
		if ( waypointIndex >= numPointsInCurrentSet ) waypointIndex = 0 ;
#endif
	
	waypointRadius = currentWaypointSet[waypointIndex].radius;
	if ( waypointIndex == 0 )
	{
		if ( (numPointsInCurrentSet > 1) && (numPointsInCurrentSet < 4))
		{
			struct relWaypointDef previous_waypoint = wp_to_relative( currentWaypointSet[numPointsInCurrentSet-1] ) ;
			struct relWaypointDef current_waypoint  = wp_to_relative( currentWaypointSet[0] ) ;
			set_goal( previous_waypoint.loc, current_waypoint.loc ) ;
			set_camera_view( current_waypoint.viewpoint ) ;
		}
		else
		{
			struct relWaypointDef current_waypoint = wp_to_relative( currentWaypointSet[0] ) ;
			set_goal( GPSlocation, current_waypoint.loc ) ;
			set_camera_view( current_waypoint.viewpoint ) ;
		}
		setBehavior( currentWaypointSet[0].flags ) ;
	}
	else
	{
		struct relWaypointDef previous_waypoint = wp_to_relative( currentWaypointSet[waypointIndex-1] ) ;
		struct relWaypointDef current_waypoint = wp_to_relative( currentWaypointSet[waypointIndex] ) ;
		set_goal( previous_waypoint.loc, current_waypoint.loc ) ;
		set_camera_view( current_waypoint.viewpoint ) ;
		setBehavior( current_waypoint.flags ) ;
	}
	
#if	( DEADRECKONING == 0 )
	compute_bearing_to_goal() ;
#endif
	
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( EE_wp_pos >= 0 )
	{	return EE_wp_pos;
	} else {
		return waypointIndex;
	}
#else
		return waypointIndex;
#endif
}

void next_waypoint ( void ) 
{
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( EE_wp_pos >= 0 )
	{
		set_waypoint_by_index( EE_wp_pos + 1);
	} else {
		set_waypoint_by_index( waypointIndex + 1 );
	}
#else
		set_waypoint_by_index( waypointIndex + 1 );
#endif
}

int getNumPointsInCurrentSet( void )
{
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( EE_wp_pos >= 0 )	// using EE waypoints
	{
		return numPointsInCurrentSet;
	} else {
		if ( currentWaypointSet == (struct waypointDef*)waypoints )
			numPointsInCurrentSet = NUMBER_POINTS;
		else numPointsInCurrentSet = NUMBER_RTL_POINTS;
		return numPointsInCurrentSet;
	}
#else
		if ( currentWaypointSet == (struct waypointDef*)waypoints )
			numPointsInCurrentSet = NUMBER_POINTS;
		else numPointsInCurrentSet = NUMBER_RTL_POINTS;
		return numPointsInCurrentSet;
#endif
}

int xlateWPbyIndex( int idx, LPEEWAYPOINT store )
{
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	if ( EE_wp_pos >= 0 )	// using EE waypoints
	{
		if ( store->type != 3 ) {
			SetupReadEEWaypoint( store, idx );
			return -1;
		} else {
			xlateMLwaypoint( &udb_default, store );
			return idx;
		}
	} else {
		store->type = 3, store->ver = 3;
		if ( idx >= NUMBER_POINTS ) idx = (NUMBER_POINTS - 1); else ;
		udb_default = currentWaypointSet[idx];
		xlateUDBwaypoint( store, &udb_default, idx );
		return idx;
	}
#else
	udb_default = currentWaypointSet[idx];
	return idx;
#endif
}

void injectWPatIndex( int idx )
{
	if ( idx > 3 ) return; else ;
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
	wp_inject[idx] = udb_default;
#else
	wp_inject[idx] = udb_default;
#endif
}

void run_flightplan( void )
{
	// first run any injected wp from the serial port
	if (wp_inject_pos == WP_INJECT_READY)
	{
		struct relWaypointDef current_waypoint = wp_to_relative( wp_inject[0] ) ;
		set_goal( GPSlocation, current_waypoint.loc ) ;
		set_camera_view( current_waypoint.viewpoint ) ;
		setBehavior( current_waypoint.flags ) ;
		compute_bearing_to_goal() ;
		wp_inject_pos = 0 ;
		
		return ;
	}
	
	// steering is based on cross track error.
 	// waypoint arrival is detected computing distance to the "finish line".
	
	// note: locations are measured in meters
	//		 velocities are in centimeters per second
	
	// locations have a range of +-32000 meters (20 miles) from origin
	
	if ( desired_behavior._.altitude )
	{
		if ( abs(IMUheight - goal.height) < ((int) HEIGHT_MARGIN ))
			next_waypoint() ;
	}
	else
	{
		if ( desired_behavior._.cross_track )
		{
			if ( tofinish_line < waypointRadius ) // crossed the finish line
			{
				if ( desired_behavior._.loiter )
					set_goal( GPSlocation, wp_to_relative(currentWaypointSet[waypointIndex]).loc ) ;
				else
					next_waypoint() ;
			}
		}
		else
		{
			if ( (tofinish_line < waypointRadius) || (togoal.x < waypointRadius) ) // crossed the finish line
			{
				if ( desired_behavior._.loiter )
					set_goal( GPSlocation, wp_to_relative(currentWaypointSet[waypointIndex]).loc ) ;
				else
					next_waypoint() ;
			}
		}
	}
	
	return ;
}


void flightplan_live_begin( void )
{
	wp_inject_pos = 0 ;
	return ;
}


void flightplan_live_received_byte( unsigned char inbyte )
{
	if (wp_inject_pos < sizeof(wp_inject_byte_order))
	{
		((unsigned char*)(&wp_inject[0]))[wp_inject_byte_order[wp_inject_pos++]] = inbyte ;
	}
	else if (wp_inject_pos == sizeof(wp_inject_byte_order))
	{
		wp_inject_pos++ ;
	}
	
	return ;
}


void flightplan_live_commit( void )
{
	if (wp_inject_pos == sizeof(wp_inject_byte_order))
	{
		wp_inject_pos = WP_INJECT_READY ;
	}
	else
	{
		wp_inject_pos = 0 ;
	}
	return ;
}

//void ReadWaypoint( int dest, int src, int num )
//{
//	unsigned char *ramAdr = (unsigned char *)&wp_inject[0];
//	WORD eeAdr = EE_WAYPOINTS_START;
//
//	if ( cEEpresent == 0 )	// no ee present so indicate end in wp_inject array
//	{
//		memset( &wp_inject[0], 0xffff, sizeof(wp_inject) );
//	} else {
//		if ( (num <= 4) && (num >= 1) && (dest <= 3) && (dest >= 0 )&& (src < EE_WAYPOINTS_MAX) )
//		{	// check valid inputs, ~185 in 4k bytes of ee
//			num &= 0x3, dest &= 0x3;		// bound inputs
//			if ( (num + dest) > 4 ) num = (num + dest) & 0x3;
//			ramAdr = (unsigned char *)&wp_inject[dest];
//			eeAdr += sizeof(struct waypointDef) * src;
//			EE_Read( sizeof(struct waypointDef) * num, eeAdr, ramAdr );
//		};
//	}
//}
//
//void WriteWaypoint( int dest, int src, int num )
//{
//	unsigned char *ramAdr = (unsigned char *)&wp_inject[0];
//	WORD eeAdr = EE_WAYPOINTS_START;
//
//	if ( cEEpresent == 0 )	// no ee present so indicate end in wp_inject array
//	{
//		return;
//	} else {
//		if ( (num <= 4) && (num >= 1) && (src <= 3) && (src >= 0 )&& (dest < EE_WAYPOINTS_MAX) )
//		{	// check valid inputs, ~185 in 4k bytes of ee
//			num &= 0x7, src &= 0x3;		// bound inputs
//			if ( (num + src) > 4 ) num = (num + src) & 0x3;
//			ramAdr = (unsigned char *)&wp_inject[src];
//			eeAdr += sizeof(struct waypointDef) * dest;
//			EE_Write( sizeof(struct waypointDef) * num, eeAdr, ramAdr );
//		};
//	}
//}

LPEEWAYPOINT wpReadDest, wpWriteSrc;
int wpReadSrc, wpWriteDest;

void SetupWriteEEWaypoint( int dest, LPEEWAYPOINT src )
{
	if ( !flags._.write_EE_wp )		// ignore if already doing it
	{
		flags._.write_EE_wp = 1;	// set it up
		wpWriteDest = dest, wpWriteSrc = src;
	}

}

// void WriteEEWaypoint( int dest, LPEEWAYPOINT src )
void WriteEEWaypoint( void )
{
	WORD eeAdr = EE_WAYPOINTS_START;

	if ( (cEEpresent == 0) || EE_Active  )	// no ee present or busy so have to ignore
	{
		return;
	} else {
		if ( (wpWriteDest >= 0) && (wpWriteDest < EE_WAYPOINTS_MAX) )
		{	// check valid inputs, ~128 in 8k bytes of ee
			eeAdr += sizeof(EEWAYPOINT) * wpWriteDest;
			while ( EE_Write( sizeof(EEWAYPOINT), eeAdr, (unsigned char *)wpWriteSrc ) >= 0)
					indicate_loading_main;
			while (EE_Active != 0)		// this forces a wait in this function
				indicate_loading_main;
		};
	}
}

void SetupReadEEWaypoint( LPEEWAYPOINT dest, int src )
{
	if ( !flags._.read_EE_wp )		// ignore if already doing it
	{
		flags._.read_EE_wp = 1;		// set it up
		wpReadDest = dest, wpReadSrc = src;
	}
}

//void ReadEEWaypoint( LPEEWAYPOINT dest, int src )
void ReadEEWaypoint( void )
{
	WORD eeAdr = EE_WAYPOINTS_START;

	if ( (cEEpresent == 0) || EE_Active  )	// no ee present or busy so have to ignore
	{
		return;
	} else {
		if ( (wpReadSrc >= 0) && (wpReadSrc < EE_WAYPOINTS_MAX) )
		{	// check valid inputs, 128 in 8k bytes of ee, 256 in 16k
			eeAdr += sizeof(EEWAYPOINT) * wpReadSrc;
			while ( EE_Read( sizeof(EEWAYPOINT), eeAdr, (unsigned char *)wpReadDest ) <= 0)
				indicate_loading_main;
			while (EE_Active != 0)		// this forces a wait in this function
				indicate_loading_main;

		};
	}
}

#endif
