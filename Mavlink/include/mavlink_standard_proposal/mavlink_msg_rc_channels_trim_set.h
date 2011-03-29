// MESSAGE RC_CHANNELS_TRIM_SET PACKING

#define MAVLINK_MSG_ID_RC_CHANNELS_TRIM_SET 14
#define MAVLINK_MSG_14_LEN 9

typedef struct __mavlink_rc_channels_trim_set_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	uint8_t chan_id; ///< RC channel id
	uint16_t chan_min; ///< RC channel 1 min value, in microseconds
	uint16_t chan_zero; ///< RC channel 1 zero value, in microseconds
	uint16_t chan_max; ///< RC channel 1 max value, in microseconds
} mavlink_rc_channels_trim_set_t;

//#if sizeof(mavlink_rc_channels_trim_set_t) != 9 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a rc_channels_trim_set message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param chan_id RC channel id
 * @param chan_min RC channel 1 min value, in microseconds
 * @param chan_zero RC channel 1 zero value, in microseconds
 * @param chan_max RC channel 1 max value, in microseconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rc_channels_trim_set_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t chan_id, uint16_t chan_min, uint16_t chan_zero, uint16_t chan_max)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RC_CHANNELS_TRIM_SET;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->chan_id = chan_id; // uint8_t:RC channel id
	p->chan_min = chan_min; // uint16_t:RC channel 1 min value, in microseconds
	p->chan_zero = chan_zero; // uint16_t:RC channel 1 zero value, in microseconds
	p->chan_max = chan_max; // uint16_t:RC channel 1 max value, in microseconds

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_rc_channels_trim_set_t));
}

/**
 * @brief Pack a rc_channels_trim_set message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param chan_id RC channel id
 * @param chan_min RC channel 1 min value, in microseconds
 * @param chan_zero RC channel 1 zero value, in microseconds
 * @param chan_max RC channel 1 max value, in microseconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rc_channels_trim_set_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t chan_id, uint16_t chan_min, uint16_t chan_zero, uint16_t chan_max)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RC_CHANNELS_TRIM_SET;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->chan_id = chan_id; // uint8_t:RC channel id
	p->chan_min = chan_min; // uint16_t:RC channel 1 min value, in microseconds
	p->chan_zero = chan_zero; // uint16_t:RC channel 1 zero value, in microseconds
	p->chan_max = chan_max; // uint16_t:RC channel 1 max value, in microseconds

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_rc_channels_trim_set_t));
}

/**
 * @brief Encode a rc_channels_trim_set struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rc_channels_trim_set C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rc_channels_trim_set_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rc_channels_trim_set_t* rc_channels_trim_set)
{
	return mavlink_msg_rc_channels_trim_set_pack(system_id, component_id, msg, rc_channels_trim_set->target_system, rc_channels_trim_set->target_component, rc_channels_trim_set->chan_id, rc_channels_trim_set->chan_min, rc_channels_trim_set->chan_zero, rc_channels_trim_set->chan_max);
}

/**
 * @brief Send a rc_channels_trim_set message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param chan_id RC channel id
 * @param chan_min RC channel 1 min value, in microseconds
 * @param chan_zero RC channel 1 zero value, in microseconds
 * @param chan_max RC channel 1 max value, in microseconds
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rc_channels_trim_set_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t chan_id, uint16_t chan_min, uint16_t chan_zero, uint16_t chan_max)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_RC_CHANNELS_TRIM_SET;
	msg.len = sizeof(mavlink_rc_channels_trim_set_t);
	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->chan_id = chan_id; // uint8_t:RC channel id
	p->chan_min = chan_min; // uint16_t:RC channel 1 min value, in microseconds
	p->chan_zero = chan_zero; // uint16_t:RC channel 1 zero value, in microseconds
	p->chan_max = chan_max; // uint16_t:RC channel 1 max value, in microseconds

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
// MESSAGE RC_CHANNELS_TRIM_SET UNPACKING

/**
 * @brief Get field target_system from rc_channels_trim_set message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_rc_channels_trim_set_get_target_system(const mavlink_message_t* msg)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from rc_channels_trim_set message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_rc_channels_trim_set_get_target_component(const mavlink_message_t* msg)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field chan_id from rc_channels_trim_set message
 *
 * @return RC channel id
 */
static inline uint8_t mavlink_msg_rc_channels_trim_set_get_chan_id(const mavlink_message_t* msg)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	return (uint8_t)(p->chan_id);
}

/**
 * @brief Get field chan_min from rc_channels_trim_set message
 *
 * @return RC channel 1 min value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_trim_set_get_chan_min(const mavlink_message_t* msg)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	return (uint16_t)(p->chan_min);
}

/**
 * @brief Get field chan_zero from rc_channels_trim_set message
 *
 * @return RC channel 1 zero value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_trim_set_get_chan_zero(const mavlink_message_t* msg)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	return (uint16_t)(p->chan_zero);
}

/**
 * @brief Get field chan_max from rc_channels_trim_set message
 *
 * @return RC channel 1 max value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_trim_set_get_chan_max(const mavlink_message_t* msg)
{
	mavlink_rc_channels_trim_set_t *p = (mavlink_rc_channels_trim_set_t *)&msg->payload[0];
	return (uint16_t)(p->chan_max);
}

/**
 * @brief Decode a rc_channels_trim_set message into a struct
 *
 * @param msg The message to decode
 * @param rc_channels_trim_set C-struct to decode the message contents into
 */
static inline void mavlink_msg_rc_channels_trim_set_decode(const mavlink_message_t* msg, mavlink_rc_channels_trim_set_t* rc_channels_trim_set)
{
	memcpy( rc_channels_trim_set, msg->payload, sizeof(mavlink_rc_channels_trim_set_t));
}
