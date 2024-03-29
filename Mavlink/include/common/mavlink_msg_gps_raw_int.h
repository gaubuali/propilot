// MESSAGE GPS_RAW_INT PACKING

#define MAVLINK_MSG_ID_GPS_RAW_INT 25
#define MAVLINK_MSG_ID_GPS_RAW_INT_LEN 37
#define MAVLINK_MSG_25_LEN 37

typedef struct __mavlink_gps_raw_int_t 
{
	uint64_t usec; ///< Timestamp (microseconds since UNIX epoch or microseconds since system boot)
	int32_t lat; ///< Latitude in 1E7 degrees
	int32_t lon; ///< Longitude in 1E7 degrees
	int32_t alt; ///< Altitude in 1E3 meters (millimeters)
	float eph; ///< GPS HDOP
	float epv; ///< GPS VDOP
	float v; ///< GPS ground speed (m/s)
	float hdg; ///< Compass heading in degrees, 0..360 degrees
	uint8_t fix_type; ///< 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
} mavlink_gps_raw_int_t;


/**
 * @brief Pack a gps_raw_int message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
 * @param lat Latitude in 1E7 degrees
 * @param lon Longitude in 1E7 degrees
 * @param alt Altitude in 1E3 meters (millimeters)
 * @param eph GPS HDOP
 * @param epv GPS VDOP
 * @param v GPS ground speed (m/s)
 * @param hdg Compass heading in degrees, 0..360 degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_raw_int_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint64_t usec, uint8_t fix_type, int32_t lat, int32_t lon, int32_t alt, float eph, float epv, float v, float hdg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_GPS_RAW_INT;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch or microseconds since system boot)
	p->lat = lat; // int32_t:Latitude in 1E7 degrees
	p->lon = lon; // int32_t:Longitude in 1E7 degrees
	p->alt = alt; // int32_t:Altitude in 1E3 meters (millimeters)
	p->eph = eph; // float:GPS HDOP
	p->epv = epv; // float:GPS VDOP
	p->v = v; // float:GPS ground speed (m/s)
	p->hdg = hdg; // float:Compass heading in degrees, 0..360 degrees
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_GPS_RAW_INT_LEN);
}

/**
 * @brief Pack a gps_raw_int message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
 * @param lat Latitude in 1E7 degrees
 * @param lon Longitude in 1E7 degrees
 * @param alt Altitude in 1E3 meters (millimeters)
 * @param eph GPS HDOP
 * @param epv GPS VDOP
 * @param v GPS ground speed (m/s)
 * @param hdg Compass heading in degrees, 0..360 degrees
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_raw_int_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint64_t usec, uint8_t fix_type, int32_t lat, int32_t lon, int32_t alt, float eph, float epv, float v, float hdg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_GPS_RAW_INT;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch or microseconds since system boot)
	p->lat = lat; // int32_t:Latitude in 1E7 degrees
	p->lon = lon; // int32_t:Longitude in 1E7 degrees
	p->alt = alt; // int32_t:Altitude in 1E3 meters (millimeters)
	p->eph = eph; // float:GPS HDOP
	p->epv = epv; // float:GPS VDOP
	p->v = v; // float:GPS ground speed (m/s)
	p->hdg = hdg; // float:Compass heading in degrees, 0..360 degrees
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_GPS_RAW_INT_LEN);
}

/**
 * @brief Encode a gps_raw_int struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps_raw_int C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_raw_int_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_raw_int_t* gps_raw_int)
{
	return mavlink_msg_gps_raw_int_pack(system_id, component_id, msg, gps_raw_int->usec, gps_raw_int->fix_type, gps_raw_int->lat, gps_raw_int->lon, gps_raw_int->alt, gps_raw_int->eph, gps_raw_int->epv, gps_raw_int->v, gps_raw_int->hdg);
}

/**
 * @brief Send a gps_raw_int message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
 * @param lat Latitude in 1E7 degrees
 * @param lon Longitude in 1E7 degrees
 * @param alt Altitude in 1E3 meters (millimeters)
 * @param eph GPS HDOP
 * @param epv GPS VDOP
 * @param v GPS ground speed (m/s)
 * @param hdg Compass heading in degrees, 0..360 degrees
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_gps_raw_int_send(mavlink_channel_t chan, uint64_t usec, uint8_t fix_type, int32_t lat, int32_t lon, int32_t alt, float eph, float epv, float v, float hdg)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg.payload[0];

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch or microseconds since system boot)
	p->lat = lat; // int32_t:Latitude in 1E7 degrees
	p->lon = lon; // int32_t:Longitude in 1E7 degrees
	p->alt = alt; // int32_t:Altitude in 1E3 meters (millimeters)
	p->eph = eph; // float:GPS HDOP
	p->epv = epv; // float:GPS VDOP
	p->v = v; // float:GPS ground speed (m/s)
	p->hdg = hdg; // float:Compass heading in degrees, 0..360 degrees
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_GPS_RAW_INT_LEN;
	msg.msgid = MAVLINK_MSG_ID_GPS_RAW_INT;
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
static inline void mavlink_msg_gps_raw_int_send(mavlink_channel_t chan, uint64_t usec, uint8_t fix_type, int32_t lat, int32_t lon, int32_t alt, float eph, float epv, float v, float hdg)
{
	mavlink_header_t hdr;
	mavlink_gps_raw_int_t payload;
	uint16_t checksum;
	mavlink_gps_raw_int_t *p = &payload;

	p->usec = usec; // uint64_t:Timestamp (microseconds since UNIX epoch or microseconds since system boot)
	p->lat = lat; // int32_t:Latitude in 1E7 degrees
	p->lon = lon; // int32_t:Longitude in 1E7 degrees
	p->alt = alt; // int32_t:Altitude in 1E3 meters (millimeters)
	p->eph = eph; // float:GPS HDOP
	p->epv = epv; // float:GPS VDOP
	p->v = v; // float:GPS ground speed (m/s)
	p->hdg = hdg; // float:Compass heading in degrees, 0..360 degrees
	p->fix_type = fix_type; // uint8_t:0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_GPS_RAW_INT_LEN;
	hdr.msgid = MAVLINK_MSG_ID_GPS_RAW_INT;
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
// MESSAGE GPS_RAW_INT UNPACKING

/**
 * @brief Get field usec from gps_raw_int message
 *
 * @return Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 */
