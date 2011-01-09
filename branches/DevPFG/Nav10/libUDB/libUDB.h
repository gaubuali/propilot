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


#ifndef LIB_UDB_H
#define LIB_UDB_H


#include "options.h"
#include "fixDeps.h"
#include "libUDB_defines.h"
#include "magnetometerOptions.h"
#include <dsp.h>
#define _DI()	__asm__ volatile("disi #0xFFF")
#define _EI()	__asm__ volatile("disi #0")

////////////////////////////////////////////////////////////////////////////////
// libUDB.h defines the API for accessing the UDB hardware through libUDB
//
// libUDB requires an options.h file be provided that defines at least the following constants:
// 
// #define NUM_INPUTS
// #define NUM_OUTPUTS
// 
// #define FAILSAFE_INPUT_CHANNEL
// #define FAILSAFE_INPUT_MIN
// #define FAILSAFE_INPUT_MAX
// 
// #define NORADIO
// #define SERVOSAT


////////////////////////////////////////////////////////////////////////////////
// Initialize the UDB

// Call this once soon after the board boots up
void udb_init(void);

// Start the UDB running
// Once you have everything else set up, call udb_run().
// This function will not return.
// From this point on, everything is event-driven.
// Your code should respond to the Callbacks below.
void udb_run(void);

// If you use any of the Vector/Matrix routines from the MicroChip library,
// call udb_setDSPLibInUse(true) before using any of these routines, and then
// call udb_setDSPLibInUse(false) when you're done.
void udb_setDSPLibInUse(boolean inUse);


////////////////////////////////////////////////////////////////////////////////
// Run Background Tasks

// Implement this callback to perform periodic background tasks (low priority).
// It is called once every 0.5 seconds.
void udb_background_callback_periodic(void);			// Callback

// Call this function to trigger the udb_background_callback_triggered() function
// from a low priority ISR.
void udb_background_trigger(void);

// Implement this callback to respond to udb_background_trigger() in
// the background (low priority)
void udb_background_callback_triggered(void);			// Callback

// This function returns the current CPU load as an integer percentage value
// from 0-100.
unsigned char udb_cpu_load(void);


////////////////////////////////////////////////////////////////////////////////
// Radio Inputs / Servo Outputs

// These are the values of the radio input channels.  Each channel will be a
// value between approximately 2000 and 4000, with 3000 being the center.
// Treat udb_pwIn values as readonly.
#define RC_START 8
#define AUX_START 16
extern int udb_pwIn[];		// pulse widths of radio inputs

// These are the recorded trim values of the radio input channels.
// These values are recorded when you call the udb_servo_record_trims()
// function.
// Each channel will be a value between approximately 2000 and 4000.
// Treat udb_pwTrim values as readonly.
extern int udb_pwTrim[];	// initial pulse widths for trimming

// These are the servo channel values that will be sent out to the servos.
// Set these values in your implementation of the udb_servo_callback_prepare_outputs()
// callback.
// Each channel should be set to a value between 2000 and 4000.
extern int udb_pwOut[];		// pulse widths for servo outputs

#if (BOARD_TYPE == ASPG_BOARD)
// These are the low level digital objects, includes all the RC in and servo out
// structures plus the timer / general inputs and outputs. see ConfigASPG.h
#define RC_PIN_START 1
#define SERVO_PIN_START 9
extern PIN DIO[] __attribute__ ((section(".myDataSection"),address(0x2700)));		// digital I/O handling
#endif

// This read-only value holds flags that tell you, among other things,
// whether the receiver is currently receiving values from the transmitter.
extern union udb_fbts_byte { struct udb_flag_bits _ ; char B ; } udb_flags ;

// This takes a servo out value, and clips it to be within
// 3000-1000*SERVOSAT and 3000+1000*SERVOSAT (2000-4000 by default).
int  udb_servo_pulsesat(long pw);

// Call this funtion once at some point soon after
// the UDB has booted up and the radio is on.
void udb_servo_record_trims(void);

// Implement this callback to prepare the pwOut values.
// It is called at 40Hz (once every 25ms).
void udb_servo_callback_prepare_outputs(void);			// Callback

// Call this function to set the digital output to 0 or 1.
// This can be used to do things like triggering cameras, turning on
// lights, etc.
void udb_set_action_state(boolean newValue);


////////////////////////////////////////////////////////////////////////////////
// Raw Accelerometer and Gyroscope(rate) Values
extern struct ADchannel udb_xaccel, udb_yaccel, udb_zaccel;	// x, y, and z accelerometer channels
extern struct ADchannel udb_xrate, udb_yrate, udb_zrate;	// x, y, and z gyro channels
extern struct ADchannel udb_vref;							// reference voltage

