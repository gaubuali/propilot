#ifndef  _MAVLINK_PROTOCOL_H_
#define  _MAVLINK_PROTOCOL_H_

#include "string.h"
#include "inttypes.h"
#include "mavlink_types.h"

extern inline void crc_accumulate(uint8_t data, uint16_t *crcAccum);
extern inline void crc_init(uint16_t* crcAccum);
extern inline uint16_t crc_calculate(uint8_t* pBuffer, int length);
extern inline uint16_t crc_calculate_msg(mavlink_message_t* pMSG, int length);

extern void mavlink_parse_state_initialize(mavlink_status_t* initStatus);
extern inline mavlink_status_t* mavlink_get_channel_status(uint8_t chan);
extern inline uint16_t mavlink_finalize_message(mavlink_message_t* msg, uint8_t system_id, uint8_t component_id, uint16_t length);
extern inline uint16_t mavlink_finalize_message_chan(mavlink_message_t* msg, uint8_t system_id, uint8_t component_id, uint8_t chan, uint16_t length);
extern inline uint16_t mavlink_msg_to_send_buffer(uint8_t* buffer, const mavlink_message_t* msg);
extern inline uint16_t mavlink_msg_get_send_buffer_length(const mavlink_message_t* msg);
extern inline void mavlink_start_checksum(mavlink_message_t* msg);
extern inline void mavlink_update_checksum(mavlink_message_t* msg, uint8_t c);
extern inline uint8_t mavlink_parse_char(uint8_t chan, uint8_t c, mavlink_message_t* r_message, mavlink_status_t* r_mavlink_status);
extern inline void mavlink_send_uart(mavlink_channel_t chan, mavlink_message_t* msg);

#endif /* _MAVLINK_PROTOCOL_H_ */
