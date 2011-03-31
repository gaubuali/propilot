// MESSAGE DATA_LOG PACKING

#define MAVLINK_MSG_ID_DATA_LOG 177
#define MAVLINK_MSG_177_LEN 24

typedef struct __mavlink_data_log_t 
{
	float fl_1; ///< Log value 1 
	float fl_2; ///< Log value 2 
	float fl_3; ///< Log value 3 
	float fl_4; ///< Log value 4 
	float fl_5; ///< Log value 5 
	float fl_6; ///< Log value 6 
} mavlink_data_log_t;

//#if sizeof(mavlink_data_log_t) != 24 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a data_log message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param fl_1 Log value 1 
 * @param fl_2 Log value 2 
 * @param fl_3 Log value 3 
 * @param fl_4 Log value 4 
 * @param fl_5 Log value 5 
 * @param fl_6 Log value 6 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_data_log_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, float fl_1, float fl_2, float fl_3, float fl_4, float fl_5, float fl_6)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_DATA_LOG;

	p->fl_1 = fl_1; // float:Log value 1 
	p->fl_2 = fl_2; // float:Log value 2 
	p->fl_3 = fl_3; // float:Log value 3 
	p->fl_4 = fl_4; // float:Log value 4 
	p->fl_5 = fl_5; // float:Log value 5 
	p->fl_6 = fl_6; // float:Log value 6 

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_data_log_t));
}

/**
 * @brief Pack a data_log message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param fl_1 Log value 1 
 * @param fl_2 Log value 2 
 * @param fl_3 Log value 3 
 * @param fl_4 Log value 4 
 * @param fl_5 Log value 5 
 * @param fl_6 Log value 6 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_data_log_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, float fl_1, float fl_2, float fl_3, float fl_4, float fl_5, float fl_6)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_DATA_LOG;

	p->fl_1 = fl_1; // float:Log value 1 
	p->fl_2 = fl_2; // float:Log value 2 
	p->fl_3 = fl_3; // float:Log value 3 
	p->fl_4 = fl_4; // float:Log value 4 
	p->fl_5 = fl_5; // float:Log value 5 
	p->fl_6 = fl_6; // float:Log value 6 

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_data_log_t));
}

/**
 * @brief Encode a data_log struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param data_log C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_data_log_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_data_log_t* data_log)
{
	return mavlink_msg_data_log_pack(system_id, component_id, msg, data_log->fl_1, data_log->fl_2, data_log->fl_3, data_log->fl_4, data_log->fl_5, data_log->fl_6);
}

/**
 * @brief Send a data_log message
 * @param chan MAVLink channel to send the message
 *
 * @param fl_1 Log value 1 
 * @param fl_2 Log value 2 
 * @param fl_3 Log value 3 
 * @param fl_4 Log value 4 
 * @param fl_5 Log value 5 
 * @param fl_6 Log value 6 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_data_log_send(mavlink_channel_t chan, float fl_1, float fl_2, float fl_3, float fl_4, float fl_5, float fl_6)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_DATA_LOG;
	msg.len = sizeof(mavlink_data_log_t);
	p->fl_1 = fl_1; // float:Log value 1 
	p->fl_2 = fl_2; // float:Log value 2 
	p->fl_3 = fl_3; // float:Log value 3 
	p->fl_4 = fl_4; // float:Log value 4 
	p->fl_5 = fl_5; // float:Log value 5 
	p->fl_6 = fl_6; // float:Log value 6 

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
// MESSAGE DATA_LOG UNPACKING

/**
 * @brief Get field fl_1 from data_log message
 *
 * @return Log value 1 
 */
static inline float mavlink_msg_data_log_get_fl_1(const mavlink_message_t* msg)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	return (float)(p->fl_1);
}

/**
 * @brief Get field fl_2 from data_log message
 *
 * @return Log value 2 
 */
static inline float mavlink_msg_data_log_get_fl_2(const mavlink_message_t* msg)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	return (float)(p->fl_2);
}

/**
 * @brief Get field fl_3 from data_log message
 *
 * @return Log value 3 
 */
static inline float mavlink_msg_data_log_get_fl_3(const mavlink_message_t* msg)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	return (float)(p->fl_3);
}

/**
 * @brief Get field fl_4 from data_log message
 *
 * @return Log value 4 
 */
static inline float mavlink_msg_data_log_get_fl_4(const mavlink_message_t* msg)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	return (float)(p->fl_4);
}

/**
 * @brief Get field fl_5 from data_log message
 *
 * @return Log value 5 
 */
static inline float mavlink_msg_data_log_get_fl_5(const mavlink_message_t* msg)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	return (float)(p->fl_5);
}

/**
 * @brief Get field fl_6 from data_log message
 *
 * @return Log value 6 
 */
static inline float mavlink_msg_data_log_get_fl_6(const mavlink_message_t* msg)
{
	mavlink_data_log_t *p = (mavlink_data_log_t *)&msg->payload[0];
	return (float)(p->fl_6);
}

/**
 * @brief Decode a data_log message into a struct
 *
 * @param msg The message to decode
 * @param data_log C-struct to decode the message contents into
 */
static inline void mavlink_msg_data_log_decode(const mavlink_message_t* msg, mavlink_data_log_t* data_log)
{
	memcpy( data_log, msg->payload, sizeof(mavlink_data_log_t));
}