// Calibrate the sensors
// Call this function once, soon after booting up, after a few seconds of
// holding the UDB very still.
void udb_a2d_record_offsets(void);


////////////////////////////////////////////////////////////////////////////////
// Magnetometer
// If the magnetometer is connected and enabled, these will be the raw values, and the
// calibration offsets.
extern fractional udb_magFieldBody[3];
extern fractional udb_magOffset[3];

// Implement this callback to make use of the magetometer data.  This is called each
// time the magnetometer reports new data.
void udb_magnetometer_callback_data_available(void);	// Callback
void rxMagnetometer(void);  // service the magnetometer
void doneReadMagData(void);	// use data
#define magCDindex 1	// this driver uses CD[1]

////////////////////////////////////////////////////////////////////////////////
// LEDs
// Use this to toggle an LED.  Use the LED definition from the Config*.h files,
// for example udb_led_toggle(LED_RED);
#define udb_led_toggle(x)		((x) = !(x))

////////////////////////////////////////////////////////////////////////////////
// I2C2
void I2C_Start( int );
void I2C_Reset( void );
extern I2C_Action uI2C_Commands[];		// command buffer, see I2C_aspg.c
extern I2CCMD CC;		// peripheral driver command buffer, never mess with this
extern I2CCMD CD[8];	// device driver command buffers - [0] reserved
extern int EE_Write_Timer;	// simple counter decremented to 0 in T3 interrupt (servoOut_aspg.c)
extern int I2C_Timeout;		// simple counter decremented to 0 in T3 interrupt (servoOut_aspg.c)
#define I2C_BUF_LEN 128+16		// page write size + enough bytes to send an address
extern unsigned char __attribute__ ((section(".myDataSection"),address(0x2270))) I2C_buffer[I2C_BUF_LEN];	// peripheral buf
extern void (* I2C_call_back[] ) ( void );
extern struct tagI2C_flags I2C_flags;	// defined in ConfigASPG.h

////////////////////////////////////////////////////////////////////////////////
// GPS IO

// Set the GPS serial data rate.
void udb_gps_set_rate(int rate);
boolean udb_gps_check_rate(int rate);  //returns true if the rate arg is the current rate

// Output one character to the GPS
void udb_gps_send_char(char txchar);

// Implement this cal;back to handle receiving a character from the GPS
void udb_gps_callback_received_char(char rxchar);		// Callback

#if (BOARD_TYPE == ASPG_BOARD)
// Output packet to the serial port
// Don't mix this with the serial_start_sending / serial_callback mechanism
void udb_gps_send_packet( unsigned char *ucpData, int len );
#endif


////////////////////////////////////////////////////////////////////////////////
// Serial IO

// Set the serial port data rate.  Use the UDB_BAUD_* constants defined in the Config*.h
// files.
void udb_serial_set_rate(long int rate);

// Call this function to initiate sending a string of characters to the serial port
void udb_serial_start_sending(void);

// Output one character to the serial port
// Don't mix this with the serial_start_sending / serial_callback mechanism
void udb_serial_send_char( char outchar );

// Implement this callback to tell the UDB what character is next to send on the serial port.
// Return 0 to stop sending this string of characters.
char udb_serial_callback_get_char_to_send(void);		// Call back

// Implement this call back to handle receiving a character from the serial port
void udb_serial_callback_received_char(char rxchar);	// Call back

#if (BOARD_TYPE == ASPG_BOARD)
// Output packet to the serial port
// Don't mix this with the serial_start_sending / serial_callback mechanism
void udb_serial_send_packet( unsigned char *ucpData, int len );
void udb_serial_send_string( unsigned char *ucpData );
#endif


////////////////////////////////////////////////////////////////////////////////
// On Screen Display

void osd_spi_write(char address, char byte) ;
void osd_spi_write_byte(char byte) ; // Used for writing chars while in auto-increment mode
void osd_spi_write_location(char row, char column) ; // Set where on screen to write the next char
void osd_spi_write_string(const unsigned char *str) ; // OSD chars, not ASCII

#define NUM_FLAG_ZERO_PADDED	1	// When num_digits > 0, left-pad with zeros instead of spaces
#define NUM_FLAG_SIGNED			2	// Reserve space for a - sign to the left of the number
void osd_spi_write_number(long val, char num_digits, char num_flags, char header, char footer) ;
// num_digits == 0 means left aligned
// header or footer == 0 means skip the header or footer char

#endif