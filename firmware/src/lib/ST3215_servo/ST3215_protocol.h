#ifndef ST3215_PROTOCOL_H
#define ST3215_PROTOCOL_H

#include <Arduino.h>
#include "ST3215_registers.h"
#include "ST3215_cmd.h"

class ST3215_protocol
{
public:
    ST3215_protocol(HardwareSerial &serial);

    bool ping(uint8_t id);
    bool read(uint8_t id, ST3215_REG reg, uint8_t read_length, uint8_t *out);
    bool write(uint8_t id, ST3215_REG reg, uint8_t *data, uint8_t data_length);
    bool reg_write(uint8_t id, ST3215_REG reg, uint8_t *data, uint8_t data_length);
    bool action(uint8_t id);
    bool sync_write(ST3215_REG reg, uint8_t data_length_per_servo, uint8_t *ids, uint8_t *data, uint8_t num_servos);

private:
    HardwareSerial &_serial;
    static constexpr uint8_t HEADER = 0xFF;
    static constexpr uint8_t BROADCAST_ID = 0xFE;

    bool send_packet(uint8_t id, ST3215_CMD cmd, uint8_t *payload, uint8_t payload_length);
    bool receive_packet(uint8_t id, uint8_t *out, uint8_t out_length);
    bool checksum(uint8_t id, uint8_t length, uint8_t *data, uint8_t *checksum_out);
};

#endif