/**
 * @file ST3215_protocol.cpp
 * @brief Implementation of the ST3215_protocol class for communicating with ST3215 servo motors.
 * 
 * Note: The actual communication with the servo motors (e.g., sending packets over a serial interface) is not implemented 
 * in this file and should be handled separately.
 * @author Lim Wei Jian
 * @date 2026-02-16
 * @version 1.0
 * License: This is an open-source implementation, and you are free to use, modify, and distribute it as needed. 
 * Please provide appropriate attribution if you use this code in your projects.
 */

#ifndef ST3215_PROTOCOL_CPP
#define ST3215_PROTOCOL_CPP

#include "ST3215_protocol.h"

ST3215_protocol::ST3215_protocol(HardwareSerial &serial) : _serial(serial) {}

bool ST3215_protocol::ST3215_write(uint8_t id, uint8_t data_length, uint8_t instruction,  uint8_t *data) 
{
    size_t packet_size = 6 + data_length;
    uint8_t packet[packet_size];
    packet[0] = ST3215_PROTOCOL_HEADER;
    packet[1] = ST3215_PROTOCOL_HEADER;
    packet[2] = id;
    packet[3] = data_length+2; // data length + instruction byte + checksum byte
    packet[4] = instruction;

    if (!(data == nullptr))
    {
        for (uint8_t i = 0; i < data_length; i++) 
        {
            packet[5 + i] = data[i]; // Copy data into the packet
        }
    }

    uint8_t checksum_value;
    if (!checksum(id, data_length+2, packet+4, &checksum_value))
    {
        return false; // Checksum calculation failed
    }

    packet[5 + data_length] = checksum_value;

    if(_serial.write(packet, packet_size) != packet_size) 
    {
        return false; // Failed to send the complete packet
    }
    _serial.flush(); // Ensure the packet is sent before returning

    // debugging: print all sent bytes
    Serial.print("Sent packet: ");
    Serial.print("ID: ");
    Serial.print(id);
    Serial.print(", Length: ");
    Serial.print(data_length + 2);
    Serial.print(", Instruction: ");
    Serial.print(instruction, HEX);
    if (data_length > 0) {
        Serial.print(", Data: ");
        for (uint8_t i = 0; i < data_length; i++) {
            Serial.print(data[i], HEX);
            Serial.print(" ");
        }
    }
    Serial.print(", Checksum: ");
    Serial.print(checksum_value, HEX);
    Serial.println();
    // End of debugging

    uint8_t clear[packet_size];
    _serial.readBytes(clear, packet_size);
    return true; // Placeholder return value
}

bool ST3215_protocol::ST3215_receive(uint8_t id, uint8_t *out) 
{
    uint8_t header[2];
    if (_serial.readBytes(header, 2) != 2)
    {
        return false;
    }

    if (header[0] != ST3215_PROTOCOL_HEADER || header[1] != ST3215_PROTOCOL_HEADER)
    {
        return false;
    }

    uint8_t packet_id;
    if (_serial.readBytes(&packet_id, 1) != 1)
    {
        return false;
    }

    if (packet_id != id)
    {
        return false;
    }

    uint8_t data_length;
    if (_serial.readBytes(&data_length, 1) != 1)
    {
        return false;
    }

    if (data_length < 2)   // must at least contain instruction + checksum
    {
        return false;
    }

    // data will contain working byte + payload + checksum
    // if working byte is 0x00, means instruction executed successfully, we can return the other bytes as payload.
    uint8_t data[data_length];
    for (uint8_t i = 0; i < data_length; i++) {
        int b = _serial.read();

        if (b < 0) 
        {
            return false;
        }
        data[i] = (uint8_t)b;
    }

    if (data[0] != 0x00) // check if working byte is 0x00, meaning executed successfully
    {
        return false;
    }

    uint8_t calc_checksum;
    if (!checksum(packet_id, data_length, data, &calc_checksum))
    {
        return false;
    }
    uint8_t received_checksum = data[data_length - 1];

    if (calc_checksum != received_checksum)
    {
        return false;
    }

    // copy payload without checksum
    for (uint8_t i = 1; i < data_length - 1; i++)
    {
        out[i - 1] = data[i];
    }

    return true;
}

bool ST3215_protocol::checksum(uint8_t id, uint8_t length, uint8_t *data, uint8_t *checksum_out)
{
    if (!data || !checksum_out)
    {
        return false; // Invalid input parameters
    }

    uint16_t sum = 0;

    sum += id;
    sum += length;

    for (uint8_t i = 0; i < length - 1; i++)   // exclude checksum byte
        sum += data[i];

    *checksum_out = ~(sum & 0xFF);
    return true;
}

#endif // ST3215_PROTOCOL_CPP