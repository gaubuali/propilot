// MESSAGE GPS_RAW PACKING

#define MAVLINK_MSG_ID_GPS_RAW 32

typedef struct __mavlink_gps_raw_t 
{
	uint64_t usec; ///< Timestamp (microseconds since unix epoch)
	uint8_t fix_type; ///< 0-1: no fix, 2: 2D fix, 3: 3D fix
	float lat; ///< X Position
	float lon; ///< Y Position
	float alt; ///< Z Position in meters
	float eph; ///< Uncertainty in meters of latitude
	float epv; ///< Uncertainty in meters of longitude
	float v; ///< Overall speed
	float hdg; ///< Heading, in FIXME

} mavlink_gps_raw_t;



/**
 * @brief Pack a gps_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (microseconds since unix epoch)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix
 * @param lat X Position
 * @param lon Y Position
 * @param alt Z Position in meters
 * @param eph Uncertainty in meters of latitude
 * @param epv Uncertainty in meters of longitude
 * @param v Overall speed
 * @param hdg Heading, in FIXME
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_raw_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint64_t usec, uint8_t fix_type, float lat, float lon, float alt, float eph, float epv, float v, float hdg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_GPS_RAW;

	p->usec = usec; // uint64_t:Timestamp (microseconds since unix epoch)
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix
	p->lat = lat; // float:X Position
	p->lon = lon; // float:Y Position
	p->alt = alt; // float:Z Position in meters
	p->eph = eph; // float:Uncertainty in meters of latitude
	p->epv = epv; // float:Uncertainty in meters of longitude
	p->v = v; // float:Overall speed
	p->hdg = hdg; // float:Heading, in FIXME

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_gps_raw_t));
}

/**
 * @brief Pack a gps_raw message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param usec Timestamp (microseconds since unix epoch)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix
 * @param lat X Position
 * @param lon Y Position
 * @param alt Z Position in meters
 * @param eph Uncertainty in meters of latitude
 * @param epv Uncertainty in meters of longitude
 * @param v Overall speed
 * @param hdg Heading, in FIXME
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_raw_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint64_t usec, uint8_t fix_type, float lat, float lon, float alt, float eph, float epv, float v, float hdg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_GPS_RAW;

	p->usec = usec; // uint64_t:Timestamp (microseconds since unix epoch)
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix
	p->lat = lat; // float:X Position
	p->lon = lon; // float:Y Position
	p->alt = alt; // float:Z Position in meters
	p->eph = eph; // float:Uncertainty in meters of latitude
	p->epv = epv; // float:Uncertainty in meters of longitude
	p->v = v; // float:Overall speed
	p->hdg = hdg; // float:Heading, in FIXME

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_gps_raw_t));
}

/**
 * @brief Encode a gps_raw struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps_raw C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_raw_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_raw_t* gps_raw)
{
	return mavlink_msg_gps_raw_pack(system_id, component_id, msg, gps_raw->usec, gps_raw->fix_type, gps_raw->lat, gps_raw->lon, gps_raw->alt, gps_raw->eph, gps_raw->epv, gps_raw->v, gps_raw->hdg);
}

/**
 * @brief Send a gps_raw message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (microseconds since unix epoch)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix
 * @param lat X Position
 * @param lon Y Position
 * @param alt Z Position in meters
 * @param eph Uncertainty in meters of latitude
 * @param epv Uncertainty in meters of longitude
 * @param v Overall speed
 * @param hdg Heading, in FIXME
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_raw_send(mavlink_channel_t chan, uint64_t usec, uint8_t fix_type, float lat, float lon, float alt, float eph, float epv, float v, float hdg)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_GPS_RAW;
	msg.len = sizeof(mavlink_gps_raw_t);
	p->usec = usec; // uint64_t:Timestamp (microseconds since unix epoch)
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix
	p->lat = lat; // float:X Position
	p->lon = lon; // float:Y Position
	p->alt = alt; // float:Z Position in meters
	p->eph = eph; // float:Uncertainty in meters of latitude
	p->epv = epv; // float:Uncertainty in meters of longitude
	p->v = v; // float:Overall speed
	p->hdg = hdg; // float:Heading, in FIXME

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
// MESSAGE GPS_RAW UNPACKING

/**
 * @brief Get field usec from gps_raw message
 *
 * @return Timestamp (microseconds since unix epoch)
 */
static inline uint64_t mavlink_msg_gps_raw_get_usec(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (uint64_t)(p->usec);
}

/**
 * @brief Get field fix_type from gps_raw message
 *
 * @return 0-1: no fix, 2: 2D fix, 3: 3D fix
 */
static inline uint8_t mavlink_msg_gps_raw_get_fix_type(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (uint8_t)(p->fix_type);
}

/**
 * @brief Get field lat from gps_raw message
 *
 * @return X Position
 */
static inline float mavlink_msg_gps_raw_get_lat(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->lat);
}

/**
 * @brief Get field lon from gps_raw message
 *
 * @return Y Position
 */
static inline float mavlink_msg_gps_raw_get_lon(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->lon);
}

/**
 * @brief Get field alt from gps_raw message
 *
 * @return Z Position in meters
 */
static inline float mavlink_msg_gps_raw_get_alt(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->alt);
}

/**
 * @brief Get field eph from gps_raw message
 *
 * @return Uncertainty in meters of latitude
 */
static inline float mavlink_msg_gps_raw_get_eph(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->eph);
}

/**
 * @brief Get field epv from gps_raw message
 *
 * @return Uncertainty in meters of longitude
 */
static inline float mavlink_msg_gps_raw_get_epv(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->epv);
}

/**
 * @brief Get field v from gps_raw message
 *
 * @return Overall speed
 */
static inline float mavlink_msg_gps_raw_get_v(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->v);
}

/**
 * @brief Get field hdg from gps_raw message
 *
 * @return Heading, in FIXME
 */
static inline float mavlink_msg_gps_raw_get_hdg(const mavlink_message_t* msg)
{
	mavlink_gps_raw_t *p = (mavlink_gps_raw_t *)&msg->payload[0];
	return (float)(p->hdg);
}

/**
 * @brief Decode a gps_raw message into a struct
 *
 * @param msg The message to decode
 * @param gps_raw C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_raw_decode(const mavlink_message_t* msg, mavlink_gps_raw_t* gps_raw)
{
	memcpy( gps_raw, msg->payload, sizeof(mavlink_gps_raw_t));
}
