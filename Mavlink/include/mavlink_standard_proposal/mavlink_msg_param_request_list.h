// MESSAGE PARAM_REQUEST_LIST PACKING

#define MAVLINK_MSG_ID_PARAM_REQUEST_LIST 33
#define MAVLINK_MSG_ID_PARAM_REQUEST_LIST_LEN 3
#define MAVLINK_MSG_33_LEN 3

typedef struct __mavlink_param_request_list_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	uint8_t param_subset_id; ///< 0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum
} mavlink_param_request_list_t;


/**
 * @brief Pack a param_request_list message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_subset_id 0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_request_list_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t param_subset_id)
{
	mavlink_param_request_list_t *p = (mavlink_param_request_list_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_REQUEST_LIST;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->param_subset_id = param_subset_id; // uint8_t:0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_PARAM_REQUEST_LIST_LEN);
}

/**
 * @brief Pack a param_request_list message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_subset_id 0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_request_list_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t param_subset_id)
{
	mavlink_param_request_list_t *p = (mavlink_param_request_list_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_REQUEST_LIST;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->param_subset_id = param_subset_id; // uint8_t:0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_PARAM_REQUEST_LIST_LEN);
}

/**
 * @brief Encode a param_request_list struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param param_request_list C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_param_request_list_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_param_request_list_t* param_request_list)
{
	return mavlink_msg_param_request_list_pack(system_id, component_id, msg, param_request_list->target_system, param_request_list->target_component, param_request_list->param_subset_id);
}

/**
 * @brief Send a param_request_list message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_subset_id 0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_param_request_list_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t param_subset_id)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_param_request_list_t *p = (mavlink_param_request_list_t *)&msg.payload[0];

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->param_subset_id = param_subset_id; // uint8_t:0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_PARAM_REQUEST_LIST_LEN;
	msg.msgid = MAVLINK_MSG_ID_PARAM_REQUEST_LIST;
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
static inline void mavlink_msg_param_request_list_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t param_subset_id)
{
	mavlink_header_t hdr;
	mavlink_param_request_list_t payload;
	uint16_t checksum;
	mavlink_param_request_list_t *p = &payload;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->param_subset_id = param_subset_id; // uint8_t:0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_PARAM_REQUEST_LIST_LEN;
	hdr.msgid = MAVLINK_MSG_ID_PARAM_REQUEST_LIST;
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
// MESSAGE PARAM_REQUEST_LIST UNPACKING

/**
 * @brief Get field target_system from param_request_list message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_param_request_list_get_target_system(const mavlink_message_t* msg)
{
	mavlink_param_request_list_t *p = (mavlink_param_request_list_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from param_request_list message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_param_request_list_get_target_component(const mavlink_message_t* msg)
{
	mavlink_param_request_list_t *p = (mavlink_param_request_list_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field param_subset_id from param_request_list message
 *
 * @return 0: All parameters, else report a subset of parameters as defined in MAVLIN_SUBSET_PARAM enum
 */
static inline uint8_t mavlink_msg_param_request_list_get_param_subset_id(const mavlink_message_t* msg)
{
	mavlink_param_request_list_t *p = (mavlink_param_request_list_t *)&msg->payload[0];
	return (uint8_t)(p->param_subset_id);
}

/**
 * @brief Decode a param_request_list message into a struct
 *
 * @param msg The message to decode
 * @param param_request_list C-struct to decode the message contents into
 */
static inline void mavlink_msg_param_request_list_decode(const mavlink_message_t* msg, mavlink_param_request_list_t* param_request_list)
{
	memcpy( param_request_list, msg->payload, sizeof(mavlink_param_request_list_t));
}
