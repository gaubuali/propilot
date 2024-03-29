// MESSAGE NAV_CONTROLLER_OUTPUT PACKING

#define MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT 62
#define MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT_LEN 26
#define MAVLINK_MSG_62_LEN 26

typedef struct __mavlink_nav_controller_output_t 
{
	float nav_roll; ///< Current desired roll in degrees
	float nav_pitch; ///< Current desired pitch in degrees
	int16_t nav_bearing; ///< Current desired heading in degrees
	int16_t target_bearing; ///< Bearing to current waypoint/target in degrees
	uint16_t wp_dist; ///< Distance to active waypoint in meters
	float alt_error; ///< Current altitude error in meters
	float aspd_error; ///< Current airspeed error in meters/second
	float xtrack_error; ///< Current crosstrack error on x-y plane in meters
} mavlink_nav_controller_output_t;


/**
 * @brief Pack a nav_controller_output message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param nav_roll Current desired roll in degrees
 * @param nav_pitch Current desired pitch in degrees
 * @param nav_bearing Current desired heading in degrees
 * @param target_bearing Bearing to current waypoint/target in degrees
 * @param wp_dist Distance to active waypoint in meters
 * @param alt_error Current altitude error in meters
 * @param aspd_error Current airspeed error in meters/second
 * @param xtrack_error Current crosstrack error on x-y plane in meters
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nav_controller_output_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, float nav_roll, float nav_pitch, int16_t nav_bearing, int16_t target_bearing, uint16_t wp_dist, float alt_error, float aspd_error, float xtrack_error)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT;

	p->nav_roll = nav_roll; // float:Current desired roll in degrees
	p->nav_pitch = nav_pitch; // float:Current desired pitch in degrees
	p->nav_bearing = nav_bearing; // int16_t:Current desired heading in degrees
	p->target_bearing = target_bearing; // int16_t:Bearing to current waypoint/target in degrees
	p->wp_dist = wp_dist; // uint16_t:Distance to active waypoint in meters
	p->alt_error = alt_error; // float:Current altitude error in meters
	p->aspd_error = aspd_error; // float:Current airspeed error in meters/second
	p->xtrack_error = xtrack_error; // float:Current crosstrack error on x-y plane in meters

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT_LEN);
}

/**
 * @brief Pack a nav_controller_output message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param nav_roll Current desired roll in degrees
 * @param nav_pitch Current desired pitch in degrees
 * @param nav_bearing Current desired heading in degrees
 * @param target_bearing Bearing to current waypoint/target in degrees
 * @param wp_dist Distance to active waypoint in meters
 * @param alt_error Current altitude error in meters
 * @param aspd_error Current airspeed error in meters/second
 * @param xtrack_error Current crosstrack error on x-y plane in meters
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_nav_controller_output_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, float nav_roll, float nav_pitch, int16_t nav_bearing, int16_t target_bearing, uint16_t wp_dist, float alt_error, float aspd_error, float xtrack_error)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT;

	p->nav_roll = nav_roll; // float:Current desired roll in degrees
	p->nav_pitch = nav_pitch; // float:Current desired pitch in degrees
	p->nav_bearing = nav_bearing; // int16_t:Current desired heading in degrees
	p->target_bearing = target_bearing; // int16_t:Bearing to current waypoint/target in degrees
	p->wp_dist = wp_dist; // uint16_t:Distance to active waypoint in meters
	p->alt_error = alt_error; // float:Current altitude error in meters
	p->aspd_error = aspd_error; // float:Current airspeed error in meters/second
	p->xtrack_error = xtrack_error; // float:Current crosstrack error on x-y plane in meters

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT_LEN);
}

/**
 * @brief Encode a nav_controller_output struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param nav_controller_output C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_nav_controller_output_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_nav_controller_output_t* nav_controller_output)
{
	return mavlink_msg_nav_controller_output_pack(system_id, component_id, msg, nav_controller_output->nav_roll, nav_controller_output->nav_pitch, nav_controller_output->nav_bearing, nav_controller_output->target_bearing, nav_controller_output->wp_dist, nav_controller_output->alt_error, nav_controller_output->aspd_error, nav_controller_output->xtrack_error);
}

/**
 * @brief Send a nav_controller_output message
 * @param chan MAVLink channel to send the message
 *
 * @param nav_roll Current desired roll in degrees
 * @param nav_pitch Current desired pitch in degrees
 * @param nav_bearing Current desired heading in degrees
 * @param target_bearing Bearing to current waypoint/target in degrees
 * @param wp_dist Distance to active waypoint in meters
 * @param alt_error Current altitude error in meters
 * @param aspd_error Current airspeed error in meters/second
 * @param xtrack_error Current crosstrack error on x-y plane in meters
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_nav_controller_output_send(mavlink_channel_t chan, float nav_roll, float nav_pitch, int16_t nav_bearing, int16_t target_bearing, uint16_t wp_dist, float alt_error, float aspd_error, float xtrack_error)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg.payload[0];

	p->nav_roll = nav_roll; // float:Current desired roll in degrees
	p->nav_pitch = nav_pitch; // float:Current desired pitch in degrees
	p->nav_bearing = nav_bearing; // int16_t:Current desired heading in degrees
	p->target_bearing = target_bearing; // int16_t:Bearing to current waypoint/target in degrees
	p->wp_dist = wp_dist; // uint16_t:Distance to active waypoint in meters
	p->alt_error = alt_error; // float:Current altitude error in meters
	p->aspd_error = aspd_error; // float:Current airspeed error in meters/second
	p->xtrack_error = xtrack_error; // float:Current crosstrack error on x-y plane in meters

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT_LEN;
	msg.msgid = MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT;
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
static inline void mavlink_msg_nav_controller_output_send(mavlink_channel_t chan, float nav_roll, float nav_pitch, int16_t nav_bearing, int16_t target_bearing, uint16_t wp_dist, float alt_error, float aspd_error, float xtrack_error)
{
	mavlink_header_t hdr;
	mavlink_nav_controller_output_t payload;
	uint16_t checksum;
	mavlink_nav_controller_output_t *p = &payload;

	p->nav_roll = nav_roll; // float:Current desired roll in degrees
	p->nav_pitch = nav_pitch; // float:Current desired pitch in degrees
	p->nav_bearing = nav_bearing; // int16_t:Current desired heading in degrees
	p->target_bearing = target_bearing; // int16_t:Bearing to current waypoint/target in degrees
	p->wp_dist = wp_dist; // uint16_t:Distance to active waypoint in meters
	p->alt_error = alt_error; // float:Current altitude error in meters
	p->aspd_error = aspd_error; // float:Current airspeed error in meters/second
	p->xtrack_error = xtrack_error; // float:Current crosstrack error on x-y plane in meters

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT_LEN;
	hdr.msgid = MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT;
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
// MESSAGE NAV_CONTROLLER_OUTPUT UNPACKING

/**
 * @brief Get field nav_roll from nav_controller_output message
 *
 * @return Current desired roll in degrees
 */