static inline uint64_t mavlink_msg_gps_raw_int_get_usec(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (uint64_t)(p->usec);
}

/**
 * @brief Get field fix_type from gps_raw_int message
 *
 * @return 0-1: no fix, 2: 2D fix, 3: 3D fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
 */
static inline uint8_t mavlink_msg_gps_raw_int_get_fix_type(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (uint8_t)(p->fix_type);
}

/**
 * @brief Get field lat from gps_raw_int message
 *
 * @return Latitude in 1E7 degrees
 */
static inline int32_t mavlink_msg_gps_raw_int_get_lat(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (int32_t)(p->lat);
}

/**
 * @brief Get field lon from gps_raw_int message
 *
 * @return Longitude in 1E7 degrees
 */
static inline int32_t mavlink_msg_gps_raw_int_get_lon(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (int32_t)(p->lon);
}

/**
 * @brief Get field alt from gps_raw_int message
 *
 * @return Altitude in 1E3 meters (millimeters)
 */
static inline int32_t mavlink_msg_gps_raw_int_get_alt(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (int32_t)(p->alt);
}

/**
 * @brief Get field eph from gps_raw_int message
 *
 * @return GPS HDOP
 */
static inline float mavlink_msg_gps_raw_int_get_eph(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (float)(p->eph);
}

/**
 * @brief Get field epv from gps_raw_int message
 *
 * @return GPS VDOP
 */
static inline float mavlink_msg_gps_raw_int_get_epv(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (float)(p->epv);
}

/**
 * @brief Get field v from gps_raw_int message
 *
 * @return GPS ground speed (m/s)
 */
static inline float mavlink_msg_gps_raw_int_get_v(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (float)(p->v);
}

/**
 * @brief Get field hdg from gps_raw_int message
 *
 * @return Compass heading in degrees, 0..360 degrees
 */
static inline float mavlink_msg_gps_raw_int_get_hdg(const mavlink_message_t* msg)
{
	mavlink_gps_raw_int_t *p = (mavlink_gps_raw_int_t *)&msg->payload[0];
	return (float)(p->hdg);
}

/**
 * @brief Decode a gps_raw_int message into a struct
 *
 * @param msg The message to decode
 * @param gps_raw_int C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_raw_int_decode(const mavlink_message_t* msg, mavlink_gps_raw_int_t* gps_raw_int)
{
	memcpy( gps_raw_int, msg->payload, sizeof(mavlink_gps_raw_int_t));
}
