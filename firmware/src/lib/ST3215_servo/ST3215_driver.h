#ifndef ST3215_DRIVER_H
#define ST3215_DRIVER_H

#include "ST3215_protocol.h"
#include <Arduino.h>
#include "driver/uart.h"


#define SERIAL_BAUD_RATE        1000000
#define SERIAL_BAUD_RATE_DEBUG  115200
#define RX 18
#define TX 17

enum class ST3215_Mode : uint8_t
{
    POSITION    = 0x00,
    SPEED       = 0x01,
    PWM         = 0x02,
    STEP        = 0x03,
};

class ST3215_driver
{
public:
    ST3215_driver(HardwareSerial &serial);

    // --- Misc ---
    bool ping(uint8_t id);
    bool change_id(uint8_t old_id, uint8_t new_id);

    // --- Torque ---
    bool set_torque(uint8_t id, bool enable);
    bool set_torque_limit(uint8_t id, uint16_t limit);

    // --- Angle ---
    bool set_angle(uint8_t id, uint16_t angle);
    bool read_angle(uint8_t id, uint16_t *angle);
    bool hardware_zero_calibration(uint8_t id, uint16_t angle);

    // --- Speed ---
    bool set_speed(uint8_t id, uint16_t step_speed);
    bool read_speed(uint8_t id, uint16_t *step_speed);

    // --- Acceleration ---
    bool set_acceleration(uint8_t id, uint8_t acceleration);

    // --- Synchronized multi-servo ---
    bool set_angle_sync(uint8_t *ids, uint16_t *angles, uint8_t num_servos);
    bool set_speed_sync(uint8_t *ids, uint16_t *speeds, uint8_t num_servos);
    bool set_angle_speed_sync(uint8_t *ids, uint16_t *angles, uint16_t *speeds, uint8_t num_servos);

    // --- Status & Safety ---
    bool read_temperature(uint8_t id, uint8_t *temperature);
    bool read_voltage(uint8_t id, uint8_t *voltage);
    bool read_current(uint8_t id, uint16_t *current);
    bool read_load(uint8_t id, uint16_t *load);
    bool read_status(uint8_t id, uint8_t *status);
    bool is_moving(uint8_t id, bool *moving);

    // --- Bulk reads ---
    bool read_all_angles(uint8_t *ids, uint16_t *angles, uint8_t num_servos);
    bool read_all_status(uint8_t *ids, uint8_t *statuses, uint8_t num_servos);

    // --- Operation mode ---
    bool set_operation_mode(uint8_t id, ST3215_Mode mode);

protected:
    HardwareSerial &_serial;
    ST3215_protocol protocol;

private:
    // helpers
    bool eeprom_unlock(uint8_t id);
    bool eeprom_lock(uint8_t id);
};

#endif // ST3215_DRIVER_H