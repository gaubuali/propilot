// MESSAGE ATTITUDE_CONTROLLER_OUTPUT PACKING

#define MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_OUTPUT 60

typedef struct __mavlink_attitude_controller_output_t 
{
	uint8_t enabled; ///< 1: enabled, 0: disabled
	int8_t roll; ///< Attitude roll: -128: -100%, 127: +100%
	int8_t pitch; ///< Attitude pitch: -128: -100%, 127: +100%
	int8_t yaw; ///< Attitude yaw: -128: -100%, 127: +100%
	int8_t thrust; ///< Attitude thrust: -128: -100%, 127: +100%

} mavlink_attitude_controller_output_t;



/**
 * @brief Pack a attitude_controller_output message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enabled 1: enabled, 0: disabled
 * @param roll Attitude roll: -128: -100%, 127: +100%
 * @param pitch Attitude pitch: -128: -100%, 127: +100%
 * @param yaw Attitude yaw: -128: -100%, 127: +100%
 * @param thrust Attitude thrust: -128: -100%, 127: +100%
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_controller_output_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t enabled, int8_t roll, int8_t pitch, int8_t yaw, int8_t thrust)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_OUTPUT;

	p->enabled = enabled; // uint8_t:1: enabled, 0: disabled
	p->roll = roll; // int8_t:Attitude roll: -128: -100%, 127: +100%
	p->pitch = pitch; // int8_t:Attitude pitch: -128: -100%, 127: +100%
	p->yaw = yaw; // int8_t:Attitude yaw: -128: -100%, 127: +100%
	p->thrust = thrust; // int8_t:Attitude thrust: -128: -100%, 127: +100%

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_attitude_controller_output_t));
}

/**
 * @brief Pack a attitude_controller_output message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param enabled 1: enabled, 0: disabled
 * @param roll Attitude roll: -128: -100%, 127: +100%
 * @param pitch Attitude pitch: -128: -100%, 127: +100%
 * @param yaw Attitude yaw: -128: -100%, 127: +100%
 * @param thrust Attitude thrust: -128: -100%, 127: +100%
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_attitude_controller_output_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t enabled, int8_t roll, int8_t pitch, int8_t yaw, int8_t thrust)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_OUTPUT;

	p->enabled = enabled; // uint8_t:1: enabled, 0: disabled
	p->roll = roll; // int8_t:Attitude roll: -128: -100%, 127: +100%
	p->pitch = pitch; // int8_t:Attitude pitch: -128: -100%, 127: +100%
	p->yaw = yaw; // int8_t:Attitude yaw: -128: -100%, 127: +100%
	p->thrust = thrust; // int8_t:Attitude thrust: -128: -100%, 127: +100%

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_attitude_controller_output_t));
}

/**
 * @brief Encode a attitude_controller_output struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param attitude_controller_output C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_attitude_controller_output_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_attitude_controller_output_t* attitude_controller_output)
{
	return mavlink_msg_attitude_controller_output_pack(system_id, component_id, msg, attitude_controller_output->enabled, attitude_controller_output->roll, attitude_controller_output->pitch, attitude_controller_output->yaw, attitude_controller_output->thrust);
}

/**
 * @brief Send a attitude_controller_output message
 * @param chan MAVLink channel to send the message
 *
 * @param enabled 1: enabled, 0: disabled
 * @param roll Attitude roll: -128: -100%, 127: +100%
 * @param pitch Attitude pitch: -128: -100%, 127: +100%
 * @param yaw Attitude yaw: -128: -100%, 127: +100%
 * @param thrust Attitude thrust: -128: -100%, 127: +100%
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_attitude_controller_output_send(mavlink_channel_t chan, uint8_t enabled, int8_t roll, int8_t pitch, int8_t yaw, int8_t thrust)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_ATTITUDE_CONTROLLER_OUTPUT;
	msg.len = sizeof(mavlink_attitude_controller_output_t);
	p->enabled = enabled; // uint8_t:1: enabled, 0: disabled
	p->roll = roll; // int8_t:Attitude roll: -128: -100%, 127: +100%
	p->pitch = pitch; // int8_t:Attitude pitch: -128: -100%, 127: +100%
	p->yaw = yaw; // int8_t:Attitude yaw: -128: -100%, 127: +100%
	p->thrust = thrust; // int8_t:Attitude thrust: -128: -100%, 127: +100%

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
// MESSAGE ATTITUDE_CONTROLLER_OUTPUT UNPACKING

/**
 * @brief Get field enabled from attitude_controller_output message
 *
 * @return 1: enabled, 0: disabled
 */
static inline uint8_t mavlink_msg_attitude_controller_output_get_enabled(const mavlink_message_t* msg)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	return (uint8_t)(p->enabled);
}

/**
 * @brief Get field roll from attitude_controller_output message
 *
 * @return Attitude roll: -128: -100%, 127: +100%
 */
static inline int8_t mavlink_msg_attitude_controller_output_get_roll(const mavlink_message_t* msg)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	return (int8_t)(p->roll);
}

/**
 * @brief Get field pitch from attitude_controller_output message
 *
 * @return Attitude pitch: -128: -100%, 127: +100%
 */
static inline int8_t mavlink_msg_attitude_controller_output_get_pitch(const mavlink_message_t* msg)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	return (int8_t)(p->pitch);
}

/**
 * @brief Get field yaw from attitude_controller_output message
 *
 * @return Attitude yaw: -128: -100%, 127: +100%
 */
static inline int8_t mavlink_msg_attitude_controller_output_get_yaw(const mavlink_message_t* msg)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	return (int8_t)(p->yaw);
}

/**
 * @brief Get field thrust from attitude_controller_output message
 *
 * @return Attitude thrust: -128: -100%, 127: +100%
 */
static inline int8_t mavlink_msg_attitude_controller_output_get_thrust(const mavlink_message_t* msg)
{
	mavlink_attitude_controller_output_t *p = (mavlink_attitude_controller_output_t *)&msg->payload[0];
	return (int8_t)(p->thrust);
}

/**
 * @brief Decode a attitude_controller_output message into a struct
 *
 * @param msg The message to decode
 * @param attitude_controller_output C-struct to decode the message contents into
 */
static inline void mavlink_msg_attitude_controller_output_decode(const mavlink_message_t* msg, mavlink_attitude_controller_output_t* attitude_controller_output)
{
	memcpy( attitude_controller_output, msg->payload, sizeof(mavlink_attitude_controller_output_t));
}
