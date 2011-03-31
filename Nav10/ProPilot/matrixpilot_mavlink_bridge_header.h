/* MAVLink adapter header */
#ifndef MATRIXPILOT_MAVLINK_BRIDGE_HEADER_H
#define MATRIXPILOT_MAVLINK_BRIDGE_HEADER_H
 
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#include "inttypes.h"
#include "mavlink_types.h"
mavlink_system_t mavlink_system PARAMETER = {
	.sysid = 1, .compid = MAV_COMP_ID_IMU
};

/**
 * @brief Send one char (uint8_t) over a comm channel
 *
 * @param chan MAVLink channel to use, usually MAVLINK_COMM_0 = UART0
 * @param ch Character to send
 *

extern void uart1_transmit(uint8_t ch) ;

static inline void comm_send_ch(mavlink_channel_t chan, uint8_t ch)
{
   	// MatrixPilot currently only transmits out of one channel for telemetry
	// so mavlink_t chan is ignored
   
    uart1_transmit(ch);
 
} */

#define comm_send_ch( chan, c) udb_serial_send_char( c )

#include "common/mavlink.h"

//extern void uart1_transmit(unsigned char) ; 

/* Struct that stores the communication settings of this system.
   you can also define / alter these settings elsewhere, as long
   as they're included BEFORE mavlink.h.
   So you can set the
 
   mavlink_system.sysid = 100; // System ID, 1-255
   mavlink_system.compid = 50; // Component/Subsystem ID, 1-255
 
   Lines also in your main.c, e.g. by reading these parameter from EEPROM.
 */
 
 
#endif /* MATRIXPILOT_MAVLINK_BRIDGE_HEADER_H */
