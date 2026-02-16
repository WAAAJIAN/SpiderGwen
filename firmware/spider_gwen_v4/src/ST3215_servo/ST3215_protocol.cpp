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
    uint8_t packet[packet_size]; // Buffer for the command packet
    packet[0] = ST3215_PROTOCOL_HEADER; // Header byte
    packet[1] = ST3215_PROTOCOL_HEADER;
    packet[2] = id;
    packet[3] = data_length;
    packet[4] = instruction;
    for (uint8_t i = 0; i < data_length; ++i) 
    {
        packet[5 + i] = data[i]; // Copy data into the packet
    }

    uint8_t checksum_value;
    if (!checksum(packet, &checksum_value))
    {
        return false; // Checksum calculation failed
    }
    packet[5 + data_length] = checksum_value;

    if(_serial.write(packet, packet_size) != packet_size) 
    {
        return false; // Failed to send the complete packet
    }
    
    return true; // Placeholder return value
}

bool ST3215_protocol::ST3215_receive(uint8_t id, uint8_t *out) 
{
    uint8_t header_check[2];
    _serial.readBytes(header_check, 2);
    if (header_check[0] != ST3215_PROTOCOL_HEADER || header_check[1] != ST3215_PROTOCOL_HEADER) 
    {
        return false; // Invalid packet header
    }

    uint8_t packet_id;
    _serial.readBytes(&packet_id, 1);
    if (packet_id != id) 
    {
        return false; // ID mismatch
    }

    uint8_t data_length;
    _serial.readBytes(&data_length, 1);

    uint8_t data[data_length];
    for (size_t i = 0; i < data_length + 1; ++i) 
    {
        data[i] = _serial.read(); // Read data bytes and checksum
    }

    for (size_t i = 0; i < data_length; ++i) 
    {
        out[i] = data[i]; // Store received data in output variable
    }

    return true;
}

bool ST3215_protocol::checksum(uint8_t *packet, uint8_t *checksum) 
{
    // Implement checksum calculation according to the ST3215 protocol specifications
    // Return true if the checksum is valid, false otherwise
    if (!packet) 
    {
        return false;
    }

    if (packet[0] != ST3215_PROTOCOL_HEADER) 
    {
        if(packet[1] != ST3215_PROTOCOL_HEADER) 
        {
            return false; // Invalid packet header
        }
    }

    packet += 2;

    size_t buf = 0;
    for (size_t i = 0; i < sizeof(packet); ++i) 
    {
        // Calculate checksum (this is a placeholder implementation)
        buf += packet[i];
    }

    *checksum = ~(buf & 0xFF);
    return true;
}

#endif // ST3215_PROTOCOL_CPP