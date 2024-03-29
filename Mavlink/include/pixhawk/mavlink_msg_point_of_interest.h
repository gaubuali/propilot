// MESSAGE POINT_OF_INTEREST PACKING

#define MAVLINK_MSG_ID_POINT_OF_INTEREST 161
#define MAVLINK_MSG_ID_POINT_OF_INTEREST_LEN 42
#define MAVLINK_MSG_161_LEN 42

typedef struct __mavlink_point_of_interest_t 
{
	uint8_t type; ///< 0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
	uint8_t color; ///< 0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
	uint8_t coordinate_system; ///< 0: global, 1:local
	uint16_t timeout; ///< 0: no timeout, >1: timeout in seconds
	float x; ///< X Position
	float y; ///< Y Position
	float z; ///< Z Position
	int8_t name[25]; ///< POI name
} mavlink_point_of_interest_t;

#define MAVLINK_MSG_POINT_OF_INTEREST_FIELD_NAME_LEN 25

/**
 * @brief Pack a point_of_interest message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type 0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
 * @param color 0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
 * @param coordinate_system 0: global, 1:local
 * @param timeout 0: no timeout, >1: timeout in seconds
 * @param x X Position
 * @param y Y Position
 * @param z Z Position
 * @param name POI name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_point_of_interest_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t type, uint8_t color, uint8_t coordinate_system, uint16_t timeout, float x, float y, float z, const int8_t* name)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POINT_OF_INTEREST;

	p->type = type; // uint8_t:0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
	p->color = color; // uint8_t:0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
	p->coordinate_system = coordinate_system; // uint8_t:0: global, 1:local
	p->timeout = timeout; // uint16_t:0: no timeout, >1: timeout in seconds
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	memcpy( p->name, name, sizeof(p->name)); // array[25]:POI name

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POINT_OF_INTEREST_LEN);
}

/**
 * @brief Pack a point_of_interest message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param type 0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
 * @param color 0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
 * @param coordinate_system 0: global, 1:local
 * @param timeout 0: no timeout, >1: timeout in seconds
 * @param x X Position
 * @param y Y Position
 * @param z Z Position
 * @param name POI name
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_point_of_interest_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t type, uint8_t color, uint8_t coordinate_system, uint16_t timeout, float x, float y, float z, const int8_t* name)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POINT_OF_INTEREST;

	p->type = type; // uint8_t:0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
	p->color = color; // uint8_t:0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
	p->coordinate_system = coordinate_system; // uint8_t:0: global, 1:local
	p->timeout = timeout; // uint16_t:0: no timeout, >1: timeout in seconds
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	memcpy( p->name, name, sizeof(p->name)); // array[25]:POI name

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POINT_OF_INTEREST_LEN);
}

/**
 * @brief Encode a point_of_interest struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param point_of_interest C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_point_of_interest_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_point_of_interest_t* point_of_interest)
{
	return mavlink_msg_point_of_interest_pack(system_id, component_id, msg, point_of_interest->type, point_of_interest->color, point_of_interest->coordinate_system, point_of_interest->timeout, point_of_interest->x, point_of_interest->y, point_of_interest->z, point_of_interest->name);
}

/**
 * @brief Send a point_of_interest message
 * @param chan MAVLink channel to send the message
 *
 * @param type 0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
 * @param color 0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
 * @param coordinate_system 0: global, 1:local
 * @param timeout 0: no timeout, >1: timeout in seconds
 * @param x X Position
 * @param y Y Position
 * @param z Z Position
 * @param name POI name
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_point_of_interest_send(mavlink_channel_t chan, uint8_t type, uint8_t color, uint8_t coordinate_system, uint16_t timeout, float x, float y, float z, const int8_t* name)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg.payload[0];

	p->type = type; // uint8_t:0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
	p->color = color; // uint8_t:0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
	p->coordinate_system = coordinate_system; // uint8_t:0: global, 1:local
	p->timeout = timeout; // uint16_t:0: no timeout, >1: timeout in seconds
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	memcpy( p->name, name, sizeof(p->name)); // array[25]:POI name

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_POINT_OF_INTEREST_LEN;
	msg.msgid = MAVLINK_MSG_ID_POINT_OF_INTEREST;
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
static inline void mavlink_msg_point_of_interest_send(mavlink_channel_t chan, uint8_t type, uint8_t color, uint8_t coordinate_system, uint16_t timeout, float x, float y, float z, const int8_t* name)
{
	mavlink_header_t hdr;
	mavlink_point_of_interest_t payload;
	uint16_t checksum;
	mavlink_point_of_interest_t *p = &payload;

	p->type = type; // uint8_t:0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
	p->color = color; // uint8_t:0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
	p->coordinate_system = coordinate_system; // uint8_t:0: global, 1:local
	p->timeout = timeout; // uint16_t:0: no timeout, >1: timeout in seconds
	p->x = x; // float:X Position
	p->y = y; // float:Y Position
	p->z = z; // float:Z Position
	memcpy( p->name, name, sizeof(p->name)); // array[25]:POI name

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_POINT_OF_INTEREST_LEN;
	hdr.msgid = MAVLINK_MSG_ID_POINT_OF_INTEREST;
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
// MESSAGE POINT_OF_INTEREST UNPACKING

/**
 * @brief Get field type from point_of_interest message
 *
 * @return 0: Notice, 1: Warning, 2: Critical, 3: Emergency, 4: Debug
 */
static inline uint8_t mavlink_msg_point_of_interest_get_type(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (uint8_t)(p->type);
}

/**
 * @brief Get field color from point_of_interest message
 *
 * @return 0: blue, 1: yellow, 2: red, 3: orange, 4: green, 5: magenta
 */
static inline uint8_t mavlink_msg_point_of_interest_get_color(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (uint8_t)(p->color);
}

/**
 * @brief Get field coordinate_system from point_of_interest message
 *
 * @return 0: global, 1:local
 */
static inline uint8_t mavlink_msg_point_of_interest_get_coordinate_system(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (uint8_t)(p->coordinate_system);
}

/**
 * @brief Get field timeout from point_of_interest message
 *
 * @return 0: no timeout, >1: timeout in seconds
 */
static inline uint16_t mavlink_msg_point_of_interest_get_timeout(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (uint16_t)(p->timeout);
}

/**
 * @brief Get field x from point_of_interest message
 *
 * @return X Position
 */
static inline float mavlink_msg_point_of_interest_get_x(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from point_of_interest message
 *
 * @return Y Position
 */
static inline float mavlink_msg_point_of_interest_get_y(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from point_of_interest message
 *
 * @return Z Position
 */
static inline float mavlink_msg_point_of_interest_get_z(const mavlink_message_t* msg)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field name from point_of_interest message
 *
 * @return POI name
 */
static inline uint16_t mavlink_msg_point_of_interest_get_name(const mavlink_message_t* msg, int8_t* name)
{
	mavlink_point_of_interest_t *p = (mavlink_point_of_interest_t *)&msg->payload[0];

	memcpy(name, p->name, sizeof(p->name));
	return sizeof(p->name);
}

/**
 * @brief Decode a point_of_interest message into a struct
 *
 * @param msg The message to decode
 * @param point_of_interest C-struct to decode the message contents into
 */
static inline void mavlink_msg_point_of_interest_decode(const mavlink_message_t* msg, mavlink_point_of_interest_t* point_of_interest)
{
	memcpy( point_of_interest, msg->payload, sizeof(mavlink_point_of_interest_t));
}
