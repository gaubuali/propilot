// MESSAGE REQUEST_DYNAMIC_GYRO_CALIBRATION PACKING

#define MAVLINK_MSG_ID_REQUEST_DYNAMIC_GYRO_CALIBRATION 67

typedef struct __mavlink_request_dynamic_gyro_calibration_t 
{
	uint8_t target_system; ///< The system which should auto-calibrate
	uint8_t target_component; ///< The system component which should auto-calibrate
	float mode; ///< The current ground-truth rpm
	uint8_t axis; ///< The axis to calibrate: 0 roll, 1 pitch, 2 yaw
	uint16_t time; ///< The time to average over in ms

} mavlink_request_dynamic_gyro_calibration_t;



/**
 * @brief Pack a request_dynamic_gyro_calibration message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system The system which should auto-calibrate
 * @param target_component The system component which should auto-calibrate
 * @param mode The current ground-truth rpm
 * @param axis The axis to calibrate: 0 roll, 1 pitch, 2 yaw
 * @param time The time to average over in ms
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_dynamic_gyro_calibration_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, float mode, uint8_t axis, uint16_t time)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_REQUEST_DYNAMIC_GYRO_CALIBRATION;

	p->target_system = target_system; // uint8_t:The system which should auto-calibrate
	p->target_component = target_component; // uint8_t:The system component which should auto-calibrate
	p->mode = mode; // float:The current ground-truth rpm
	p->axis = axis; // uint8_t:The axis to calibrate: 0 roll, 1 pitch, 2 yaw
	p->time = time; // uint16_t:The time to average over in ms

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_request_dynamic_gyro_calibration_t));
}

/**
 * @brief Pack a request_dynamic_gyro_calibration message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system The system which should auto-calibrate
 * @param target_component The system component which should auto-calibrate
 * @param mode The current ground-truth rpm
 * @param axis The axis to calibrate: 0 roll, 1 pitch, 2 yaw
 * @param time The time to average over in ms
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_dynamic_gyro_calibration_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, float mode, uint8_t axis, uint16_t time)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_REQUEST_DYNAMIC_GYRO_CALIBRATION;

	p->target_system = target_system; // uint8_t:The system which should auto-calibrate
	p->target_component = target_component; // uint8_t:The system component which should auto-calibrate
	p->mode = mode; // float:The current ground-truth rpm
	p->axis = axis; // uint8_t:The axis to calibrate: 0 roll, 1 pitch, 2 yaw
	p->time = time; // uint16_t:The time to average over in ms

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_request_dynamic_gyro_calibration_t));
}

/**
 * @brief Encode a request_dynamic_gyro_calibration struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param request_dynamic_gyro_calibration C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_request_dynamic_gyro_calibration_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_request_dynamic_gyro_calibration_t* request_dynamic_gyro_calibration)
{
	return mavlink_msg_request_dynamic_gyro_calibration_pack(system_id, component_id, msg, request_dynamic_gyro_calibration->target_system, request_dynamic_gyro_calibration->target_component, request_dynamic_gyro_calibration->mode, request_dynamic_gyro_calibration->axis, request_dynamic_gyro_calibration->time);
}

/**
 * @brief Send a request_dynamic_gyro_calibration message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system The system which should auto-calibrate
 * @param target_component The system component which should auto-calibrate
 * @param mode The current ground-truth rpm
 * @param axis The axis to calibrate: 0 roll, 1 pitch, 2 yaw
 * @param time The time to average over in ms
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_request_dynamic_gyro_calibration_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, float mode, uint8_t axis, uint16_t time)
{
	mavlink_message_t msg;
	mavlink_msg_request_dynamic_gyro_calibration_pack_chan(mavlink_system.sysid, mavlink_system.compid, chan, &msg, target_system, target_component, mode, axis, time);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE REQUEST_DYNAMIC_GYRO_CALIBRATION UNPACKING

/**
 * @brief Get field target_system from request_dynamic_gyro_calibration message
 *
 * @return The system which should auto-calibrate
 */
static inline uint8_t mavlink_msg_request_dynamic_gyro_calibration_get_target_system(const mavlink_message_t* msg)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from request_dynamic_gyro_calibration message
 *
 * @return The system component which should auto-calibrate
 */
static inline uint8_t mavlink_msg_request_dynamic_gyro_calibration_get_target_component(const mavlink_message_t* msg)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field mode from request_dynamic_gyro_calibration message
 *
 * @return The current ground-truth rpm
 */
static inline float mavlink_msg_request_dynamic_gyro_calibration_get_mode(const mavlink_message_t* msg)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	return (float)(p->mode);
}

/**
 * @brief Get field axis from request_dynamic_gyro_calibration message
 *
 * @return The axis to calibrate: 0 roll, 1 pitch, 2 yaw
 */
static inline uint8_t mavlink_msg_request_dynamic_gyro_calibration_get_axis(const mavlink_message_t* msg)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	return (uint8_t)(p->axis);
}

/**
 * @brief Get field time from request_dynamic_gyro_calibration message
 *
 * @return The time to average over in ms
 */
static inline uint16_t mavlink_msg_request_dynamic_gyro_calibration_get_time(const mavlink_message_t* msg)
{
	mavlink_request_dynamic_gyro_calibration_t *p = (mavlink_request_dynamic_gyro_calibration_t *)&msg->payload[0];
	return (uint16_t)(p->time);
}

/**
 * @brief Decode a request_dynamic_gyro_calibration message into a struct
 *
 * @param msg The message to decode
 * @param request_dynamic_gyro_calibration C-struct to decode the message contents into
 */
static inline void mavlink_msg_request_dynamic_gyro_calibration_decode(const mavlink_message_t* msg, mavlink_request_dynamic_gyro_calibration_t* request_dynamic_gyro_calibration)
{
	memcpy( request_dynamic_gyro_calibration, msg->payload, sizeof(mavlink_request_dynamic_gyro_calibration_t));
}
