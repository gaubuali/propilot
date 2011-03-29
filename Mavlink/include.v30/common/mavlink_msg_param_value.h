// MESSAGE PARAM_VALUE PACKING

#define MAVLINK_MSG_ID_PARAM_VALUE 22

typedef struct __mavlink_param_value_t 
{
	int8_t param_id[16]; ///< Onboard parameter id
	float param_value; ///< Onboard parameter value
	uint16_t param_count; ///< Total number of onboard parameters
	uint16_t param_index; ///< Index of this onboard parameter

} mavlink_param_value_t;

#define MAVLINK_MSG_PARAM_VALUE_FIELD_PARAM_ID_LEN 16


/**
 * @brief Pack a param_value message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param param_id Onboard parameter id
 * @param param_value Onboard parameter value
 * @param param_count Total number of onboard parameters
 * @param param_index Index of this onboard parameter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_value_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const int8_t* param_id, float param_value, uint16_t param_count, uint16_t param_index)
{
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_VALUE;

	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id
	p->param_value = param_value; // float:Onboard parameter value
	p->param_count = param_count; // uint16_t:Total number of onboard parameters
	p->param_index = param_index; // uint16_t:Index of this onboard parameter

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_param_value_t));
}

/**
 * @brief Pack a param_value message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param param_id Onboard parameter id
 * @param param_value Onboard parameter value
 * @param param_count Total number of onboard parameters
 * @param param_index Index of this onboard parameter
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_value_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const int8_t* param_id, float param_value, uint16_t param_count, uint16_t param_index)
{
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_VALUE;

	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id
	p->param_value = param_value; // float:Onboard parameter value
	p->param_count = param_count; // uint16_t:Total number of onboard parameters
	p->param_index = param_index; // uint16_t:Index of this onboard parameter

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_param_value_t));
}

/**
 * @brief Encode a param_value struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param param_value C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_param_value_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_param_value_t* param_value)
{
	return mavlink_msg_param_value_pack(system_id, component_id, msg, param_value->param_id, param_value->param_value, param_value->param_count, param_value->param_index);
}

/**
 * @brief Send a param_value message
 * @param chan MAVLink channel to send the message
 *
 * @param param_id Onboard parameter id
 * @param param_value Onboard parameter value
 * @param param_count Total number of onboard parameters
 * @param param_index Index of this onboard parameter
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_param_value_send(mavlink_channel_t chan, const int8_t* param_id, float param_value, uint16_t param_count, uint16_t param_index)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_PARAM_VALUE;
	msg.len = sizeof(mavlink_param_value_t);
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id
	p->param_value = param_value; // float:Onboard parameter value
	p->param_count = param_count; // uint16_t:Total number of onboard parameters
	p->param_index = param_index; // uint16_t:Index of this onboard parameter

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
// MESSAGE PARAM_VALUE UNPACKING

/**
 * @brief Get field param_id from param_value message
 *
 * @return Onboard parameter id
 */
static inline uint16_t mavlink_msg_param_value_get_param_id(const mavlink_message_t* msg, int8_t* param_id)
{
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg->payload[0];

	memcpy(param_id, p->param_id, sizeof(p->param_id));
	return sizeof(p->param_id);
}

/**
 * @brief Get field param_value from param_value message
 *
 * @return Onboard parameter value
 */
static inline float mavlink_msg_param_value_get_param_value(const mavlink_message_t* msg)
{
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg->payload[0];
	return (float)(p->param_value);
}

/**
 * @brief Get field param_count from param_value message
 *
 * @return Total number of onboard parameters
 */
static inline uint16_t mavlink_msg_param_value_get_param_count(const mavlink_message_t* msg)
{
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg->payload[0];
	return (uint16_t)(p->param_count);
}

/**
 * @brief Get field param_index from param_value message
 *
 * @return Index of this onboard parameter
 */
static inline uint16_t mavlink_msg_param_value_get_param_index(const mavlink_message_t* msg)
{
	mavlink_param_value_t *p = (mavlink_param_value_t *)&msg->payload[0];
	return (uint16_t)(p->param_index);
}

/**
 * @brief Decode a param_value message into a struct
 *
 * @param msg The message to decode
 * @param param_value C-struct to decode the message contents into
 */
static inline void mavlink_msg_param_value_decode(const mavlink_message_t* msg, mavlink_param_value_t* param_value)
{
	memcpy( param_value, msg->payload, sizeof(mavlink_param_value_t));
}
