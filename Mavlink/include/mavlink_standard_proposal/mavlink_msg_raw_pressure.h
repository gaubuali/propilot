// MESSAGE RAW_PRESSURE PACKING

#define MAVLINK_MSG_ID_RAW_PRESSURE 51
#define MAVLINK_MSG_ID_RAW_PRESSURE_LEN 20
#define MAVLINK_MSG_51_LEN 20

typedef struct __mavlink_raw_pressure_t 
{
	uint64_t usec; ///< Timestamp (microseconds since UNIX epoch)
	int32_t press_abs; ///< Absolute pressure (hectopascal)
	int32_t press_diff1; ///< Differential pressure 1 (hectopascal)
	int32_t press_diff2; ///< Differential pressure 2 (hectopascal)
} mavlink_raw_pressure_t;


/**
 * @brief Pack a raw_pressure message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (microseconds since UNIX epoch)
 * @param press_abs Absolute pressure (hectopascal)
 * @param press_diff1 Differential pressure 1 (hectopascal)
 * @param press_diff2 Differential pressure 2 (hectopascal)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_pressure_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint64_t usec, int32_t press_abs, int32_t press_diff1, int32_t press_diff2)
{
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RAW_PRESSURE;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->press_abs = press_abs; // int32_t:Absolute pressure (hectopascal)
	p->press_diff1 = press_diff1; // int32_t:Differential pressure 1 (hectopascal)
	p->press_diff2 = press_diff2; // int32_t:Differential pressure 2 (hectopascal)

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RAW_PRESSURE_LEN);
}

/**
 * @brief Pack a raw_pressure message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param usec Timestamp (microseconds since UNIX epoch)
 * @param press_abs Absolute pressure (hectopascal)
 * @param press_diff1 Differential pressure 1 (hectopascal)
 * @param press_diff2 Differential pressure 2 (hectopascal)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_pressure_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint64_t usec, int32_t press_abs, int32_t press_diff1, int32_t press_diff2)
{
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RAW_PRESSURE;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->press_abs = press_abs; // int32_t:Absolute pressure (hectopascal)
	p->press_diff1 = press_diff1; // int32_t:Differential pressure 1 (hectopascal)
	p->press_diff2 = press_diff2; // int32_t:Differential pressure 2 (hectopascal)

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RAW_PRESSURE_LEN);
}

/**
 * @brief Encode a raw_pressure struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param raw_pressure C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_raw_pressure_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_raw_pressure_t* raw_pressure)
{
	return mavlink_msg_raw_pressure_pack(system_id, component_id, msg, raw_pressure->usec, raw_pressure->press_abs, raw_pressure->press_diff1, raw_pressure->press_diff2);
}

/**
 * @brief Send a raw_pressure message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (microseconds since UNIX epoch)
 * @param press_abs Absolute pressure (hectopascal)
 * @param press_diff1 Differential pressure 1 (hectopascal)
 * @param press_diff2 Differential pressure 2 (hectopascal)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_raw_pressure_send(mavlink_channel_t chan, uint64_t usec, int32_t press_abs, int32_t press_diff1, int32_t press_diff2)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg.payload[0];

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->press_abs = press_abs; // int32_t:Absolute pressure (hectopascal)
	p->press_diff1 = press_diff1; // int32_t:Differential pressure 1 (hectopascal)
	p->press_diff2 = press_diff2; // int32_t:Differential pressure 2 (hectopascal)

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_RAW_PRESSURE_LEN;
	msg.msgid = MAVLINK_MSG_ID_RAW_PRESSURE;
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
static inline void mavlink_msg_raw_pressure_send(mavlink_channel_t chan, uint64_t usec, int32_t press_abs, int32_t press_diff1, int32_t press_diff2)
{
	mavlink_header_t hdr;
	mavlink_raw_pressure_t payload;
	uint16_t checksum;
	mavlink_raw_pressure_t *p = &payload;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->press_abs = press_abs; // int32_t:Absolute pressure (hectopascal)
	p->press_diff1 = press_diff1; // int32_t:Differential pressure 1 (hectopascal)
	p->press_diff2 = press_diff2; // int32_t:Differential pressure 2 (hectopascal)

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_RAW_PRESSURE_LEN;
	hdr.msgid = MAVLINK_MSG_ID_RAW_PRESSURE;
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
// MESSAGE RAW_PRESSURE UNPACKING

/**
 * @brief Get field usec from raw_pressure message
 *
 * @return Timestamp (microseconds since UNIX epoch)
 */
static inline uint64_t mavlink_msg_raw_pressure_get_usec(const mavlink_message_t* msg)
{
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg->payload[0];
	return (uint64_t)(p->usec);
}

/**
 * @brief Get field press_abs from raw_pressure message
 *
 * @return Absolute pressure (hectopascal)
 */
static inline int32_t mavlink_msg_raw_pressure_get_press_abs(const mavlink_message_t* msg)
{
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg->payload[0];
	return (int32_t)(p->press_abs);
}

/**
 * @brief Get field press_diff1 from raw_pressure message
 *
 * @return Differential pressure 1 (hectopascal)
 */
static inline int32_t mavlink_msg_raw_pressure_get_press_diff1(const mavlink_message_t* msg)
{
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg->payload[0];
	return (int32_t)(p->press_diff1);
}

/**
 * @brief Get field press_diff2 from raw_pressure message
 *
 * @return Differential pressure 2 (hectopascal)
 */
static inline int32_t mavlink_msg_raw_pressure_get_press_diff2(const mavlink_message_t* msg)
{
	mavlink_raw_pressure_t *p = (mavlink_raw_pressure_t *)&msg->payload[0];
	return (int32_t)(p->press_diff2);
}

/**
 * @brief Decode a raw_pressure message into a struct
 *
 * @param msg The message to decode
 * @param raw_pressure C-struct to decode the message contents into
 */
static inline void mavlink_msg_raw_pressure_decode(const mavlink_message_t* msg, mavlink_raw_pressure_t* raw_pressure)
{
	memcpy( raw_pressure, msg->payload, sizeof(mavlink_raw_pressure_t));
}
