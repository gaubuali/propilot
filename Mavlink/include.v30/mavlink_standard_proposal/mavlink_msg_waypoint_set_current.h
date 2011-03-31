// MESSAGE WAYPOINT_SET_CURRENT PACKING

#define MAVLINK_MSG_ID_WAYPOINT_SET_CURRENT 17

typedef struct __mavlink_waypoint_set_current_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	uint16_t wp_id; ///< Waypoint ID

} mavlink_waypoint_set_current_t;



/**
 * @brief Pack a waypoint_set_current message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param wp_id Waypoint ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_set_current_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint16_t wp_id)
{
	mavlink_waypoint_set_current_t *p = (mavlink_waypoint_set_current_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT_SET_CURRENT;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->wp_id = wp_id; // uint16_t:Waypoint ID

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_waypoint_set_current_t));
}

/**
 * @brief Pack a waypoint_set_current message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param wp_id Waypoint ID
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_set_current_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint16_t wp_id)
{
	mavlink_waypoint_set_current_t *p = (mavlink_waypoint_set_current_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT_SET_CURRENT;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->wp_id = wp_id; // uint16_t:Waypoint ID

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_waypoint_set_current_t));
}

/**
 * @brief Encode a waypoint_set_current struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param waypoint_set_current C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waypoint_set_current_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_waypoint_set_current_t* waypoint_set_current)
{
	return mavlink_msg_waypoint_set_current_pack(system_id, component_id, msg, waypoint_set_current->target_system, waypoint_set_current->target_component, waypoint_set_current->wp_id);
}

/**
 * @brief Send a waypoint_set_current message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param wp_id Waypoint ID
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_waypoint_set_current_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t wp_id)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_waypoint_set_current_t *p = (mavlink_waypoint_set_current_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_WAYPOINT_SET_CURRENT;
	msg.len = sizeof(mavlink_waypoint_set_current_t);
	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->wp_id = wp_id; // uint16_t:Waypoint ID

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
// MESSAGE WAYPOINT_SET_CURRENT UNPACKING

/**
 * @brief Get field target_system from waypoint_set_current message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_waypoint_set_current_get_target_system(const mavlink_message_t* msg)
{
	mavlink_waypoint_set_current_t *p = (mavlink_waypoint_set_current_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from waypoint_set_current message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_waypoint_set_current_get_target_component(const mavlink_message_t* msg)
{
	mavlink_waypoint_set_current_t *p = (mavlink_waypoint_set_current_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field wp_id from waypoint_set_current message
 *
 * @return Waypoint ID
 */
static inline uint16_t mavlink_msg_waypoint_set_current_get_wp_id(const mavlink_message_t* msg)
{
	mavlink_waypoint_set_current_t *p = (mavlink_waypoint_set_current_t *)&msg->payload[0];
	return (uint16_t)(p->wp_id);
}

/**
 * @brief Decode a waypoint_set_current message into a struct
 *
 * @param msg The message to decode
 * @param waypoint_set_current C-struct to decode the message contents into
 */
static inline void mavlink_msg_waypoint_set_current_decode(const mavlink_message_t* msg, mavlink_waypoint_set_current_t* waypoint_set_current)
{
	memcpy( waypoint_set_current, msg->payload, sizeof(mavlink_waypoint_set_current_t));
}