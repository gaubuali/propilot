// MESSAGE VFR_HUD PACKING

#define MAVLINK_MSG_ID_VFR_HUD 74

typedef struct __mavlink_vfr_hud_t 
{
	float airspeed; ///< Current airspeed in m/s
	float groundspeed; ///< Current ground speed in m/s
	int16_t heading; ///< Current heading in degrees, in compass units (0..360, 0=north)
	uint16_t throttle; ///< Current throttle setting in integer percent, 0 to 100
	float alt; ///< Current altitude (MSL), in meters
	float climb; ///< Current climb rate in meters/second

} mavlink_vfr_hud_t;



/**
 * @brief Pack a vfr_hud message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param airspeed Current airspeed in m/s
 * @param groundspeed Current ground speed in m/s
 * @param heading Current heading in degrees, in compass units (0..360, 0=north)
 * @param throttle Current throttle setting in integer percent, 0 to 100
 * @param alt Current altitude (MSL), in meters
 * @param climb Current climb rate in meters/second
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vfr_hud_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_VFR_HUD;

	p->airspeed = airspeed; // float:Current airspeed in m/s
	p->groundspeed = groundspeed; // float:Current ground speed in m/s
	p->heading = heading; // int16_t:Current heading in degrees, in compass units (0..360, 0=north)
	p->throttle = throttle; // uint16_t:Current throttle setting in integer percent, 0 to 100
	p->alt = alt; // float:Current altitude (MSL), in meters
	p->climb = climb; // float:Current climb rate in meters/second

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_vfr_hud_t));
}

/**
 * @brief Pack a vfr_hud message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param airspeed Current airspeed in m/s
 * @param groundspeed Current ground speed in m/s
 * @param heading Current heading in degrees, in compass units (0..360, 0=north)
 * @param throttle Current throttle setting in integer percent, 0 to 100
 * @param alt Current altitude (MSL), in meters
 * @param climb Current climb rate in meters/second
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vfr_hud_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_VFR_HUD;

	p->airspeed = airspeed; // float:Current airspeed in m/s
	p->groundspeed = groundspeed; // float:Current ground speed in m/s
	p->heading = heading; // int16_t:Current heading in degrees, in compass units (0..360, 0=north)
	p->throttle = throttle; // uint16_t:Current throttle setting in integer percent, 0 to 100
	p->alt = alt; // float:Current altitude (MSL), in meters
	p->climb = climb; // float:Current climb rate in meters/second

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_vfr_hud_t));
}

/**
 * @brief Encode a vfr_hud struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param vfr_hud C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vfr_hud_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_vfr_hud_t* vfr_hud)
{
	return mavlink_msg_vfr_hud_pack(system_id, component_id, msg, vfr_hud->airspeed, vfr_hud->groundspeed, vfr_hud->heading, vfr_hud->throttle, vfr_hud->alt, vfr_hud->climb);
}

/**
 * @brief Send a vfr_hud message
 * @param chan MAVLink channel to send the message
 *
 * @param airspeed Current airspeed in m/s
 * @param groundspeed Current ground speed in m/s
 * @param heading Current heading in degrees, in compass units (0..360, 0=north)
 * @param throttle Current throttle setting in integer percent, 0 to 100
 * @param alt Current altitude (MSL), in meters
 * @param climb Current climb rate in meters/second
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_vfr_hud_send(mavlink_channel_t chan, float airspeed, float groundspeed, int16_t heading, uint16_t throttle, float alt, float climb)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_VFR_HUD;
	msg.len = sizeof(mavlink_vfr_hud_t);
	p->airspeed = airspeed; // float:Current airspeed in m/s
	p->groundspeed = groundspeed; // float:Current ground speed in m/s
	p->heading = heading; // int16_t:Current heading in degrees, in compass units (0..360, 0=north)
	p->throttle = throttle; // uint16_t:Current throttle setting in integer percent, 0 to 100
	p->alt = alt; // float:Current altitude (MSL), in meters
	p->climb = climb; // float:Current climb rate in meters/second

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
// MESSAGE VFR_HUD UNPACKING

/**
 * @brief Get field airspeed from vfr_hud message
 *
 * @return Current airspeed in m/s
 */
static inline float mavlink_msg_vfr_hud_get_airspeed(const mavlink_message_t* msg)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	return (float)(p->airspeed);
}

/**
 * @brief Get field groundspeed from vfr_hud message
 *
 * @return Current ground speed in m/s
 */
static inline float mavlink_msg_vfr_hud_get_groundspeed(const mavlink_message_t* msg)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	return (float)(p->groundspeed);
}

/**
 * @brief Get field heading from vfr_hud message
 *
 * @return Current heading in degrees, in compass units (0..360, 0=north)
 */
static inline int16_t mavlink_msg_vfr_hud_get_heading(const mavlink_message_t* msg)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	return (int16_t)(p->heading);
}

/**
 * @brief Get field throttle from vfr_hud message
 *
 * @return Current throttle setting in integer percent, 0 to 100
 */
static inline uint16_t mavlink_msg_vfr_hud_get_throttle(const mavlink_message_t* msg)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	return (uint16_t)(p->throttle);
}

/**
 * @brief Get field alt from vfr_hud message
 *
 * @return Current altitude (MSL), in meters
 */
static inline float mavlink_msg_vfr_hud_get_alt(const mavlink_message_t* msg)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	return (float)(p->alt);
}

/**
 * @brief Get field climb from vfr_hud message
 *
 * @return Current climb rate in meters/second
 */
static inline float mavlink_msg_vfr_hud_get_climb(const mavlink_message_t* msg)
{
	mavlink_vfr_hud_t *p = (mavlink_vfr_hud_t *)&msg->payload[0];
	return (float)(p->climb);
}

/**
 * @brief Decode a vfr_hud message into a struct
 *
 * @param msg The message to decode
 * @param vfr_hud C-struct to decode the message contents into
 */
static inline void mavlink_msg_vfr_hud_decode(const mavlink_message_t* msg, mavlink_vfr_hud_t* vfr_hud)
{
	memcpy( vfr_hud, msg->payload, sizeof(mavlink_vfr_hud_t));
}
