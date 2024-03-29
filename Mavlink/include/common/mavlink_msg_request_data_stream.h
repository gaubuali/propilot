// MESSAGE REQUEST_DATA_STREAM PACKING

#define MAVLINK_MSG_ID_REQUEST_DATA_STREAM 66
#define MAVLINK_MSG_ID_REQUEST_DATA_STREAM_LEN 6
#define MAVLINK_MSG_66_LEN 6

typedef struct __mavlink_request_data_stream_t 
{
	uint8_t target_system; ///< The target requested to send the message stream.
	uint8_t target_component; ///< The target requested to send the message stream.
	uint16_t req_message_rate; ///< The requested interval between two messages of this type
	uint8_t req_stream_id; ///< The ID of the requested message type
	uint8_t start_stop; ///< 1 to start sending, 0 to stop sending.
} mavlink_request_data_stream_t;


/**
 * @brief Pack a request_data_stream message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system The target requested to send the message stream.
 * @param target_component The target requested to send the message stream.
 * @param req_stream_id The ID of the requested message type
 * @param req_message_rate The requested interval between two messages of this type
 * @param start_stop 1 to start sending, 0 to stop sending.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_data_stream_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t req_stream_id, uint16_t req_message_rate, uint8_t start_stop)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_REQUEST_DATA_STREAM;

	p->target_system = target_system; // uint8_t:The target requested to send the message stream.
	p->target_component = target_component; // uint8_t:The target requested to send the message stream.
	p->req_message_rate = req_message_rate; // uint16_t:The requested interval between two messages of this type
	p->req_stream_id = req_stream_id; // uint8_t:The ID of the requested message type
	p->start_stop = start_stop; // uint8_t:1 to start sending, 0 to stop sending.

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_REQUEST_DATA_STREAM_LEN);
}

/**
 * @brief Pack a request_data_stream message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system The target requested to send the message stream.
 * @param target_component The target requested to send the message stream.
 * @param req_stream_id The ID of the requested message type
 * @param req_message_rate The requested interval between two messages of this type
 * @param start_stop 1 to start sending, 0 to stop sending.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_data_stream_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint8_t req_stream_id, uint16_t req_message_rate, uint8_t start_stop)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_REQUEST_DATA_STREAM;

	p->target_system = target_system; // uint8_t:The target requested to send the message stream.
	p->target_component = target_component; // uint8_t:The target requested to send the message stream.
	p->req_message_rate = req_message_rate; // uint16_t:The requested interval between two messages of this type
	p->req_stream_id = req_stream_id; // uint8_t:The ID of the requested message type
	p->start_stop = start_stop; // uint8_t:1 to start sending, 0 to stop sending.

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_REQUEST_DATA_STREAM_LEN);
}

/**
 * @brief Encode a request_data_stream struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param request_data_stream C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_request_data_stream_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_request_data_stream_t* request_data_stream)
{
	return mavlink_msg_request_data_stream_pack(system_id, component_id, msg, request_data_stream->target_system, request_data_stream->target_component, request_data_stream->req_stream_id, request_data_stream->req_message_rate, request_data_stream->start_stop);
}

/**
 * @brief Send a request_data_stream message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system The target requested to send the message stream.
 * @param target_component The target requested to send the message stream.
 * @param req_stream_id The ID of the requested message type
 * @param req_message_rate The requested interval between two messages of this type
 * @param start_stop 1 to start sending, 0 to stop sending.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_request_data_stream_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t req_stream_id, uint16_t req_message_rate, uint8_t start_stop)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg.payload[0];

	p->target_system = target_system; // uint8_t:The target requested to send the message stream.
	p->target_component = target_component; // uint8_t:The target requested to send the message stream.
	p->req_message_rate = req_message_rate; // uint16_t:The requested interval between two messages of this type
	p->req_stream_id = req_stream_id; // uint8_t:The ID of the requested message type
	p->start_stop = start_stop; // uint8_t:1 to start sending, 0 to stop sending.

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_REQUEST_DATA_STREAM_LEN;
	msg.msgid = MAVLINK_MSG_ID_REQUEST_DATA_STREAM;
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
static inline void mavlink_msg_request_data_stream_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t req_stream_id, uint16_t req_message_rate, uint8_t start_stop)
{
	mavlink_header_t hdr;
	mavlink_request_data_stream_t payload;
	uint16_t checksum;
	mavlink_request_data_stream_t *p = &payload;

	p->target_system = target_system; // uint8_t:The target requested to send the message stream.
	p->target_component = target_component; // uint8_t:The target requested to send the message stream.
	p->req_message_rate = req_message_rate; // uint16_t:The requested interval between two messages of this type
	p->req_stream_id = req_stream_id; // uint8_t:The ID of the requested message type
	p->start_stop = start_stop; // uint8_t:1 to start sending, 0 to stop sending.

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_REQUEST_DATA_STREAM_LEN;
	hdr.msgid = MAVLINK_MSG_ID_REQUEST_DATA_STREAM;
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
// MESSAGE REQUEST_DATA_STREAM UNPACKING

/**
 * @brief Get field target_system from request_data_stream message
 *
 * @return The target requested to send the message stream.
 */
static inline uint8_t mavlink_msg_request_data_stream_get_target_system(const mavlink_message_t* msg)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from request_data_stream message
 *
 * @return The target requested to send the message stream.
 */
static inline uint8_t mavlink_msg_request_data_stream_get_target_component(const mavlink_message_t* msg)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field req_stream_id from request_data_stream message
 *
 * @return The ID of the requested message type
 */
static inline uint8_t mavlink_msg_request_data_stream_get_req_stream_id(const mavlink_message_t* msg)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	return (uint8_t)(p->req_stream_id);
}

/**
 * @brief Get field req_message_rate from request_data_stream message
 *
 * @return The requested interval between two messages of this type
 */
static inline uint16_t mavlink_msg_request_data_stream_get_req_message_rate(const mavlink_message_t* msg)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	return (uint16_t)(p->req_message_rate);
}

/**
 * @brief Get field start_stop from request_data_stream message
 *
 * @return 1 to start sending, 0 to stop sending.
 */
static inline uint8_t mavlink_msg_request_data_stream_get_start_stop(const mavlink_message_t* msg)
{
	mavlink_request_data_stream_t *p = (mavlink_request_data_stream_t *)&msg->payload[0];
	return (uint8_t)(p->start_stop);
}

/**
 * @brief Decode a request_data_stream message into a struct
 *
 * @param msg The message to decode
 * @param request_data_stream C-struct to decode the message contents into
 */
static inline void mavlink_msg_request_data_stream_decode(const mavlink_message_t* msg, mavlink_request_data_stream_t* request_data_stream)
{
	memcpy( request_data_stream, msg->payload, sizeof(mavlink_request_data_stream_t));
}
