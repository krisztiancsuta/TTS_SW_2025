#ifndef MAS_CAN_H
#define MAS_CAN_H

#include <stdint.h>
#include <ti/driverlib/dl_mcan.h>
#include "ti_msp_dl_config.h"

#define CAN_MESSAGE_ID 0x611
#define CAN_DATA_LENGTH 5  // 4 bytes for float temperature + 1 byte for heartbeat

// CAN message structure
typedef struct
{
    uint32_t id;     // CAN message ID
    bool extended;   // Extended ID flag
    uint8_t length;  // Data length (0-8 bytes)
    uint8_t data[8]; // Data payload
} CAN_Message;

bool CAN_transfer(float max_temp);
bool can_send(CAN_Message *message, uint8_t bufferIndex);

#endif // MAS_CAN_H
