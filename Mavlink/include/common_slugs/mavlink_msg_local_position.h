// MESSAGE LOCAL_POSITION PACKING

#define MAVLINK_MSG_ID_LOCAL_POSITION 31
#define MAVLINK_MSG_31_LEN 32

typedef struct __mavlink_local_position_t 
{
	uint64_t usec; ///< Timestamp (microseconds since unix epoch)
	float x; ///< X Position
	float y; ///< Y Position
	float z; ///< Z Position
	float vx; ///< X Speed
	float vy; ///< Y Speed
	float vz; ///< Z Speed
} mavlink_local_position_t;

//#if sizeof(mavlink_local_position_t) != 32 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a local_position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (microseconds since unix epoch)
 * @param x X Position
 * @param y Y Position
 * @param z Z Position
 * @param vx X Speed
 * @param vy Y Speed
 * @param vz Z Speed
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_local_position_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint64_t usec, float x, float y, float z, float vx, float vy, float vz)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_LOCAL_POSITION;

	p->usec = usec; // uint64_t:Timestamp (microseconds since unix epoch)
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	p->vx = vx; // float:X Speed
	p->vy = vy; // float:Y Speed
	p->vz = vz; // float:Z Speed

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_local_position_t));
}

/**
 * @brief Pack a local_position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param usec Timestamp (microseconds since unix epoch)
 * @param x X Position
 * @param y Y Position
 * @param z Z Position
 * @param vx X Speed
 * @param vy Y Speed
 * @param vz Z Speed
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_local_position_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint64_t usec, float x, float y, float z, float vx, float vy, float vz)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_LOCAL_POSITION;

	p->usec = usec; // uint64_t:Timestamp (microseconds since unix epoch)
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	p->vx = vx; // float:X Speed
	p->vy = vy; // float:Y Speed
	p->vz = vz; // float:Z Speed

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_local_position_t));
}

/**
 * @brief Encode a local_position struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param local_position C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_local_position_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_local_position_t* local_position)
{
	return mavlink_msg_local_position_pack(system_id, component_id, msg, local_position->usec, local_position->x, local_position->y, local_position->z, local_position->vx, local_position->vy, local_position->vz);
}

/**
 * @brief Send a local_position message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (microseconds since unix epoch)
 * @param x X Position
 * @param y Y Position
 * @param z Z Position
 * @param vx X Speed
 * @param vy Y Speed
 * @param vz Z Speed
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_local_position_send(mavlink_channel_t chan, uint64_t usec, float x, float y, float z, float vx, float vy, float vz)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_LOCAL_POSITION;
	msg.len = sizeof(mavlink_local_position_t);
	p->usec = usec; // uint64_t:Timestamp (microseconds since unix epoch)
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	p->vx = vx; // float:X Speed
	p->vy = vy; // float:Y Speed
	p->vz = vz; // float:Z Speed

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
// MESSAGE LOCAL_POSITION UNPACKING

/**
 * @brief Get field usec from local_position message
 *
 * @return Timestamp (microseconds since unix epoch)
 */
static inline uint64_t mavlink_msg_local_position_get_usec(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (uint64_t)(p->usec);
}

/**
 * @brief Get field x from local_position message
 *
 * @return X Position
 */
static inline float mavlink_msg_local_position_get_x(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from local_position message
 *
 * @return Y Position
 */
static inline float mavlink_msg_local_position_get_y(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from local_position message
 *
 * @return Z Position
 */
static inline float mavlink_msg_local_position_get_z(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field vx from local_position message
 *
 * @return X Speed
 */
static inline float mavlink_msg_local_position_get_vx(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (float)(p->vx);
}

/**
 * @brief Get field vy from local_position message
 *
 * @return Y Speed
 */
static inline float mavlink_msg_local_position_get_vy(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (float)(p->vy);
}

/**
 * @brief Get field vz from local_position message
 *
 * @return Z Speed
 */
static inline float mavlink_msg_local_position_get_vz(const mavlink_message_t* msg)
{
	mavlink_local_position_t *p = (mavlink_local_position_t *)&msg->payload[0];
	return (float)(p->vz);
}

/**
 * @brief Decode a local_position message into a struct
 *
 * @param msg The message to decode
 * @param local_position C-struct to decode the message contents into
 */
static inline void mavlink_msg_local_position_decode(const mavlink_message_t* msg, mavlink_local_position_t* local_position)
{
	memcpy( local_position, msg->payload, sizeof(mavlink_local_position_t));
}