// MESSAGE SLUGS_ACTION PACKING

#define MAVLINK_MSG_ID_SLUGS_ACTION 183
#define MAVLINK_MSG_183_LEN 4

typedef struct __mavlink_slugs_action_t 
{
	uint8_t target; ///< The system reporting the action
	uint8_t actionId; ///< Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
	uint16_t actionVal; ///< Value associated with the action
} mavlink_slugs_action_t;

//#if sizeof(mavlink_slugs_action_t) != 4 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a slugs_action message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target The system reporting the action
 * @param actionId Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
 * @param actionVal Value associated with the action
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_slugs_action_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target, uint8_t actionId, uint16_t actionVal)
{
	mavlink_slugs_action_t *p = (mavlink_slugs_action_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SLUGS_ACTION;

	p->target = target; // uint8_t:The system reporting the action
	p->actionId = actionId; // uint8_t:Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
	p->actionVal = actionVal; // uint16_t:Value associated with the action

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_slugs_action_t));
}

/**
 * @brief Pack a slugs_action message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target The system reporting the action
 * @param actionId Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
 * @param actionVal Value associated with the action
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_slugs_action_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target, uint8_t actionId, uint16_t actionVal)
{
	mavlink_slugs_action_t *p = (mavlink_slugs_action_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_SLUGS_ACTION;

	p->target = target; // uint8_t:The system reporting the action
	p->actionId = actionId; // uint8_t:Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
	p->actionVal = actionVal; // uint16_t:Value associated with the action

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_slugs_action_t));
}

/**
 * @brief Encode a slugs_action struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param slugs_action C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_slugs_action_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_slugs_action_t* slugs_action)
{
	return mavlink_msg_slugs_action_pack(system_id, component_id, msg, slugs_action->target, slugs_action->actionId, slugs_action->actionVal);
}

/**
 * @brief Send a slugs_action message
 * @param chan MAVLink channel to send the message
 *
 * @param target The system reporting the action
 * @param actionId Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
 * @param actionVal Value associated with the action
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_slugs_action_send(mavlink_channel_t chan, uint8_t target, uint8_t actionId, uint16_t actionVal)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_slugs_action_t *p = (mavlink_slugs_action_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_SLUGS_ACTION;
	msg.len = sizeof(mavlink_slugs_action_t);
	p->target = target; // uint8_t:The system reporting the action
	p->actionId = actionId; // uint8_t:Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
	p->actionVal = actionVal; // uint16_t:Value associated with the action

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
// MESSAGE SLUGS_ACTION UNPACKING

/**
 * @brief Get field target from slugs_action message
 *
 * @return The system reporting the action
 */
static inline uint8_t mavlink_msg_slugs_action_get_target(const mavlink_message_t* msg)
{
	mavlink_slugs_action_t *p = (mavlink_slugs_action_t *)&msg->payload[0];
	return (uint8_t)(p->target);
}

/**
 * @brief Get field actionId from slugs_action message
 *
 * @return Action ID. See apDefinitions.h in the SLUGS /clib directory for the ID names
 */
static inline uint8_t mavlink_msg_slugs_action_get_actionId(const mavlink_message_t* msg)
{
	mavlink_slugs_action_t *p = (mavlink_slugs_action_t *)&msg->payload[0];
	return (uint8_t)(p->actionId);
}

/**
 * @brief Get field actionVal from slugs_action message
 *
 * @return Value associated with the action
 */
static inline uint16_t mavlink_msg_slugs_action_get_actionVal(const mavlink_message_t* msg)
{
	mavlink_slugs_action_t *p = (mavlink_slugs_action_t *)&msg->payload[0];
	return (uint16_t)(p->actionVal);
}

/**
 * @brief Decode a slugs_action message into a struct
 *
 * @param msg The message to decode
 * @param slugs_action C-struct to decode the message contents into
 */
static inline void mavlink_msg_slugs_action_decode(const mavlink_message_t* msg, mavlink_slugs_action_t* slugs_action)
{
	memcpy( slugs_action, msg->payload, sizeof(mavlink_slugs_action_t));
}
