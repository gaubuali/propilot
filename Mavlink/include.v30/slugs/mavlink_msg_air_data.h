// MESSAGE AIR_DATA PACKING

#define MAVLINK_MSG_ID_AIR_DATA 171

typedef struct __mavlink_air_data_t 
{
	float dynamicPressure; ///< Dynamic pressure (Pa)
	float staticPressure; ///< Static pressure (Pa)
	uint16_t temperature; ///< Board temperature

} mavlink_air_data_t;



/**
 * @brief Pack a air_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param dynamicPressure Dynamic pressure (Pa)
 * @param staticPressure Static pressure (Pa)
 * @param temperature Board temperature
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_air_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, float dynamicPressure, float staticPressure, uint16_t temperature)
{
	mavlink_air_data_t *p = (mavlink_air_data_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_AIR_DATA;

	p->dynamicPressure = dynamicPressure; // float:Dynamic pressure (Pa)
	p->staticPressure = staticPressure; // float:Static pressure (Pa)
	p->temperature = temperature; // uint16_t:Board temperature

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_air_data_t));
}

/**
 * @brief Pack a air_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param dynamicPressure Dynamic pressure (Pa)
 * @param staticPressure Static pressure (Pa)
 * @param temperature Board temperature
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_air_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, float dynamicPressure, float staticPressure, uint16_t temperature)
{
	mavlink_air_data_t *p = (mavlink_air_data_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_AIR_DATA;

	p->dynamicPressure = dynamicPressure; // float:Dynamic pressure (Pa)
	p->staticPressure = staticPressure; // float:Static pressure (Pa)
	p->temperature = temperature; // uint16_t:Board temperature

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_air_data_t));
}

/**
 * @brief Encode a air_data struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param air_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_air_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_air_data_t* air_data)
{
	return mavlink_msg_air_data_pack(system_id, component_id, msg, air_data->dynamicPressure, air_data->staticPressure, air_data->temperature);
}

/**
 * @brief Send a air_data message
 * @param chan MAVLink channel to send the message
 *
 * @param dynamicPressure Dynamic pressure (Pa)
 * @param staticPressure Static pressure (Pa)
 * @param temperature Board temperature
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_air_data_send(mavlink_channel_t chan, float dynamicPressure, float staticPressure, uint16_t temperature)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_air_data_t *p = (mavlink_air_data_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_AIR_DATA;
	msg.len = sizeof(mavlink_air_data_t);
	p->dynamicPressure = dynamicPressure; // float:Dynamic pressure (Pa)
	p->staticPressure = staticPressure; // float:Static pressure (Pa)
	p->temperature = temperature; // uint16_t:Board temperature

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
// MESSAGE AIR_DATA UNPACKING

/**
 * @brief Get field dynamicPressure from air_data message
 *
 * @return Dynamic pressure (Pa)
 */
static inline float mavlink_msg_air_data_get_dynamicPressure(const mavlink_message_t* msg)
{
	mavlink_air_data_t *p = (mavlink_air_data_t *)&msg->payload[0];
	return (float)(p->dynamicPressure);
}

/**
 * @brief Get field staticPressure from air_data message
 *
 * @return Static pressure (Pa)
 */
static inline float mavlink_msg_air_data_get_staticPressure(const mavlink_message_t* msg)
{
	mavlink_air_data_t *p = (mavlink_air_data_t *)&msg->payload[0];
	return (float)(p->staticPressure);
}

/**
 * @brief Get field temperature from air_data message
 *
 * @return Board temperature
 */
static inline uint16_t mavlink_msg_air_data_get_temperature(const mavlink_message_t* msg)
{
	mavlink_air_data_t *p = (mavlink_air_data_t *)&msg->payload[0];
	return (uint16_t)(p->temperature);
}

/**
 * @brief Decode a air_data message into a struct
 *
 * @param msg The message to decode
 * @param air_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_air_data_decode(const mavlink_message_t* msg, mavlink_air_data_t* air_data)
{
	memcpy( air_data, msg->payload, sizeof(mavlink_air_data_t));
}
