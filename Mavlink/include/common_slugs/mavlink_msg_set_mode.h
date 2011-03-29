// MESSAGE SET_MODE PACKING

#define MAVLINK_MSG_ID_SET_MODE 11
#define MAVLINK_MSG_11_LEN 2

typedef struct __mavlink_set_mode_t 
{
	uint8_t target; ///< The system setting the mode
	uint8_t mode; ///< The new mode
} mavlink_set_mode_t;

//#if sizeof(mavlink_set_mode_t) != 2 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a set_mode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target The system setting the mode
 * @param mode The new mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_mode_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target, uint8_t mode)
{
	mavlink_set_mode_t *p = (mavlink_set_mode_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SET_MODE;

	p->target = target; // uint8_t:The system setting the mode
	p->mode = mode; // uint8_t:The new mode

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_set_mode_t));
}

/**
 * @brief Pack a set_mode message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target The system setting the mode
 * @param mode The new mode
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_set_mode_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target, uint8_t mode)
{
	mavlink_set_mode_t *p = (mavlink_set_mode_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SET_MODE;

	p->target = target; // uint8_t:The system setting the mode
	p->mode = mode; // uint8_t:The new mode

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_set_mode_t));
}

/**
 * @brief Encode a set_mode struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param set_mode C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_set_mode_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_set_mode_t* set_mode)
{
	return mavlink_msg_set_mode_pack(system_id, component_id, msg, set_mode->target, set_mode->mode);
}

/**
 * @brief Send a set_mode message
 * @param chan MAVLink channel to send the message
 *
 * @param target The system setting the mode
 * @param mode The new mode
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_set_mode_send(mavlink_channel_t chan, uint8_t target, uint8_t mode)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_set_mode_t *p = (mavlink_set_mode_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_SET_MODE;
	msg.len = sizeof(mavlink_set_mode_t);
	p->target = target; // uint8_t:The system setting the mode
	p->mode = mode; // uint8_t:The new mode

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
// MESSAGE SET_MODE UNPACKING

/**
 * @brief Get field target from set_mode message
 *
 * @return The system setting the mode
 */
static inline uint8_t mavlink_msg_set_mode_get_target(const mavlink_message_t* msg)
{
	mavlink_set_mode_t *p = (mavlink_set_mode_t *)&msg->payload[0];
	return (uint8_t)(p->target);
}

/**
 * @brief Get field mode from set_mode message
 *
 * @return The new mode
 */
static inline uint8_t mavlink_msg_set_mode_get_mode(const mavlink_message_t* msg)
{
	mavlink_set_mode_t *p = (mavlink_set_mode_t *)&msg->payload[0];
	return (uint8_t)(p->mode);
}

/**
 * @brief Decode a set_mode message into a struct
 *
 * @param msg The message to decode
 * @param set_mode C-struct to decode the message contents into
 */
static inline void mavlink_msg_set_mode_decode(const mavlink_message_t* msg, mavlink_set_mode_t* set_mode)
{
	memcpy( set_mode, msg->payload, sizeof(mavlink_set_mode_t));
}
