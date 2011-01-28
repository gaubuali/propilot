
#define MIX_NUM_INPUTS 8
#define MIX_NUM_OUTPUTS 8
#define SERVO_CENTER_PULSE 7500
#define SERVO_PULSE_RANGE 3500
#define SERVO_PULSE_REV -3500

#define UNUSED 0
#define DCM_ROLL 1
#define DCM_PITCH 2
#define DCM_YAW 3
#define DCM_THROTTLE 4
#define DCM_CAM_PITCH 5
#define DCM_CAM_YAW 6
#define DCM_CAM_ROLL 7
#define RC_THROTTLE 8
#define RC_ROLL 9
#define RC_PITCH 10
#define RC_YAW 11
#define RC_MODE_FAILSAFE 12
#define RC_AUX1_FLAPS 13
#define RC_AUX2_CAM_P 14
#define RC_AUX3_CAM_Y 15

#define UNUSED_MIX 0
#define BALANCED_FULL_FACTOR 1
#define BALANCED_NO_FACTOR 2
#define BALANCED_HALF_FACTOR 3
#define SPARE 4
#define SIMPLE_FACTOR 5
#define SIMPLE_FACTOR_2_INPUT 6
#define MANUAL_SIMPLE 7
#define MANUAL_SIMPLE_2_INPUT 8
#define ASSIST_SIMPLE 9
#define ASSIST_SIMPLE_2_INPUT 10
#define AUTOPILOT_SIMPLE 11
#define AUTOPILOT_SIMPLE_2_INPUT 12
#define POSITIVE_DIFFERENTIAL 13
#define NEGATIVE_DIFFERENTIAL 14
#define FIXED_OUTPUT_OVERRIDE 15

