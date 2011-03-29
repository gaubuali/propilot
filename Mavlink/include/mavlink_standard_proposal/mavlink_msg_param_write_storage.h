// MESSAGE PARAM_WRITE_STORAGE PACKING

#define MAVLINK_MSG_ID_PARAM_WRITE_STORAGE 12
#define MAVLINK_MSG_12_LEN 18

typedef struct __mavlink_param_write_storage_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	int8_t param_id[16]; ///< Onboard parameter id
} mavlink_param_write_storage_t;

//#if sizeof(mavlink_param_write_storage_t) != 18 // sadly this fails 
//#warning struct and size do not match
//#endif

#define MAVLINK_MSG_PARAM_WRITE_STORAGE_FIELD_PARAM_ID_LEN 16

/**
 * @brief Pack a param_write_storage message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_id Onboard parameter id
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_write_storage_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, const int8_t* param_id)
{
	mavlink_param_write_storage_t *p = (mavlink_param_write_storage_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_WRITE_STORAGE;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_param_write_storage_t));
}

/**
 * @brief Pack a param_write_storage message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_id Onboard parameter id
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_write_storage_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, const int8_t* param_id)
{
	mavlink_param_write_storage_t *p = (mavlink_param_write_storage_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_WRITE_STORAGE;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_param_write_storage_t));
}

/**
 * @brief Encode a param_write_storage struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param param_write_storage C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_param_write_storage_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_param_write_storage_t* param_write_storage)
{
	return mavlink_msg_param_write_storage_pack(system_id, component_id, msg, param_write_storage->target_system, param_write_storage->target_component, param_write_storage->param_id);
}

/**
 * @brief Send a param_write_storage message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_id Onboard parameter id
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_param_write_storage_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, const int8_t* param_id)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_param_write_storage_t *p = (mavlink_param_write_storage_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_PARAM_WRITE_STORAGE;
	msg.len = sizeof(mavlink_param_write_storage_t);
	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id

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
// MESSAGE PARAM_WRITE_STORAGE UNPACKING

/**
 * @brief Get field target_system from param_write_storage message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_param_write_storage_get_target_system(const mavlink_message_t* msg)
{
	mavlink_param_write_storage_t *p = (mavlink_param_write_storage_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from param_write_storage message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_param_write_storage_get_target_component(const mavlink_message_t* msg)
{
	mavlink_param_write_storage_t *p = (mavlink_param_write_storage_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field param_id from param_write_storage message
 *
 * @return Onboard parameter id
 */
static inline uint16_t mavlink_msg_param_write_storage_get_param_id(const mavlink_message_t* msg, int8_t* param_id)
{
	mavlink_param_write_storage_t *p = (mavlink_param_write_storage_t *)&msg->payload[0];

	memcpy(param_id, p->param_id, sizeof(p->param_id));
	return sizeof(p->param_id);
}

/**
 * @brief Decode a param_write_storage message into a struct
 *
 * @param msg The message to decode
 * @param param_write_storage C-struct to decode the message contents into
 */
static inline void mavlink_msg_param_write_storage_decode(const mavlink_message_t* msg, mavlink_param_write_storage_t* param_write_storage)
{
	memcpy( param_write_storage, msg->payload, sizeof(mavlink_param_write_storage_t));
}
