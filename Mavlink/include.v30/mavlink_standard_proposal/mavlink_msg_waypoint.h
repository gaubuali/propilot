// MESSAGE WAYPOINT PACKING

#define MAVLINK_MSG_ID_WAYPOINT 37

typedef struct __mavlink_waypoint_t 
{
	uint16_t wp_id; ///< Waypoint ID
	uint8_t type; ///< 0: global (GPS), 1: local, 2: global orbit, 3: local orbit
	float param1; ///< Orbit to circle around the waypoint, in meters
	float param2; ///< Time that the MAV should stay inside the orbit before advancing, in milliseconds
	uint8 orbit; ///< 0: No orbit, 1: Right Orbit, 2: Left Orbit
	uint8_t current; ///< false:0, true:1
	float x; ///< local: x position, global: longitude
	float y; ///< y position: global: latitude
	float z; ///< z position: global: altitude
	uint16_t autocontinue; ///< autocontinue to next wp

} mavlink_waypoint_t;



/**
 * @brief Pack a waypoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param wp_id Waypoint ID
 * @param type 0: global (GPS), 1: local, 2: global orbit, 3: local orbit
 * @param param1 Orbit to circle around the waypoint, in meters
 * @param param2 Time that the MAV should stay inside the orbit before advancing, in milliseconds
 * @param orbit 0: No orbit, 1: Right Orbit, 2: Left Orbit
 * @param current false:0, true:1
 * @param x local: x position, global: longitude
 * @param y y position: global: latitude
 * @param z z position: global: altitude
 * @param autocontinue autocontinue to next wp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t wp_id, uint8_t type, float param1, float param2, uint8 orbit, uint8_t current, float x, float y, float z, uint16_t autocontinue)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT;

	p->wp_id = wp_id; // uint16_t:Waypoint ID
	p->type = type; // uint8_t:0: global (GPS), 1: local, 2: global orbit, 3: local orbit
	p->param1 = param1; // float:Orbit to circle around the waypoint, in meters
	p->param2 = param2; // float:Time that the MAV should stay inside the orbit before advancing, in milliseconds
	p->orbit = orbit; // uint8:0: No orbit, 1: Right Orbit, 2: Left Orbit
	p->current = current; // uint8_t:false:0, true:1
	p->x = x; // float:local: x position, global: longitude
	p->y = y; // float:y position: global: latitude
	p->z = z; // float:z position: global: altitude
	p->autocontinue = autocontinue; // uint16_t:autocontinue to next wp

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_waypoint_t));
}

/**
 * @brief Pack a waypoint message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param wp_id Waypoint ID
 * @param type 0: global (GPS), 1: local, 2: global orbit, 3: local orbit
 * @param param1 Orbit to circle around the waypoint, in meters
 * @param param2 Time that the MAV should stay inside the orbit before advancing, in milliseconds
 * @param orbit 0: No orbit, 1: Right Orbit, 2: Left Orbit
 * @param current false:0, true:1
 * @param x local: x position, global: longitude
 * @param y y position: global: latitude
 * @param z z position: global: altitude
 * @param autocontinue autocontinue to next wp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t wp_id, uint8_t type, float param1, float param2, uint8 orbit, uint8_t current, float x, float y, float z, uint16_t autocontinue)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT;

	p->wp_id = wp_id; // uint16_t:Waypoint ID
	p->type = type; // uint8_t:0: global (GPS), 1: local, 2: global orbit, 3: local orbit
	p->param1 = param1; // float:Orbit to circle around the waypoint, in meters
	p->param2 = param2; // float:Time that the MAV should stay inside the orbit before advancing, in milliseconds
	p->orbit = orbit; // uint8:0: No orbit, 1: Right Orbit, 2: Left Orbit
	p->current = current; // uint8_t:false:0, true:1
	p->x = x; // float:local: x position, global: longitude
	p->y = y; // float:y position: global: latitude
	p->z = z; // float:z position: global: altitude
	p->autocontinue = autocontinue; // uint16_t:autocontinue to next wp

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_waypoint_t));
}

/**
 * @brief Encode a waypoint struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param waypoint C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waypoint_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_waypoint_t* waypoint)
{
	return mavlink_msg_waypoint_pack(system_id, component_id, msg, waypoint->wp_id, waypoint->type, waypoint->param1, waypoint->param2, waypoint->orbit, waypoint->current, waypoint->x, waypoint->y, waypoint->z, waypoint->autocontinue);
}

/**
 * @brief Send a waypoint message
 * @param chan MAVLink channel to send the message
 *
 * @param wp_id Waypoint ID
 * @param type 0: global (GPS), 1: local, 2: global orbit, 3: local orbit
 * @param param1 Orbit to circle around the waypoint, in meters
 * @param param2 Time that the MAV should stay inside the orbit before advancing, in milliseconds
 * @param orbit 0: No orbit, 1: Right Orbit, 2: Left Orbit
 * @param current false:0, true:1
 * @param x local: x position, global: longitude
 * @param y y position: global: latitude
 * @param z z position: global: altitude
 * @param autocontinue autocontinue to next wp
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_waypoint_send(mavlink_channel_t chan, uint16_t wp_id, uint8_t type, float param1, float param2, uint8 orbit, uint8_t current, float x, float y, float z, uint16_t autocontinue)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_WAYPOINT;
	msg.len = sizeof(mavlink_waypoint_t);
	p->wp_id = wp_id; // uint16_t:Waypoint ID
	p->type = type; // uint8_t:0: global (GPS), 1: local, 2: global orbit, 3: local orbit
	p->param1 = param1; // float:Orbit to circle around the waypoint, in meters
	p->param2 = param2; // float:Time that the MAV should stay inside the orbit before advancing, in milliseconds
	p->orbit = orbit; // uint8:0: No orbit, 1: Right Orbit, 2: Left Orbit
	p->current = current; // uint8_t:false:0, true:1
	p->x = x; // float:local: x position, global: longitude
	p->y = y; // float:y position: global: latitude
	p->z = z; // float:z position: global: altitude
	p->autocontinue = autocontinue; // uint16_t:autocontinue to next wp

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
// MESSAGE WAYPOINT UNPACKING

/**
 * @brief Get field wp_id from waypoint message
 *
 * @return Waypoint ID
 */
