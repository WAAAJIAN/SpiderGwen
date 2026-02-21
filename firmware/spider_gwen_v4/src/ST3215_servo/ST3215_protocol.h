/**
 * @file ST3215_protocol.h
 * @author  Lim Wei Jian
 * @brief   This file contains the declaration of the ST3215_protocol class, 
 *          which provides an interface for controlling the ST3215 servo motor protocol.
 * @version 1.0
 * @date    2026-02-16
 */

#ifndef ST3215_PROTOCOL_H
#define ST3215_PROTOCOL_H

#include <stdint.h>
#include <cstdio>
#include <Arduino.h>

/**
 * EEPROM Memory addresses for the ST3215 servomotor, needed to construct command packets for reading and writing
 */
#define ST3215_REG_ID 0x05
#define ST3215_REG_BAUDRATE 0x06
#define ST3215_REG_POS_CORRECTION 0x1C

/**
 * SRAM Memory addresses for the ST3215 servomotor, needed to construct command packets for reading and writing
 */
#define ST3215_REG_TARGET_LOCATION 0x2A
#define ST3215_REG_RUNNING_SPEED 0x2E
#define ST3215_REG_LOCK_PROTECTION 0x37
#define ST3215_REG_CURRENT_LOCATION 0x38
#define ST3215_REG_CURRENT_SPEED 0x3A
#define ST3215_REG_CURRENT_LOAD 0x3C
#define ST3215_REG_CURRENT_VOLTAGE 0x3E
#define ST3215_REG_CURRENT_TEMPERATURE 0x3F
#define ST3215_REG_ASYNC_WRITE_FLAG 0x40

/**
 * HEADER byte for the ST3215 protocol, used to indicate the start of a command packet.
 * Requires 2 consecutive HEADER bytes to signify the beginning of a valid command packet.
 */
#define ST3215_PROTOCOL_HEADER 0xFF

/**
 * Instruction bytes for the ST3215 protocol, defining the various commands that can be sent to the servo motor.
 * These instructions include:
 * - ST3215_PROTOCOL_WRITE: Command to write data to a register in the servo motor.
 * - ST3215_PROTOCOL_READ: Command to read data from a register in the servo motor.
 * - ST3215_PROTOCOL_SYNC_WRITE: Command to perform a synchronous write operation to multiple servo motors.
 */

#define ST3215_PROTOCOL_PING 0x01
#define ST3215_PROTOCOL_READ 0x02
#define ST3215_PROTOCOL_WRITE 0x03
#define ST3215_PROTOCOL_REGWRITE 0x04
#define ST3215_PROTOCOL_ACTION 0x05
#define ST3215_PROTOCOL_RESET 0x06
#define ST3215_PROTOCOL_SYNC_WRITE 0x83


class ST3215_protocol {
    public:
        /**
         * @brief Constructs an instance of the ST3215_protocol class, which provides methods for communicating with ST3215 servo motors using the defined protocol.
         */
        ST3215_protocol(HardwareSerial &serial);

        /**
         * @brief general write function for ST3215 protocol, which sends a command packet to the servo motor with the specified ID, register address, and data.
         * @param id The ID of the servo motor to write to.
         * @param data_length the length of the data, does not include instruction byte and checksum byte.
         * @param instruction the instruction byte to be sent, use defined instruction bytes such as ST3215_PROTOCOL_WRITE, ST3215_PROTOCOL_READ, etc.
         * @param data the data bytes to be sent, typically also known as the parameters of the byte stream. Can be set to nullptr if no data is required to be sent.
         * @return true if the write command is successful, false otherwise.
         */
        bool ST3215_write(uint8_t id, uint8_t data_length, uint8_t instruction,  uint8_t *data);

        /**
         * @brief general read function for ST3215 protocol, which sends a command packet to the servo motor with 
         * the specified ID and register address, and reads the response data from the servo motor.
         * @param id The ID of the servo motor to read from.
         * @param out A pointer to a byte array where the read data will be stored.
         * @return true if the read command is successful and data is stored in the provided array, false otherwise.
         */
        bool ST3215_receive(uint8_t id, uint8_t *out);

        /**
         * @brief Calculates the checksum for a given command packet according to the ST3215 protocol specifications. 
         * The checksum is typically calculated by summing all bytes in the packet (excluding the header) and taking the result modulo 256.
         * @param packet A pointer to the byte array containing the command packet for which the checksum is to be calculated.
         * @param checksum The output parameter where the calculated checksum will be stored.
         * @return true if the checksum is valid, false otherwise.
         */
        bool checksum(uint8_t id, uint8_t length, uint8_t *data, uint8_t *checksum_out);

    protected:
        HardwareSerial &_serial; // Reference to the HardwareSerial object used for communication with the servo motors


} ;

#endif // ST3215_PROTOCOL_H