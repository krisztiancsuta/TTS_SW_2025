#include "MAS_CAN.h"


CAN_Message message;
static uint8_t heartbeat_counter = 0; // Heartbeat counter

bool can_send(CAN_Message *message, uint8_t bufferIndex)
{
    DL_MCAN_TxBufElement txElement = {
        .id = (message->id << 18),
        .rtr = 0U, // Data frame
        .xtd = message->extended ? 1U : 0U,
        .esi = 0U, // Error state indicator
        .dlc = message->length,
        .brs = 0U,  // Bit rate switching disabled
        .fdf = 0U,  // Classic CAN frame
        .efc = 1U,  // Event FIFO control
        .mm = 0xAAU // Message marker
    };

    // Copy message data
    for (uint8_t i = 0; i < message->length; i++)
    {
        txElement.data[i] = message->data[i];
    }

    // Wait for normal mode
    while (DL_MCAN_OPERATION_MODE_NORMAL != DL_MCAN_getOpMode(MCAN0_INST))
        ;

    // Write to message RAM
    DL_MCAN_writeMsgRam(MCAN0_INST, DL_MCAN_MEM_TYPE_BUF, bufferIndex, &txElement);

    // Request transmission
    return (DL_MCAN_TXBufAddReq(MCAN0_INST, bufferIndex) == 0);
}

bool CAN_transfer(float max_temp)
{
    // Convert float to bytes for CAN transmission
    union {
        float f;
        uint8_t bytes[4];
    } temp_union;
    
    temp_union.f = max_temp;

    message.id = CAN_MESSAGE_ID;
    message.extended = false;
    message.length = CAN_DATA_LENGTH;

    // Send temperature as 4 bytes
    message.data[0] = temp_union.bytes[0];
    message.data[1] = temp_union.bytes[1];
    message.data[2] = temp_union.bytes[2];
    message.data[3] = temp_union.bytes[3];
    
    // Add heartbeat counter in 5th byte
    message.data[4] = heartbeat_counter++;

    return can_send(&message, 0);
}