static inline uint16_t mavlink_msg_waypoint_get_wp_id(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (uint16_t)(p->wp_id);
}

/**
 * @brief Get field type from waypoint message
 *
 * @return 0: global (GPS), 1: local, 2: global orbit, 3: local orbit
 */
static inline uint8_t mavlink_msg_waypoint_get_type(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (uint8_t)(p->type);
}

/**
 * @brief Get field param1 from waypoint message
 *
 * @return Orbit to circle around the waypoint, in meters
 */
static inline float mavlink_msg_waypoint_get_param1(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (float)(p->param1);
}

/**
 * @brief Get field param2 from waypoint message
 *
 * @return Time that the MAV should stay inside the orbit before advancing, in milliseconds
 */
static inline float mavlink_msg_waypoint_get_param2(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (float)(p->param2);
}

/**
 * @brief Get field orbit from waypoint message
 *
 * @return 0: No orbit, 1: Right Orbit, 2: Left Orbit
 */
static inline uint8 mavlink_msg_waypoint_get_orbit(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];

}

/**
 * @brief Get field current from waypoint message
 *
 * @return false:0, true:1
 */
static inline uint8_t mavlink_msg_waypoint_get_current(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (uint8_t)(p->current);
}

/**
 * @brief Get field x from waypoint message
 *
 * @return local: x position, global: longitude
 */
static inline float mavlink_msg_waypoint_get_x(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from waypoint message
 *
 * @return y position: global: latitude
 */
static inline float mavlink_msg_waypoint_get_y(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from waypoint message
 *
 * @return z position: global: altitude
 */
static inline float mavlink_msg_waypoint_get_z(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field autocontinue from waypoint message
 *
 * @return autocontinue to next wp
 */
static inline uint16_t mavlink_msg_waypoint_get_autocontinue(const mavlink_message_t* msg)
{
	mavlink_waypoint_t *p = (mavlink_waypoint_t *)&msg->payload[0];
	return (uint16_t)(p->autocontinue);
}

/**
 * @brief Decode a waypoint message into a struct
 *
 * @param msg The message to decode
 * @param waypoint C-struct to decode the message contents into
 */
static inline void mavlink_msg_waypoint_decode(const mavlink_message_t* msg, mavlink_waypoint_t* waypoint)
{
	memcpy( waypoint, msg->payload, sizeof(mavlink_waypoint_t));
}
