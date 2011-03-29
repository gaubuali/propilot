// MESSAGE SYS_STATUS PACKING

#define MAVLINK_MSG_ID_SYS_STATUS 2
#define MAVLINK_MSG_2_LEN 7

typedef struct __mavlink_sys_status_t 
{
	uint8_t mode; ///< System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
	uint8_t nav_mode; ///< Navigation mode, see MAV_NAV_MODE ENUM
	uint8_t status; ///< System status flag, see MAV_STATUS ENUM
	uint8_t failure; ///< Failure code description, see MAV_FAILURE ENUM
	uint8_t motor_block; ///< Motor block status flag
	uint16_t packet_drop; ///< Dropped packets
} mavlink_sys_status_t;

//#if sizeof(mavlink_sys_status_t) != 7 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a sys_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param mode System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
 * @param nav_mode Navigation mode, see MAV_NAV_MODE ENUM
 * @param status System status flag, see MAV_STATUS ENUM
 * @param failure Failure code description, see MAV_FAILURE ENUM
 * @param motor_block Motor block status flag
 * @param packet_drop Dropped packets
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sys_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t mode, uint8_t nav_mode, uint8_t status, uint8_t failure, uint8_t motor_block, uint16_t packet_drop)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SYS_STATUS;

	p->mode = mode; // uint8_t:System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
	p->nav_mode = nav_mode; // uint8_t:Navigation mode, see MAV_NAV_MODE ENUM
	p->status = status; // uint8_t:System status flag, see MAV_STATUS ENUM
	p->failure = failure; // uint8_t:Failure code description, see MAV_FAILURE ENUM
	p->motor_block = motor_block; // uint8_t:Motor block status flag
	p->packet_drop = packet_drop; // uint16_t:Dropped packets

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_sys_status_t));
}

/**
 * @brief Pack a sys_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param mode System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
 * @param nav_mode Navigation mode, see MAV_NAV_MODE ENUM
 * @param status System status flag, see MAV_STATUS ENUM
 * @param failure Failure code description, see MAV_FAILURE ENUM
 * @param motor_block Motor block status flag
 * @param packet_drop Dropped packets
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sys_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t mode, uint8_t nav_mode, uint8_t status, uint8_t failure, uint8_t motor_block, uint16_t packet_drop)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SYS_STATUS;

	p->mode = mode; // uint8_t:System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
	p->nav_mode = nav_mode; // uint8_t:Navigation mode, see MAV_NAV_MODE ENUM
	p->status = status; // uint8_t:System status flag, see MAV_STATUS ENUM
	p->failure = failure; // uint8_t:Failure code description, see MAV_FAILURE ENUM
	p->motor_block = motor_block; // uint8_t:Motor block status flag
	p->packet_drop = packet_drop; // uint16_t:Dropped packets

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_sys_status_t));
}

/**
 * @brief Encode a sys_status struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sys_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sys_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sys_status_t* sys_status)
{
	return mavlink_msg_sys_status_pack(system_id, component_id, msg, sys_status->mode, sys_status->nav_mode, sys_status->status, sys_status->failure, sys_status->motor_block, sys_status->packet_drop);
}

/**
 * @brief Send a sys_status message
 * @param chan MAVLink channel to send the message
 *
 * @param mode System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
 * @param nav_mode Navigation mode, see MAV_NAV_MODE ENUM
 * @param status System status flag, see MAV_STATUS ENUM
 * @param failure Failure code description, see MAV_FAILURE ENUM
 * @param motor_block Motor block status flag
 * @param packet_drop Dropped packets
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sys_status_send(mavlink_channel_t chan, uint8_t mode, uint8_t nav_mode, uint8_t status, uint8_t failure, uint8_t motor_block, uint16_t packet_drop)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_SYS_STATUS;
	msg.len = sizeof(mavlink_sys_status_t);
	p->mode = mode; // uint8_t:System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
	p->nav_mode = nav_mode; // uint8_t:Navigation mode, see MAV_NAV_MODE ENUM
	p->status = status; // uint8_t:System status flag, see MAV_STATUS ENUM
	p->failure = failure; // uint8_t:Failure code description, see MAV_FAILURE ENUM
	p->motor_block = motor_block; // uint8_t:Motor block status flag
	p->packet_drop = packet_drop; // uint16_t:Dropped packets

	msg.sysid = mavlink_system.sysid;
	msg.compid = mavlink_system.compid;
	msg.seq = mavlink_get_channel_status(chan)->current_tx_seq;
	mavlink_get_channel_status(chan)->current_tx_seq = mavlink_get_channel_status(chan)->current_tx_seq+1;
	checksum = crc_calculate_msg(&msg, msg.len + MAVLINK_CORE_HEADER_LEN);
	msg.ck_a = (uint8_t)(checksum & 0xFF); ///< High byte
	msg.ck_b = (uint8_t)(checksum >> 8); ///< Low byte

	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE SYS_STATUS UNPACKING

/**
 * @brief Get field mode from sys_status message
 *
 * @return System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
 */
static inline uint8_t mavlink_msg_sys_status_get_mode(const mavlink_message_t* msg)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	return (uint8_t)(p->mode);
}

/**
 * @brief Get field nav_mode from sys_status message
 *
 * @return Navigation mode, see MAV_NAV_MODE ENUM
 */
static inline uint8_t mavlink_msg_sys_status_get_nav_mode(const mavlink_message_t* msg)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	return (uint8_t)(p->nav_mode);
}

/**
 * @brief Get field status from sys_status message
 *
 * @return System status flag, see MAV_STATUS ENUM
 */
static inline uint8_t mavlink_msg_sys_status_get_status(const mavlink_message_t* msg)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	return (uint8_t)(p->status);
}

/**
 * @brief Get field failure from sys_status message
 *
 * @return Failure code description, see MAV_FAILURE ENUM
 */
static inline uint8_t mavlink_msg_sys_status_get_failure(const mavlink_message_t* msg)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	return (uint8_t)(p->failure);
}

/**
 * @brief Get field motor_block from sys_status message
 *
 * @return Motor block status flag
 */
static inline uint8_t mavlink_msg_sys_status_get_motor_block(const mavlink_message_t* msg)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	return (uint8_t)(p->motor_block);
}

/**
 * @brief Get field packet_drop from sys_status message
 *
 * @return Dropped packets
 */
static inline uint16_t mavlink_msg_sys_status_get_packet_drop(const mavlink_message_t* msg)
{
	mavlink_sys_status_t *p = (mavlink_sys_status_t *)&msg->payload[0];
	return (uint16_t)(p->packet_drop);
}

/**
 * @brief Decode a sys_status message into a struct
 *
 * @param msg The message to decode
 * @param sys_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_sys_status_decode(const mavlink_message_t* msg, mavlink_sys_status_t* sys_status)
{
	memcpy( sys_status, msg->payload, sizeof(mavlink_sys_status_t));
}
