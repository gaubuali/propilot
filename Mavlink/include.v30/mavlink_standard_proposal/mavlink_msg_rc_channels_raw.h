// MESSAGE RC_CHANNELS_RAW PACKING

#define MAVLINK_MSG_ID_RC_CHANNELS_RAW 56

typedef struct __mavlink_rc_channels_raw_t 
{
	uint16_t chan1; ///< RC channel 1 value, in microseconds
	uint16_t chan2; ///< RC channel 2 value, in microseconds
	uint16_t chan3; ///< RC channel 3 value, in microseconds
	uint16_t chan4; ///< RC channel 3 value, in microseconds
	uint16_t chan5; ///< RC channel 3 value, in microseconds

} mavlink_rc_channels_raw_t;



/**
 * @brief Pack a rc_channels_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param chan1 RC channel 1 value, in microseconds
 * @param chan2 RC channel 2 value, in microseconds
 * @param chan3 RC channel 3 value, in microseconds
 * @param chan4 RC channel 3 value, in microseconds
 * @param chan5 RC channel 3 value, in microseconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rc_channels_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t chan1, uint16_t chan2, uint16_t chan3, uint16_t chan4, uint16_t chan5)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RC_CHANNELS_RAW;

	p->chan1 = chan1; // uint16_t:RC channel 1 value, in microseconds
	p->chan2 = chan2; // uint16_t:RC channel 2 value, in microseconds
	p->chan3 = chan3; // uint16_t:RC channel 3 value, in microseconds
	p->chan4 = chan4; // uint16_t:RC channel 3 value, in microseconds
	p->chan5 = chan5; // uint16_t:RC channel 3 value, in microseconds

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_rc_channels_raw_t));
}

/**
 * @brief Pack a rc_channels_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param chan1 RC channel 1 value, in microseconds
 * @param chan2 RC channel 2 value, in microseconds
 * @param chan3 RC channel 3 value, in microseconds
 * @param chan4 RC channel 3 value, in microseconds
 * @param chan5 RC channel 3 value, in microseconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_rc_channels_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t chan1, uint16_t chan2, uint16_t chan3, uint16_t chan4, uint16_t chan5)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RC_CHANNELS_RAW;

	p->chan1 = chan1; // uint16_t:RC channel 1 value, in microseconds
	p->chan2 = chan2; // uint16_t:RC channel 2 value, in microseconds
	p->chan3 = chan3; // uint16_t:RC channel 3 value, in microseconds
	p->chan4 = chan4; // uint16_t:RC channel 3 value, in microseconds
	p->chan5 = chan5; // uint16_t:RC channel 3 value, in microseconds

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_rc_channels_raw_t));
}

/**
 * @brief Encode a rc_channels_raw struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param rc_channels_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_rc_channels_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_rc_channels_raw_t* rc_channels_raw)
{
	return mavlink_msg_rc_channels_raw_pack(system_id, component_id, msg, rc_channels_raw->chan1, rc_channels_raw->chan2, rc_channels_raw->chan3, rc_channels_raw->chan4, rc_channels_raw->chan5);
}

/**
 * @brief Send a rc_channels_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param chan1 RC channel 1 value, in microseconds
 * @param chan2 RC channel 2 value, in microseconds
 * @param chan3 RC channel 3 value, in microseconds
 * @param chan4 RC channel 3 value, in microseconds
 * @param chan5 RC channel 3 value, in microseconds
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_rc_channels_raw_send(mavlink_channel_t chan, uint16_t chan1, uint16_t chan2, uint16_t chan3, uint16_t chan4, uint16_t chan5)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_RC_CHANNELS_RAW;
	msg.len = sizeof(mavlink_rc_channels_raw_t);
	p->chan1 = chan1; // uint16_t:RC channel 1 value, in microseconds
	p->chan2 = chan2; // uint16_t:RC channel 2 value, in microseconds
	p->chan3 = chan3; // uint16_t:RC channel 3 value, in microseconds
	p->chan4 = chan4; // uint16_t:RC channel 3 value, in microseconds
	p->chan5 = chan5; // uint16_t:RC channel 3 value, in microseconds

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
// MESSAGE RC_CHANNELS_RAW UNPACKING

/**
 * @brief Get field chan1 from rc_channels_raw message
 *
 * @return RC channel 1 value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_raw_get_chan1(const mavlink_message_t* msg)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	return (uint16_t)(p->chan1);
}

/**
 * @brief Get field chan2 from rc_channels_raw message
 *
 * @return RC channel 2 value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_raw_get_chan2(const mavlink_message_t* msg)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	return (uint16_t)(p->chan2);
}

/**
 * @brief Get field chan3 from rc_channels_raw message
 *
 * @return RC channel 3 value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_raw_get_chan3(const mavlink_message_t* msg)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	return (uint16_t)(p->chan3);
}

/**
 * @brief Get field chan4 from rc_channels_raw message
 *
 * @return RC channel 3 value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_raw_get_chan4(const mavlink_message_t* msg)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	return (uint16_t)(p->chan4);
}

/**
 * @brief Get field chan5 from rc_channels_raw message
 *
 * @return RC channel 3 value, in microseconds
 */
static inline uint16_t mavlink_msg_rc_channels_raw_get_chan5(const mavlink_message_t* msg)
{
	mavlink_rc_channels_raw_t *p = (mavlink_rc_channels_raw_t *)&msg->payload[0];
	return (uint16_t)(p->chan5);
}

/**
 * @brief Decode a rc_channels_raw message into a struct
 *
 * @param msg The message to decode
 * @param rc_channels_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_rc_channels_raw_decode(const mavlink_message_t* msg, mavlink_rc_channels_raw_t* rc_channels_raw)
{
	memcpy( rc_channels_raw, msg->payload, sizeof(mavlink_rc_channels_raw_t));
}
