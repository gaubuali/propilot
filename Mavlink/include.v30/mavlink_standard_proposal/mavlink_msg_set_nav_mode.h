// MESSAGE SET_NAV_MODE PACKING

#define MAVLINK_MSG_ID_SET_NAV_MODE 10

typedef struct __mavlink_set_nav_mode_t 
{
	uint8_t target; ///< The system setting the mode
	uint8_t nav_mode; ///< The new navigation mode

} mavlink_set_nav_mode_t;



/**
 * @brief Pack a set_nav_mode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target The system setting the mode
 * @param nav_mode The new navigation mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_nav_mode_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target, uint8_t nav_mode)
{
	mavlink_set_nav_mode_t *p = (mavlink_set_nav_mode_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SET_NAV_MODE;

	p->target = target; // uint8_t:The system setting the mode
	p->nav_mode = nav_mode; // uint8_t:The new navigation mode

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_set_nav_mode_t));
}

/**
 * @brief Pack a set_nav_mode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target The system setting the mode
 * @param nav_mode The new navigation mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_nav_mode_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target, uint8_t nav_mode)
{
	mavlink_set_nav_mode_t *p = (mavlink_set_nav_mode_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SET_NAV_MODE;

	p->target = target; // uint8_t:The system setting the mode
	p->nav_mode = nav_mode; // uint8_t:The new navigation mode

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_set_nav_mode_t));
}

/**
 * @brief Encode a set_nav_mode struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_nav_mode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_nav_mode_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_nav_mode_t* set_nav_mode)
{
	return mavlink_msg_set_nav_mode_pack(system_id, component_id, msg, set_nav_mode->target, set_nav_mode->nav_mode);
}

/**
 * @brief Send a set_nav_mode message
 * @param chan MAVLink channel to send the message
 *
 * @param target The system setting the mode
 * @param nav_mode The new navigation mode
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_nav_mode_send(mavlink_channel_t chan, uint8_t target, uint8_t nav_mode)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_set_nav_mode_t *p = (mavlink_set_nav_mode_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_SET_NAV_MODE;
	msg.len = sizeof(mavlink_set_nav_mode_t);
	p->target = target; // uint8_t:The system setting the mode
	p->nav_mode = nav_mode; // uint8_t:The new navigation mode

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
// MESSAGE SET_NAV_MODE UNPACKING

/**
 * @brief Get field target from set_nav_mode message
 *
 * @return The system setting the mode
 */
static inline uint8_t mavlink_msg_set_nav_mode_get_target(const mavlink_message_t* msg)
{
	mavlink_set_nav_mode_t *p = (mavlink_set_nav_mode_t *)&msg->payload[0];
	return (uint8_t)(p->target);
}

/**
 * @brief Get field nav_mode from set_nav_mode message
 *
 * @return The new navigation mode
 */
static inline uint8_t mavlink_msg_set_nav_mode_get_nav_mode(const mavlink_message_t* msg)
{
	mavlink_set_nav_mode_t *p = (mavlink_set_nav_mode_t *)&msg->payload[0];
	return (uint8_t)(p->nav_mode);
}

/**
 * @brief Decode a set_nav_mode message into a struct
 *
 * @param msg The message to decode
 * @param set_nav_mode C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_nav_mode_decode(const mavlink_message_t* msg, mavlink_set_nav_mode_t* set_nav_mode)
{
	memcpy( set_nav_mode, msg->payload, sizeof(mavlink_set_nav_mode_t));
}
