#ifndef ST3215_CMD_H
#define ST3215_CMD_H

enum class ST3215_CMD : uint8_t
{
    PING        = 0x01,  // Check if a servo is present and responding
    READ        = 0x02,  // Read data from a register
    WRITE       = 0x03,  // Write data to a register immediately
    REG_WRITE   = 0x04,  // Buffer a write, executed on ACTION
    ACTION      = 0x05,  // Trigger all buffered REG_WRITE commands
    RESET       = 0x06,  // Reset servo to factory defaults
    SYNC_WRITE  = 0x83,  // Write to multiple servos in one packet
};

#endif