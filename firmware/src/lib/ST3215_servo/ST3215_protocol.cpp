#include "ST3215_protocol.h"

ST3215_protocol::ST3215_protocol(HardwareSerial &serial) : _serial(serial) {}

// ============================================================
// Public API
// ============================================================

bool ST3215_protocol::ping(uint8_t id)
{
    if (!send_packet(id, ST3215_CMD::PING, nullptr, 0))
        return false;

    return receive_packet(id, nullptr, 0);
}

bool ST3215_protocol::read(uint8_t id, ST3215_REG reg, uint8_t read_length, uint8_t *out)
{
    uint8_t payload[2] = {
        static_cast<uint8_t>(reg),
        read_length
    };

    if (!send_packet(id, ST3215_CMD::READ, payload, 2))
        return false;

    return receive_packet(id, out, read_length);
}

bool ST3215_protocol::write(uint8_t id, ST3215_REG reg, uint8_t *data, uint8_t data_length)
{
    // payload = [reg_address, data...]
    uint8_t payload[1 + data_length];
    payload[0] = static_cast<uint8_t>(reg);
    for (uint8_t i = 0; i < data_length; i++)
        payload[1 + i] = data[i];

    if (!send_packet(id, ST3215_CMD::WRITE, payload, 1 + data_length))
        return false;

    return receive_packet(id, nullptr, 0);
}

bool ST3215_protocol::reg_write(uint8_t id, ST3215_REG reg, uint8_t *data, uint8_t data_length)
{
    uint8_t payload[1 + data_length];
    payload[0] = static_cast<uint8_t>(reg);
    for (uint8_t i = 0; i < data_length; i++)
        payload[1 + i] = data[i];

    if (!send_packet(id, ST3215_CMD::REG_WRITE, payload, 1 + data_length))
        return false;

    return receive_packet(id, nullptr, 0);
}

bool ST3215_protocol::action(uint8_t id)
{
    if (!send_packet(id, ST3215_CMD::ACTION, nullptr, 0))
        return false;

    return receive_packet(id, nullptr, 0);
}

bool ST3215_protocol::sync_write(ST3215_REG reg, uint8_t data_length_per_servo, uint8_t *ids, uint8_t *data, uint8_t num_servos)
{
    // payload = [reg_address, data_length_per_servo, (id + data) * N]
    uint8_t payload_length = 2 + num_servos * (1 + data_length_per_servo);
    uint8_t payload[payload_length];

    payload[0] = static_cast<uint8_t>(reg);
    payload[1] = data_length_per_servo;

    for (uint8_t i = 0; i < num_servos; i++)
    {
        uint8_t offset = 2 + i * (1 + data_length_per_servo);
        payload[offset] = ids[i];
        for (uint8_t j = 0; j < data_length_per_servo; j++)
            payload[offset + 1 + j] = data[i * data_length_per_servo + j];
    }

    // sync_write uses broadcast ID, no return packet
    return send_packet(BROADCAST_ID, ST3215_CMD::SYNC_WRITE, payload, payload_length);
}

// ============================================================
// Private
// ============================================================

bool ST3215_protocol::send_packet(uint8_t id, ST3215_CMD cmd, uint8_t *payload, uint8_t payload_length)
{
    // packet = [HEADER, HEADER, ID, LENGTH, CMD, payload..., CHECKSUM]
    // LENGTH = payload_length + 1 (cmd byte) + 1 (checksum byte)
    uint8_t length = payload_length + 2;
    uint8_t packet_size = 4 + length; // 2 headers + id + length field + rest
    uint8_t packet[packet_size];

    packet[0] = HEADER;
    packet[1] = HEADER;
    packet[2] = id;
    packet[3] = length;
    packet[4] = static_cast<uint8_t>(cmd);

    for (uint8_t i = 0; i < payload_length; i++)
    {
        packet[5 + i] = payload[i];
    }

    uint8_t checksum_value;
    if (!checksum(id, length, packet + 4, &checksum_value))
        return false;

    packet[5 + payload_length] = checksum_value;

    return _serial.write(packet, packet_size) == packet_size;
}

bool ST3215_protocol::receive_packet(uint8_t id, uint8_t *out, uint8_t out_length)
{
    // Read and validate header
    uint8_t header[2];
    if (_serial.readBytes(header, 2) != 2)
        return false;
    if (header[0] != HEADER || header[1] != HEADER)
        return false;

    // Read and validate ID
    uint8_t packet_id;
    if (_serial.readBytes(&packet_id, 1) != 1)
        return false;
    if (packet_id != id)
        return false;

    // Read length
    uint8_t data_length;
    if (_serial.readBytes(&data_length, 1) != 1)
        return false;
    if (data_length < 2)  // must at least have error byte + checksum
        return false;

    // Read payload — [error_byte, data..., checksum]
    uint8_t data[data_length];
    for (uint8_t i = 0; i < data_length; i++)
    {
        int b = _serial.read();
        if (b < 0)
            return false;
        data[i] = (uint8_t)b;
    }

    // Validate error byte
    if (data[0] != 0x00)
        return false;

    // Validate checksum
    uint8_t calc_checksum;
    if (!checksum(packet_id, data_length, data, &calc_checksum))
        return false;
    if (calc_checksum != data[data_length - 1])
        return false;

    // Copy payload to out if provided — skipping error byte and checksum
    if (out != nullptr && out_length > 0)
    {
        uint8_t payload_length = data_length - 2; // exclude error byte and checksum
        uint8_t copy_length = (out_length < payload_length) ? out_length : payload_length;
        for (uint8_t i = 0; i < copy_length; i++)
            out[i] = data[1 + i];
    }

    return true;
}

bool ST3215_protocol::checksum(uint8_t id, uint8_t length, uint8_t *data, uint8_t *checksum_out)
{
    if (!data || !checksum_out)
        return false;

    uint16_t sum = id + length;
    for (uint8_t i = 0; i < length - 1; i++) // exclude checksum byte
        sum += data[i];

    *checksum_out = ~(sum & 0xFF);
    return true;
}