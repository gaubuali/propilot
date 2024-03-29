// MESSAGE POSITION_CONTROL_SETPOINT PACKING

#define MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT 121
#define MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT_LEN 18
#define MAVLINK_MSG_121_LEN 18

typedef struct __mavlink_position_control_setpoint_t 
{
	uint16_t id; ///< ID of waypoint, 0 for plain position
	float x; ///< x position
	float y; ///< y position
	float z; ///< z position
	float yaw; ///< yaw orientation in radians, 0 = NORTH
} mavlink_position_control_setpoint_t;


/**
 * @brief Pack a position_control_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param id ID of waypoint, 0 for plain position
 * @param x x position
 * @param y y position
 * @param z z position
 * @param yaw yaw orientation in radians, 0 = NORTH
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_position_control_setpoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t id, float x, float y, float z, float yaw)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT;

	p->id = id; // uint16_t:ID of waypoint, 0 for plain position
	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT_LEN);
}

/**
 * @brief Pack a position_control_setpoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param id ID of waypoint, 0 for plain position
 * @param x x position
 * @param y y position
 * @param z z position
 * @param yaw yaw orientation in radians, 0 = NORTH
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_position_control_setpoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t id, float x, float y, float z, float yaw)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT;

	p->id = id; // uint16_t:ID of waypoint, 0 for plain position
	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT_LEN);
}

/**
 * @brief Encode a position_control_setpoint struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param position_control_setpoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_position_control_setpoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_position_control_setpoint_t* position_control_setpoint)
{
	return mavlink_msg_position_control_setpoint_pack(system_id, component_id, msg, position_control_setpoint->id, position_control_setpoint->x, position_control_setpoint->y, position_control_setpoint->z, position_control_setpoint->yaw);
}

/**
 * @brief Send a position_control_setpoint message
 * @param chan MAVLink channel to send the message
 *
 * @param id ID of waypoint, 0 for plain position
 * @param x x position
 * @param y y position
 * @param z z position
 * @param yaw yaw orientation in radians, 0 = NORTH
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_position_control_setpoint_send(mavlink_channel_t chan, uint16_t id, float x, float y, float z, float yaw)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg.payload[0];

	p->id = id; // uint16_t:ID of waypoint, 0 for plain position
	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT_LEN;
	msg.msgid = MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT;
	msg.sysid = mavlink_system.sysid;
	msg.compid = mavlink_system.compid;
	msg.seq = mavlink_get_channel_status(chan)->current_tx_seq;
	mavlink_get_channel_status(chan)->current_tx_seq = msg.seq + 1;
	checksum = crc_calculate_msg(&msg, msg.len + MAVLINK_CORE_HEADER_LEN);
	msg.ck_a = (uint8_t)(checksum & 0xFF); ///< Low byte
	msg.ck_b = (uint8_t)(checksum >> 8); ///< High byte

	mavlink_send_msg(chan, &msg);
}

#endif

#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS_SMALL
static inline void mavlink_msg_position_control_setpoint_send(mavlink_channel_t chan, uint16_t id, float x, float y, float z, float yaw)
{
	mavlink_header_t hdr;
	mavlink_position_control_setpoint_t payload;
	uint16_t checksum;
	mavlink_position_control_setpoint_t *p = &payload;

	p->id = id; // uint16_t:ID of waypoint, 0 for plain position
	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT_LEN;
	hdr.msgid = MAVLINK_MSG_ID_POSITION_CONTROL_SETPOINT;
	hdr.sysid = mavlink_system.sysid;
	hdr.compid = mavlink_system.compid;
	hdr.seq = mavlink_get_channel_status(chan)->current_tx_seq;
	mavlink_get_channel_status(chan)->current_tx_seq = hdr.seq + 1;
	mavlink_send_mem(chan, (uint8_t *)&hdr.STX, MAVLINK_NUM_HEADER_BYTES );

	crc_init(&checksum);
	checksum = crc_calculate_mem((uint8_t *)&hdr.len, &checksum, MAVLINK_CORE_HEADER_LEN);
	checksum = crc_calculate_mem((uint8_t *)&payload, &checksum, hdr.len );
	hdr.ck_a = (uint8_t)(checksum & 0xFF); ///< Low byte
	hdr.ck_b = (uint8_t)(checksum >> 8); ///< High byte

	mavlink_send_mem(chan, (uint8_t *)&payload, hdr.len);
	mavlink_send_mem(chan, (uint8_t *)&hdr.ck_a, MAVLINK_NUM_CHECKSUM_BYTES);
}

#endif
// MESSAGE POSITION_CONTROL_SETPOINT UNPACKING

/**
 * @brief Get field id from position_control_setpoint message
 *
 * @return ID of waypoint, 0 for plain position
 */
static inline uint16_t mavlink_msg_position_control_setpoint_get_id(const mavlink_message_t* msg)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	return (uint16_t)(p->id);
}

/**
 * @brief Get field x from position_control_setpoint message
 *
 * @return x position
 */
static inline float mavlink_msg_position_control_setpoint_get_x(const mavlink_message_t* msg)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from position_control_setpoint message
 *
 * @return y position
 */
static inline float mavlink_msg_position_control_setpoint_get_y(const mavlink_message_t* msg)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from position_control_setpoint message
 *
 * @return z position
 */
static inline float mavlink_msg_position_control_setpoint_get_z(const mavlink_message_t* msg)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field yaw from position_control_setpoint message
 *
 * @return yaw orientation in radians, 0 = NORTH
 */
static inline float mavlink_msg_position_control_setpoint_get_yaw(const mavlink_message_t* msg)
{
	mavlink_position_control_setpoint_t *p = (mavlink_position_control_setpoint_t *)&msg->payload[0];
	return (float)(p->yaw);
}

/**
 * @brief Decode a position_control_setpoint message into a struct
 *
 * @param msg The message to decode
 * @param position_control_setpoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_position_control_setpoint_decode(const mavlink_message_t* msg, mavlink_position_control_setpoint_t* position_control_setpoint)
{
	memcpy( position_control_setpoint, msg->payload, sizeof(mavlink_position_control_setpoint_t));
}
