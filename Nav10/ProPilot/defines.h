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

#ifndef DEFINES_H
#define DEFINES_H

#include "../libDCM/libDCM.h"
#include "gain_variables.h"


#define BYTECIR_TO_DEGREE 92160		// (360.0/256 * 2^16)


////////////////////////////////////////////////////////////////////////////////
// states.c
void init_states( void ) ;

extern int waggle ;

#define CALIB_PAUSE 21
#define STANDBY_PAUSE 48 // pause for 16 seconds of runs through the state machine
#define NUM_WAGGLES 4 // waggle 4 times during the end of the standby pause (this number must be less than STANDBY_PAUSE)
#define WAGGLE_SIZE 300

struct flag_bits {
			unsigned int unused					: 2 ;
			unsigned int read_EE_wp				: 1 ;
			unsigned int write_EE_wp			: 1 ;
			unsigned int read_EE_param			: 1 ;
			unsigned int write_EE_param			: 1 ;
			unsigned int save_origin   			: 1 ;
			unsigned int GPS_steering			: 1 ;
			unsigned int pitch_feedback			: 1 ;
			unsigned int altitude_hold_throttle	: 1 ;
			unsigned int altitude_hold_pitch	: 1 ;
			unsigned int man_req				: 1 ;
			unsigned int auto_req				: 1 ;
			unsigned int home_req				: 1 ;
			unsigned int rtl_hold				: 1 ;
			unsigned int f13_print_req			: 1 ;
			} ;
			
union fbts_int { struct flag_bits _ ; int WW ; } ;
extern union fbts_int flags ;


////////////////////////////////////////////////////////////////////////////////
// servoPrepare.c
void init_servoPrepare( void ) ;



////////////////////////////////////////////////////////////////////////////////
// Control code - rollCntrl.c, pitchCntrl.c, yawCntrl.c, altitudeCntrl.c
void rollCntrl( void ) ;
void pitchCntrl( void ) ;
void yawCntrl( void ) ;
void altitudeCntrl( void ) ;
void setTargetAltitude(int targetAlt) ;

extern int pitch_control, roll_control, yaw_control, throttle_control ;
extern union longww throttleFiltered ;
extern int pitchAltitudeAdjust ;

// AltitudeHold type
#define AH_NONE				0
#define AH_PITCH_ONLY		1
#define AH_FULL				3



////////////////////////////////////////////////////////////////////////////////
// servoMix.c
void servoMix( void ) ;
void cameraServoMix( void ) ;

// Choose the type of air frame by setting AIRFRAME_TYPE in options.h
// See options.h for a description of each type
#define AIRFRAME_STANDARD			0
#define AIRFRAME_VTAIL				1
#define AIRFRAME_DELTA				2
#define AIRFRAME_HELI				3		// Untested

// Negate VALUE if NEEDS_REVERSING is true
#define REVERSE_IF_NEEDED(NEEDS_REVERSING, VALUE)		((NEEDS_REVERSING) ? (-(VALUE)) : (VALUE))

extern int cam_pitch_servo_pwm_delta ;  
extern int cam_yaw_servo_pwm_delta ;
long cam_pitchServoLimit( long pwm_pulse) ;
long cam_yawServoLimit( long pwm_pulse) ;



////////////////////////////////////////////////////////////////////////////////
// navigation.c
void set_goal( struct relative3D fromPoint , struct relative3D toPoint ) ;
void compute_bearing_to_goal ( void ) ;
void process_flightplan( void ) ;
int determine_navigation_deflection( char navType ) ;


struct behavior_flag_bits {
			unsigned int takeoff		: 1 ;	// disable altitude interpolation for faster climbout
			unsigned int inverted		: 1 ;	// fly iverted
			unsigned int hover			: 1 ;	// hover the plane
			unsigned int rollLeft		: 1 ;				// unimplemented
			unsigned int rollRight		: 1 ;				// unimplemented
			unsigned int trigger		: 1 ;	// trigger action
			unsigned int loiter			: 1 ;	// stay on the current waypoint
			unsigned int land			: 1 ;	// throttle off
			unsigned int absolute		: 1 ;	// absolute waypoint
			unsigned int altitude		: 1 ;	// climb/descend to goal altitude
			unsigned int cross_track	: 1 ;	// use cross-tracking navigation
			unsigned int unused			: 5 ;
			} ;

union bfbts_word { struct behavior_flag_bits _ ; int W; } ;

struct relWaypointDef { struct relative3D loc ; int flags ; struct relative3D viewpoint ; } ;
struct waypointDef { 
	struct waypoint3D loc ; 		// fly to
	int flags ; 					// flight type / action
	struct waypoint3D viewpoint ;	// camera target
	int seq;						// sequence # = waypoint #
	int radius ; 					// accept radius
	union bfbts_word behavior ;		// actions
	int	channel;					// channel to perform action on / with
	int val1;						// action parameters
	int val2;						// action parameters
 } ;

