// MESSAGE WATCHDOG_PROCESS_INFO PACKING

#define MAVLINK_MSG_ID_WATCHDOG_PROCESS_INFO 151

typedef struct __mavlink_watchdog_process_info_t 
{
	uint16_t watchdog_id; ///< Watchdog ID
	uint16_t process_id; ///< Process ID
	int8_t name[100]; ///< Process name
	int8_t arguments[147]; ///< Process arguments
	int32_t timeout; ///< Timeout (seconds)

} mavlink_watchdog_process_info_t;

#define MAVLINK_MSG_WATCHDOG_PROCESS_INFO_FIELD_NAME_LEN 100
#define MAVLINK_MSG_WATCHDOG_PROCESS_INFO_FIELD_ARGUMENTS_LEN 147


/**
 * @brief Pack a watchdog_process_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param watchdog_id Watchdog ID
 * @param process_id Process ID
 * @param name Process name
 * @param arguments Process arguments
 * @param timeout Timeout (seconds)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_watchdog_process_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t watchdog_id, uint16_t process_id, const int8_t* name, const int8_t* arguments, int32_t timeout)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WATCHDOG_PROCESS_INFO;

	p->watchdog_id = watchdog_id; // uint16_t:Watchdog ID
	p->process_id = process_id; // uint16_t:Process ID
	memcpy( p->name, name, sizeof(p->name)); // array[100]:Process name
	memcpy( p->arguments, arguments, sizeof(p->arguments)); // array[147]:Process arguments
	p->timeout = timeout; // int32_t:Timeout (seconds)

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_watchdog_process_info_t));
}

/**
 * @brief Pack a watchdog_process_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param watchdog_id Watchdog ID
 * @param process_id Process ID
 * @param name Process name
 * @param arguments Process arguments
 * @param timeout Timeout (seconds)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_watchdog_process_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t watchdog_id, uint16_t process_id, const int8_t* name, const int8_t* arguments, int32_t timeout)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WATCHDOG_PROCESS_INFO;

	p->watchdog_id = watchdog_id; // uint16_t:Watchdog ID
	p->process_id = process_id; // uint16_t:Process ID
	memcpy( p->name, name, sizeof(p->name)); // array[100]:Process name
	memcpy( p->arguments, arguments, sizeof(p->arguments)); // array[147]:Process arguments
	p->timeout = timeout; // int32_t:Timeout (seconds)

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_watchdog_process_info_t));
}

/**
 * @brief Encode a watchdog_process_info struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param watchdog_process_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_watchdog_process_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_watchdog_process_info_t* watchdog_process_info)
{
	return mavlink_msg_watchdog_process_info_pack(system_id, component_id, msg, watchdog_process_info->watchdog_id, watchdog_process_info->process_id, watchdog_process_info->name, watchdog_process_info->arguments, watchdog_process_info->timeout);
}

/**
 * @brief Send a watchdog_process_info message
 * @param chan MAVLink channel to send the message
 *
 * @param watchdog_id Watchdog ID
 * @param process_id Process ID
 * @param name Process name
 * @param arguments Process arguments
 * @param timeout Timeout (seconds)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_watchdog_process_info_send(mavlink_channel_t chan, uint16_t watchdog_id, uint16_t process_id, const int8_t* name, const int8_t* arguments, int32_t timeout)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_WATCHDOG_PROCESS_INFO;
	msg.len = sizeof(mavlink_watchdog_process_info_t);
	p->watchdog_id = watchdog_id; // uint16_t:Watchdog ID
	p->process_id = process_id; // uint16_t:Process ID
	memcpy( p->name, name, sizeof(p->name)); // array[100]:Process name
	memcpy( p->arguments, arguments, sizeof(p->arguments)); // array[147]:Process arguments
	p->timeout = timeout; // int32_t:Timeout (seconds)

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
// MESSAGE WATCHDOG_PROCESS_INFO UNPACKING

/**
 * @brief Get field watchdog_id from watchdog_process_info message
 *
 * @return Watchdog ID
 */
static inline uint16_t mavlink_msg_watchdog_process_info_get_watchdog_id(const mavlink_message_t* msg)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];
	return (uint16_t)(p->watchdog_id);
}

/**
 * @brief Get field process_id from watchdog_process_info message
 *
 * @return Process ID
 */
static inline uint16_t mavlink_msg_watchdog_process_info_get_process_id(const mavlink_message_t* msg)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];
	return (uint16_t)(p->process_id);
}

/**
 * @brief Get field name from watchdog_process_info message
 *
 * @return Process name
 */
static inline uint16_t mavlink_msg_watchdog_process_info_get_name(const mavlink_message_t* msg, int8_t* name)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];

	memcpy(name, p->name, sizeof(p->name));
	return sizeof(p->name);
}

/**
 * @brief Get field arguments from watchdog_process_info message
 *
 * @return Process arguments
 */
static inline uint16_t mavlink_msg_watchdog_process_info_get_arguments(const mavlink_message_t* msg, int8_t* arguments)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];

	memcpy(arguments, p->arguments, sizeof(p->arguments));
	return sizeof(p->arguments);
}

/**
 * @brief Get field timeout from watchdog_process_info message
 *
 * @return Timeout (seconds)
 */
static inline int32_t mavlink_msg_watchdog_process_info_get_timeout(const mavlink_message_t* msg)
{
	mavlink_watchdog_process_info_t *p = (mavlink_watchdog_process_info_t *)&msg->payload[0];
	return (int32_t)(p->timeout);
}

/**
 * @brief Decode a watchdog_process_info message into a struct
 *
 * @param msg The message to decode
 * @param watchdog_process_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_watchdog_process_info_decode(const mavlink_message_t* msg, mavlink_watchdog_process_info_t* watchdog_process_info)
{
	memcpy( watchdog_process_info, msg->payload, sizeof(mavlink_watchdog_process_info_t));
}
