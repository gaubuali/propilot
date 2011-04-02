/** @file
 *	@brief MAVLink comm protocol.
 *	@see http://pixhawk.ethz.ch/software/mavlink
 *	 Generated on Tuesday, February 15 2011, 15:57 UTC
 */
#ifndef UAVDB_H
#define UAVDB_H

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

#include "protocol.h"

#define MAVLINK_ENABLED_UAVDB


#include "common/common.h"
// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 0
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 0
#endif

// ENUM DEFINITIONS


// MESSAGE DEFINITIONS

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
#endif