typedef struct __EEwaypoint { 
	char type;	// type code, 0 or 0xff = invalid / unused, 1 = UDB, 3 = MAVlink
	char ver;	// version code, 0 or 0xff = invalid / unused, 1 = UDB, 3 = Mavlink V3
	union 	{
		BYTE	bytes[62];		// pad struct out to 64 bytes
		struct waypointDef udb;
			};
} EEWAYPOINT, *LPEEWAYPOINT;

#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)
void xlateMLwaypoint( struct waypointDef *, LPEEWAYPOINT );
void xlateUDBwaypoint( LPEEWAYPOINT, struct waypointDef *, int );
int xlateWPbyIndex( int, LPEEWAYPOINT );
int getNumPointsInCurrentSet( void );
void SetupReadEEWaypoint( LPEEWAYPOINT, int );
void SetupWriteEEWaypoint( int, LPEEWAYPOINT );
void ReadEEWaypoint( void );
void WriteEEWaypoint( void );
extern struct waypointDef udb_default IMPORTANT;
extern EEWAYPOINT wpTemp IMPORTANT;		// storage for ML send / rec wp's
void injectWPatIndex( int );
int set_waypoint_by_index( int );
#endif

struct waypointparameters { int x ; int y ; int cosphi ; int sinphi ; signed char phi ; int height ; int fromHeight; int legDist; } ;
extern struct waypointparameters goal ;

extern struct relative2D togoal ;
extern int tofinish_line ;
extern int progress_to_goal ; // Fraction of the way to the goal in the range 0-4096 (2^12)
extern signed char	desired_dir ;
extern int waypointRadius PARAMETER;


////////////////////////////////////////////////////////////////////////////////
// Flight Planning modules - flightplan-waypoints.c and flightplan-logo.c
void init_flightplan( int flightplanNum ) ;
boolean use_fixed_origin( void ) ;
struct absolute3D get_fixed_origin( void ) ;
long get_fixed_altitude( void ) ;
void run_flightplan( void ) ;

void flightplan_live_begin( void ) ;
void flightplan_live_received_byte( unsigned char inbyte ) ;
void flightplan_live_commit( void ) ;

#if (FLIGHT_PLAN_TYPE == FP_WAYPOINTS)
extern int numPointsInCurrentSet PARAMETER;
extern int EE_wp_pos PARAMETER;
int SetWaypointToIndex( int );
#endif

// Failsafe Type
#define FAILSAFE_RTL					1
#define FAILSAFE_MAIN_FLIGHTPLAN		2

#define FP_WAYPOINTS					1
#define FP_LOGO							2



////////////////////////////////////////////////////////////////////////////////
// behavior.c
void init_behavior( void ) ;
void setBehavior( int newBehavior ) ;
void updateBehavior( void ) ;
void updateTriggerAction( void ) ;
boolean canStabilizeInverted( void ) ;
boolean canStabilizeHover( void ) ;

#define F_NORMAL						   0
#define F_TAKEOFF						   1
#define F_INVERTED						   2
#define F_HOVER							   4
#define F_ROLL_LEFT						   8
#define F_ROLL_RIGHT					  16
#define F_TRIGGER						  32
#define F_LOITER						  64
#define F_LAND							 128
#define F_ABSOLUTE						 256
#define F_ALTITUDE_GOAL					 512
#define F_CROSS_TRACK					1024

extern int current_orientation ;
extern union bfbts_word desired_behavior ;

#define TRIGGER_TYPE_NONE				 0
#define TRIGGER_TYPE_SERVO				 1
#define TRIGGER_TYPE_DIGITAL			 2

#define TRIGGER_PULSE_HIGH				 4
#define TRIGGER_PULSE_LOW				 8
#define TRIGGER_TOGGLE					16
#define TRIGGER_REPEATING				32



////////////////////////////////////////////////////////////////////////////////
// serialIO.c
void init_serial( void ) ;
void serial_output( char* format, ... ) ;
void serial_output_8hz( void ) ;
void mavlink_output_40hz( void );


////////////////////////////////////////////////////////////////////////////////
// cameraCntrl.c
void set_camera_view( struct relative3D current_view ) ;
void compute_camera_view( void ) ;
void cameraCntrl( void ) ;

#define CAM_VIEW_LAUNCH					{ 0, 0, 0 }



////////////////////////////////////////////////////////////////////////////////
// mp_osd.c
void osd_countdown(int countdown);

#define OSD_NTSC			0
#define OSD_PAL				1


////////////////////////////////////////////////////////////////////////////////
// GPS Parsers - gpsParseSTD.c, gpsParseUBX.c
// FIXME: This should move into libDCM
void gps_startup_sequence( int gpscount ) ;

#endif