MIXER pMixers[MIX_NUM_OUTPUTS+1][MIX_PER_CHANNEL]  __attribute__ ((section(".myDataSection"),address(0x2100))) = {
{
	{	/* Channel1 (Throttle) */
		.pType = { BALANCED_HALF_FACTOR, RC_THROTTLE, DCM_THROTTLE, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 5000, 10000 } }, }, { {         /*Channel2 (Aileron1) */
		.pType = { BALANCED_HALF_FACTOR, RC_ROLL, DCM_ROLL, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { NEGATIVE_DIFFERENTIAL, DCM_ROLL, UNUSED, toQ15( 0.200 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 4000, 11000 } }, }, { {         /*Channel3 (Elevator) */
		.pType = { BALANCED_HALF_FACTOR, RC_PITCH, DCM_PITCH, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 4000, 11000 } }, }, { {         /*Channel4 (Rudder) */
		.pType = { BALANCED_HALF_FACTOR, RC_YAW, DCM_YAW, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 4000, 11000 } }, }, { {         /*Channel5 (FLAPS) */
		.nType = { SIMPLE_FACTOR, RC_AUX1_FLAPS, UNUSED, toQ15( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 4000, 11000 } }, }, { {         /*Channel6 (Aileron2) */
		.pType = { BALANCED_HALF_FACTOR, RC_ROLL, DCM_ROLL, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.200 ) }, }, {
		.nType = { POSITIVE_DIFFERENTIAL, DCM_ROLL, UNUSED, toQ15( 0.200 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_REV }, }, {
		.iScales = { 4000, 11000 } }, }, { {         /*Channel7 (CAM_P) */
		.pType = { BALANCED_FULL_FACTOR, RC_AUX2_CAM_P, DCM_CAM_PITCH, UNUSED, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 4000, 11000 } }, }, { {         /*Channel8 (CAM_Y) */
		.pType = { BALANCED_FULL_FACTOR, RC_AUX3_CAM_Y, DCM_CAM_YAW, UNUSED, toQ10( 1.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
		.iScales = { SERVO_CENTER_PULSE, SERVO_PULSE_RANGE }, }, {
		.iScales = { 4000, 11000 }, }         /* END */
	}
};


											
											
//#define MIX_NUM_INPUTS 8
//#define MIX_NUM_OUTPUTS 8
//#define SERVO_CENTER_PULSE 3000
//#define SERVO_PULSE_RANGE 1000
//#define SERVO_PULSE_REV -1000
//
//
//#define UNUSED 0
//#define DCM_ROLL 1
//#define DCM_PITCH 2
//#define DCM_YAW 3
//#define DCM_THROTTLE 4
//#define DCM_CAM_PITCH 5
//#define DCM_CAM_YAW 6
//#define DCM_CAM_ROLL 7
//#define RC_THROTTLE 8
//#define RC_ROLL 9
//#define RC_PITCH 10
//#define RC_YAW 11
//#define RC_MODE_FAILSAFE 12
//#define RC_AUX1_ROLL2 13
//#define RC_AUX2_FLAPS 14
//#define RC_AUX3 15
//
//#define UNUSED_MIX 0
//#define BALANCED_FULL_FACTOR 1
//#define BALANCED_NO_FACTOR 2
//#define BALANCED_HALF_FACTOR 3
//#define SPARE 4
//#define SIMPLE_FACTOR 5
//#define SIMPLE_FACTOR_2_INPUT 6
//#define MANUAL_SIMPLE 7
//#define MANUAL_SIMPLE_2_INPUT 8
//#define ASSIST_SIMPLE 9
//#define ASSIST_SIMPLE_2_INPUT 10
//#define AUTOPILOT_SIMPLE 11
//#define AUTOPILOT_SIMPLE_2_INPUT 12
//#define POSITIVE_DIFFERENTIAL 13
//#define NEGATIVE_DIFFERENTIAL 14
//#define FIXED_OUTPUT_OVERRIDE 15
//
//
//
//
//
//MIXER pMixers[MIX_NUM_OUTPUTS+1][MIX_PER_CHANNEL]  __attribute__ ((section(".myDataSection"),address(0x1100))) = {
//{
//	{	/* Channel1 (Throttle) */
//		.pType = { BALANCED_HALF_FACTOR, RC_THROTTLE, DCM_THROTTLE, RC_MODE_FAILSAFE, toQ10( 0.800 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.100 ) }, }, {
//		.iScales = { 3000, 1000 }}, }, { {         /*Channel2 (Aileron1) */
//		.pType = { BALANCED_HALF_FACTOR, RC_ROLL, DCM_ROLL, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.200 ) }, }, {
//		.nType = { NEGATIVE_DIFFERENTIAL, DCM_ROLL, UNUSED, toQ15( 0.200 ) }, }, {
//		.iScales = { 3000, 1000 }}, }, { {         /*Channel3 (Elevator) */
//		.pType = { BALANCED_HALF_FACTOR, RC_PITCH, DCM_PITCH, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.iScales = { 3000, 1000 }}, }, { {         /*Channel4 (Rudder) */
//		.pType = { BALANCED_HALF_FACTOR, RC_YAW, DCM_YAW, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.iScales = { 3000, 1000 }}, }, { {         /*Channel5 (AUX1) */
//		.nType = { SIMPLE_FACTOR, RC_MODE_FAILSAFE, UNUSED, toQ15( 1.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.iScales = { 3000, -1000 }}, }, { {         /*Channel6 (Aileron2) */
//		.pType = { BALANCED_HALF_FACTOR, RC_AUX1_ROLL2, DCM_ROLL, RC_MODE_FAILSAFE, toQ10( 1.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.200 ) }, }, {
//		.nType = { POSITIVE_DIFFERENTIAL, DCM_ROLL, UNUSED, toQ15( 0.200 ) }, }, {
//		.iScales = { 3000, -1000 }}, }, { {         /*Channel7 (AUX3) */
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.iScales = { 3000, 1000 }}, }, { {         /*Channel8 (AUX4) */
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.nType = { UNUSED_MIX, UNUSED, UNUSED, toQ15( 0.000 ) }, }, {
//		.iScales = { 3000, 1000 }, }         /* */
//	}
//};
//
//
