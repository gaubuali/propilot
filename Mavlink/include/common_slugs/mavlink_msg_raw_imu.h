// MESSAGE RAW_IMU PACKING

#define MAVLINK_MSG_ID_RAW_IMU 28
#define MAVLINK_MSG_28_LEN 26

typedef struct __mavlink_raw_imu_t 
{
	uint64_t usec; ///< Timestamp (microseconds since UNIX epoch)
	int16_t xacc; ///< X acceleration (mg raw)
	int16_t yacc; ///< Y acceleration (mg raw)
	int16_t zacc; ///< Z acceleration (mg raw)
	int16_t xgyro; ///< Angular speed around X axis (adc units)
	int16_t ygyro; ///< Angular speed around Y axis (adc units)
	int16_t zgyro; ///< Angular speed around Z axis (adc units)
	int16_t xmag; ///< X Magnetic field (milli tesla)
	int16_t ymag; ///< Y Magnetic field (milli tesla)
	int16_t zmag; ///< Z Magnetic field (milli tesla)
} mavlink_raw_imu_t;

//#if sizeof(mavlink_raw_imu_t) != 26 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a raw_imu message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (microseconds since UNIX epoch)
 * @param xacc X acceleration (mg raw)
 * @param yacc Y acceleration (mg raw)
 * @param zacc Z acceleration (mg raw)
 * @param xgyro Angular speed around X axis (adc units)
 * @param ygyro Angular speed around Y axis (adc units)
 * @param zgyro Angular speed around Z axis (adc units)
 * @param xmag X Magnetic field (milli tesla)
 * @param ymag Y Magnetic field (milli tesla)
 * @param zmag Z Magnetic field (milli tesla)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_imu_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint64_t usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RAW_IMU;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->xacc = xacc; // int16_t:X acceleration (mg raw)
	p->yacc = yacc; // int16_t:Y acceleration (mg raw)
	p->zacc = zacc; // int16_t:Z acceleration (mg raw)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (milli tesla)
	p->ymag = ymag; // int16_t:Y Magnetic field (milli tesla)
	p->zmag = zmag; // int16_t:Z Magnetic field (milli tesla)

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_raw_imu_t));
}

/**
 * @brief Pack a raw_imu message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param usec Timestamp (microseconds since UNIX epoch)
 * @param xacc X acceleration (mg raw)
 * @param yacc Y acceleration (mg raw)
 * @param zacc Z acceleration (mg raw)
 * @param xgyro Angular speed around X axis (adc units)
 * @param ygyro Angular speed around Y axis (adc units)
 * @param zgyro Angular speed around Z axis (adc units)
 * @param xmag X Magnetic field (milli tesla)
 * @param ymag Y Magnetic field (milli tesla)
 * @param zmag Z Magnetic field (milli tesla)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_imu_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint64_t usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RAW_IMU;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->xacc = xacc; // int16_t:X acceleration (mg raw)
	p->yacc = yacc; // int16_t:Y acceleration (mg raw)
	p->zacc = zacc; // int16_t:Z acceleration (mg raw)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (milli tesla)
	p->ymag = ymag; // int16_t:Y Magnetic field (milli tesla)
	p->zmag = zmag; // int16_t:Z Magnetic field (milli tesla)

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_raw_imu_t));
}

/**
 * @brief Encode a raw_imu struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param raw_imu C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_raw_imu_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_raw_imu_t* raw_imu)
{
	return mavlink_msg_raw_imu_pack(system_id, component_id, msg, raw_imu->usec, raw_imu->xacc, raw_imu->yacc, raw_imu->zacc, raw_imu->xgyro, raw_imu->ygyro, raw_imu->zgyro, raw_imu->xmag, raw_imu->ymag, raw_imu->zmag);
}

/**
 * @brief Send a raw_imu message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (microseconds since UNIX epoch)
 * @param xacc X acceleration (mg raw)
 * @param yacc Y acceleration (mg raw)
 * @param zacc Z acceleration (mg raw)
 * @param xgyro Angular speed around X axis (adc units)
 * @param ygyro Angular speed around Y axis (adc units)
 * @param zgyro Angular speed around Z axis (adc units)
 * @param xmag X Magnetic field (milli tesla)
 * @param ymag Y Magnetic field (milli tesla)
 * @param zmag Z Magnetic field (milli tesla)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_raw_imu_send(mavlink_channel_t chan, uint64_t usec, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_RAW_IMU;
	msg.len = sizeof(mavlink_raw_imu_t);
	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch)
	p->xacc = xacc; // int16_t:X acceleration (mg raw)
	p->yacc = yacc; // int16_t:Y acceleration (mg raw)
	p->zacc = zacc; // int16_t:Z acceleration (mg raw)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (milli tesla)
	p->ymag = ymag; // int16_t:Y Magnetic field (milli tesla)
	p->zmag = zmag; // int16_t:Z Magnetic field (milli tesla)

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
// MESSAGE RAW_IMU UNPACKING

/**
 * @brief Get field usec from raw_imu message
 *
 * @return Timestamp (microseconds since UNIX epoch)
 */
static inline uint64_t mavlink_msg_raw_imu_get_usec(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (uint64_t)(p->usec);
}

/**
 * @brief Get field xacc from raw_imu message
 *
 * @return X acceleration (mg raw)
 */
static inline int16_t mavlink_msg_raw_imu_get_xacc(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->xacc);
}

/**
 * @brief Get field yacc from raw_imu message
 *
 * @return Y acceleration (mg raw)
 */
static inline int16_t mavlink_msg_raw_imu_get_yacc(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->yacc);
}

/**
 * @brief Get field zacc from raw_imu message
 *
 * @return Z acceleration (mg raw)
 */
static inline int16_t mavlink_msg_raw_imu_get_zacc(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->zacc);
}

/**
 * @brief Get field xgyro from raw_imu message
 *
 * @return Angular speed around X axis (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_xgyro(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->xgyro);
}

/**
 * @brief Get field ygyro from raw_imu message
 *
 * @return Angular speed around Y axis (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_ygyro(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->ygyro);
}

/**
 * @brief Get field zgyro from raw_imu message
 *
 * @return Angular speed around Z axis (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_zgyro(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->zgyro);
}

/**
 * @brief Get field xmag from raw_imu message
 *
 * @return X Magnetic field (milli tesla)
 */
static inline int16_t mavlink_msg_raw_imu_get_xmag(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->xmag);
}

/**
 * @brief Get field ymag from raw_imu message
 *
 * @return Y Magnetic field (milli tesla)
 */
static inline int16_t mavlink_msg_raw_imu_get_ymag(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->ymag);
}

/**
 * @brief Get field zmag from raw_imu message
 *
 * @return Z Magnetic field (milli tesla)
 */
static inline int16_t mavlink_msg_raw_imu_get_zmag(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->zmag);
}

/**
 * @brief Decode a raw_imu message into a struct
 *
 * @param msg The message to decode
 * @param raw_imu C-struct to decode the message contents into
 */
static inline void mavlink_msg_raw_imu_decode(const mavlink_message_t* msg, mavlink_raw_imu_t* raw_imu)
{
	memcpy( raw_imu, msg->payload, sizeof(mavlink_raw_imu_t));
}