static inline float mavlink_msg_nav_controller_output_get_nav_roll(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (float)(p->nav_roll);
}

/**
 * @brief Get field nav_pitch from nav_controller_output message
 *
 * @return Current desired pitch in degrees
 */
static inline float mavlink_msg_nav_controller_output_get_nav_pitch(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (float)(p->nav_pitch);
}

/**
 * @brief Get field nav_bearing from nav_controller_output message
 *
 * @return Current desired heading in degrees
 */
static inline int16_t mavlink_msg_nav_controller_output_get_nav_bearing(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (int16_t)(p->nav_bearing);
}

/**
 * @brief Get field target_bearing from nav_controller_output message
 *
 * @return Bearing to current waypoint/target in degrees
 */
static inline int16_t mavlink_msg_nav_controller_output_get_target_bearing(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (int16_t)(p->target_bearing);
}

/**
 * @brief Get field wp_dist from nav_controller_output message
 *
 * @return Distance to active waypoint in meters
 */
static inline uint16_t mavlink_msg_nav_controller_output_get_wp_dist(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (uint16_t)(p->wp_dist);
}

/**
 * @brief Get field alt_error from nav_controller_output message
 *
 * @return Current altitude error in meters
 */
static inline float mavlink_msg_nav_controller_output_get_alt_error(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (float)(p->alt_error);
}

/**
 * @brief Get field aspd_error from nav_controller_output message
 *
 * @return Current airspeed error in meters/second
 */
static inline float mavlink_msg_nav_controller_output_get_aspd_error(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (float)(p->aspd_error);
}

/**
 * @brief Get field xtrack_error from nav_controller_output message
 *
 * @return Current crosstrack error on x-y plane in meters
 */
static inline float mavlink_msg_nav_controller_output_get_xtrack_error(const mavlink_message_t* msg)
{
	mavlink_nav_controller_output_t *p = (mavlink_nav_controller_output_t *)&msg->payload[0];
	return (float)(p->xtrack_error);
}

/**
 * @brief Decode a nav_controller_output message into a struct
 *
 * @param msg The message to decode
 * @param nav_controller_output C-struct to decode the message contents into
 */
static inline void mavlink_msg_nav_controller_output_decode(const mavlink_message_t* msg, mavlink_nav_controller_output_t* nav_controller_output)
{
	memcpy( nav_controller_output, msg->payload, sizeof(mavlink_nav_controller_output_t));
}
