#ifndef ST3215_REGISTERS_H
#define ST3215_REGISTERS_H

#include <stdint.h>
/**
 * @brief Strongly-typed register addresses for the ST3215 servo.
 * Use with sync_write() to specify which registers to write to.
 */
enum class ST3215_REG : uint8_t
{
    // --- EEPROM: Firmware & Version (read-only) ---
    FIRMWARE_MAJOR_VER   = 0x00,
    FIRMWARE_SUB_VER     = 0x01,
    SERVO_MAIN_VER       = 0x03,
    SERVO_SUB_VER        = 0x04,

    // --- EEPROM: Communication ---
    ID                   = 0x05,
    BAUDRATE             = 0x06,
    RETURN_DELAY         = 0x07,
    RESPONSE_LEVEL       = 0x08,

    // --- EEPROM: Motion Limits ---
    MIN_ANGLE_LIMIT      = 0x09,
    MAX_ANGLE_LIMIT      = 0x0B,

    // --- EEPROM: Safety Limits ---
    MAX_TEMP_LIMIT       = 0x0D,
    MAX_VOLTAGE_LIMIT    = 0x0E,
    MIN_VOLTAGE_LIMIT    = 0x0F,

    // --- EEPROM: Torque ---
    MAX_TORQUE           = 0x10,
    MIN_STARTUP_FORCE    = 0x18,
    PROTECTIVE_TORQUE    = 0x22,
    OVERLOAD_TORQUE      = 0x24,

    // --- EEPROM: Special ---
    PHASE                = 0x12,

    // --- EEPROM: Protection ---
    UNLOAD_CONDITION     = 0x13,
    LED_ALARM_CONDITION  = 0x14,
    PROTECTION_TIME      = 0x23,
    PROTECTION_CURRENT   = 0x1C,
    OVERCURRENT_TIME     = 0x26,

    // --- EEPROM: PID ---
    P_COEFFICIENT        = 0x15,
    D_COEFFICIENT        = 0x16,
    I_COEFFICIENT        = 0x17,
    SPEED_LOOP_P         = 0x25,
    SPEED_LOOP_I         = 0x27,

    // --- EEPROM: Dead Zone ---
    CW_DEADZONE          = 0x1A,
    CCW_DEADZONE         = 0x1B,

    // --- EEPROM: Resolution & Correction ---
    ANGULAR_RESOLUTION   = 0x1E,
    POS_CORRECTION       = 0x1F,

    // --- EEPROM: Operation Mode ---
    OPERATION_MODE       = 0x21,

    // --- SRAM: Control ---
    TORQUE_SWITCH        = 0x28,
    ACCELERATION         = 0x29,
    TARGET_LOCATION      = 0x2A,
    RUNNING_TIME         = 0x2C,
    RUNNING_SPEED        = 0x2E,
    TORQUE_LIMIT         = 0x30,

    // --- SRAM: Lock ---
    LOCK_PROTECTION      = 0x37,

    // --- SRAM: Feedback (read-only) ---
    CURRENT_LOCATION     = 0x38,
    CURRENT_SPEED        = 0x3A,
    CURRENT_LOAD         = 0x3C,
    CURRENT_VOLTAGE      = 0x3E,
    CURRENT_TEMPERATURE  = 0x3F,
    ASYNC_WRITE_FLAG     = 0x40,
    SERVO_STATUS         = 0x41,
    MOBILE_SIGN          = 0x42,
    CURRENT_CURRENT      = 0x45,
};

#endif