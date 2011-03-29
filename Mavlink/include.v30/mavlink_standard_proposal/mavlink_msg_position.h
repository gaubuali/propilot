// MESSAGE POSITION PACKING

#define MAVLINK_MSG_ID_POSITION 55

typedef struct __mavlink_position_t 
{
	uint8_t type; ///< Position type: 0: Local, 1: Global
	float x; ///< X (long) Position
	float y; ///< Y (lat) Position
	float z; ///< Z (alt) Position
	float vx; ///< Vx
	float vy; ///< Vy
	float vz; ///< Vz

} mavlink_position_t;



/**
 * @brief Pack a position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type Position type: 0: Local, 1: Global
 * @param x X (long) Position
 * @param y Y (lat) Position
 * @param z Z (alt) Position
 * @param vx Vx
 * @param vy Vy
 * @param vz Vz
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_position_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t type, float x, float y, float z, float vx, float vy, float vz)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POSITION;

	p->type = type; // uint8_t:Position type: 0: Local, 1: Global
	p->x = x; // float:X (long) Position
	p->y = y; // float:Y (lat) Position
	p->z = z; // float:Z (alt) Position
	p->vx = vx; // float:Vx
	p->vy = vy; // float:Vy
	p->vz = vz; // float:Vz

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_position_t));
}

/**
 * @brief Pack a position message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param type Position type: 0: Local, 1: Global
 * @param x X (long) Position
 * @param y Y (lat) Position
 * @param z Z (alt) Position
 * @param vx Vx
 * @param vy Vy
 * @param vz Vz
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_position_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t type, float x, float y, float z, float vx, float vy, float vz)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POSITION;

	p->type = type; // uint8_t:Position type: 0: Local, 1: Global
	p->x = x; // float:X (long) Position
	p->y = y; // float:Y (lat) Position
	p->z = z; // float:Z (alt) Position
	p->vx = vx; // float:Vx
	p->vy = vy; // float:Vy
	p->vz = vz; // float:Vz

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_position_t));
}

/**
 * @brief Encode a position struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param position C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_position_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_position_t* position)
{
	return mavlink_msg_position_pack(system_id, component_id, msg, position->type, position->x, position->y, position->z, position->vx, position->vy, position->vz);
}

/**
 * @brief Send a position message
 * @param chan MAVLink channel to send the message
 *
 * @param type Position type: 0: Local, 1: Global
 * @param x X (long) Position
 * @param y Y (lat) Position
 * @param z Z (alt) Position
 * @param vx Vx
 * @param vy Vy
 * @param vz Vz
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_position_send(mavlink_channel_t chan, uint8_t type, float x, float y, float z, float vx, float vy, float vz)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_position_t *p = (mavlink_position_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_POSITION;
	msg.len = sizeof(mavlink_position_t);
	p->type = type; // uint8_t:Position type: 0: Local, 1: Global
	p->x = x; // float:X (long) Position
	p->y = y; // float:Y (lat) Position
	p->z = z; // float:Z (alt) Position
	p->vx = vx; // float:Vx
	p->vy = vy; // float:Vy
	p->vz = vz; // float:Vz

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
// MESSAGE POSITION UNPACKING

/**
 * @brief Get field type from position message
 *
 * @return Position type: 0: Local, 1: Global
 */
static inline uint8_t mavlink_msg_position_get_type(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (uint8_t)(p->type);
}

/**
 * @brief Get field x from position message
 *
 * @return X (long) Position
 */
static inline float mavlink_msg_position_get_x(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from position message
 *
 * @return Y (lat) Position
 */
static inline float mavlink_msg_position_get_y(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from position message
 *
 * @return Z (alt) Position
 */
static inline float mavlink_msg_position_get_z(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field vx from position message
 *
 * @return Vx
 */
static inline float mavlink_msg_position_get_vx(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (float)(p->vx);
}

/**
 * @brief Get field vy from position message
 *
 * @return Vy
 */
static inline float mavlink_msg_position_get_vy(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (float)(p->vy);
}

/**
 * @brief Get field vz from position message
 *
 * @return Vz
 */
static inline float mavlink_msg_position_get_vz(const mavlink_message_t* msg)
{
	mavlink_position_t *p = (mavlink_position_t *)&msg->payload[0];
	return (float)(p->vz);
}

/**
 * @brief Decode a position message into a struct
 *
 * @param msg The message to decode
 * @param position C-struct to decode the message contents into
 */
static inline void mavlink_msg_position_decode(const mavlink_message_t* msg, mavlink_position_t* position)
{
	memcpy( position, msg->payload, sizeof(mavlink_position_t));
}
