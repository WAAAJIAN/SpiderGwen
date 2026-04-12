#include "ST3215_driver.h"

ST3215_driver::ST3215_driver(HardwareSerial &serial, uint8_t dir_pin) : _serial(serial), protocol(serial, dir_pin)
{
    serial.begin(SERIAL_BAUD_RATE, SERIAL_8N1, RX, TX);
    uart_set_mode(UART_NUM_1, UART_MODE_RS485_HALF_DUPLEX);
}

// ============================================================
// Private helpers
// ============================================================

bool ST3215_driver::eeprom_unlock(uint8_t id)
{
    uint8_t unlock = 0x00;
    return protocol.write(id, ST3215_REG::LOCK_PROTECTION, &unlock, 1);
}

bool ST3215_driver::eeprom_lock(uint8_t id)
{
    uint8_t lock = 0x01;
    return protocol.write(id, ST3215_REG::LOCK_PROTECTION, &lock, 1);
}

// ============================================================
// Misc
// ============================================================

bool ST3215_driver::ping(uint8_t id)
{
    return protocol.ping(id);
}

bool ST3215_driver::change_id(uint8_t old_id, uint8_t new_id)
{
    if (!eeprom_unlock(old_id))
    {
        return false;
    }

    delay(100);

    if (!protocol.write(old_id, ST3215_REG::ID, &new_id, 1))
    {
        return false;
    }

    delay(100);

    if (!eeprom_lock(new_id))
    {
        return false;
    }

    return true;
}

// ============================================================
// Torque
// ============================================================

bool ST3215_driver::set_torque(uint8_t id, bool enable)
{
    uint8_t value = enable ? 0x01 : 0x00;
    return protocol.write(id, ST3215_REG::TORQUE_SWITCH, &value, 1);
}

bool ST3215_driver::set_torque_limit(uint8_t id, uint16_t limit)
{
    uint8_t data[2] = 
    {
        (uint8_t)(limit & 0xFF),
        (uint8_t)((limit >> 8) & 0xFF)
    };
    return protocol.write(id, ST3215_REG::TORQUE_LIMIT, data, 2);
}

// ============================================================
// Angle
// ============================================================

bool ST3215_driver::set_angle(uint8_t id, uint16_t angle)
{
    uint16_t raw = (angle * 4096) / 360;
    uint8_t data[2] = 
    {
        (uint8_t)(raw & 0xFF),
        (uint8_t)((raw >> 8) & 0xFF)
    };
    return protocol.write(id, ST3215_REG::TARGET_LOCATION, data, 2);
}

bool ST3215_driver::read_angle(uint8_t id, uint16_t *angle)
{
    uint8_t response[2];
    if (!protocol.read(id, ST3215_REG::CURRENT_LOCATION, 2, response))
    {
        return false;
    }

    uint16_t raw = (response[1] << 8) | response[0];
    *angle = (raw * 360) / 4096;

    return true;
}

bool ST3215_driver::hardware_zero_calibration(uint8_t id, uint16_t angle)
{
    uint16_t raw = (angle * 4096) / 360;
    uint8_t data[2] = 
    {
        (uint8_t)(raw & 0xFF),
        (uint8_t)((raw >> 8) & 0xFF)
    };

    if (!eeprom_unlock(id))
    {
        return false;
    }

    delay(100);

    if (!protocol.write(id, ST3215_REG::POS_CORRECTION, data, 2))
        return false;

    delay(100);

    if (!eeprom_lock(id))
    {
        return false;
    }

    return true;
}

// ============================================================
// Speed
// ============================================================

bool ST3215_driver::set_speed(uint8_t id, uint16_t step_speed)
{
    uint8_t data[2] = 
    {
        (uint8_t)(step_speed & 0xFF),
        (uint8_t)((step_speed >> 8) & 0xFF)
    };
    return protocol.write(id, ST3215_REG::RUNNING_SPEED, data, 2);
}

bool ST3215_driver::read_speed(uint8_t id, uint16_t *step_speed)
{
    uint8_t response[2];
    if (!protocol.read(id, ST3215_REG::CURRENT_SPEED, 2, response))
    {
        return false;
    }

    *step_speed = (response[1] << 8) | response[0];
    return true;
}

// ============================================================
// Acceleration
// ============================================================

bool ST3215_driver::set_acceleration(uint8_t id, uint8_t acceleration)
{
    return protocol.write(id, ST3215_REG::ACCELERATION, &acceleration, 1);
}

// ============================================================
// Synchronized multi-servo
// ============================================================

bool ST3215_driver::set_angle_sync(uint8_t *ids, uint16_t *angles, uint8_t num_servos)
{
    // 2 bytes per servo: [pos_low, pos_high]
    uint8_t data[num_servos * 2];
    for (uint8_t i = 0; i < num_servos; i++)
    {
        uint16_t raw = (angles[i] * 4096) / 360;
        data[i * 2]     = (uint8_t)(raw & 0xFF);
        data[i * 2 + 1] = (uint8_t)((raw >> 8) & 0xFF);
    }
    return protocol.sync_write(ST3215_REG::TARGET_LOCATION, 2, ids, data, num_servos);
}

bool ST3215_driver::set_speed_sync(uint8_t *ids, uint16_t *speeds, uint8_t num_servos)
{
    // 2 bytes per servo: [speed_low, speed_high]
    uint8_t data[num_servos * 2];
    
    for (uint8_t i = 0; i < num_servos; i++)
    {
        data[i * 2]     = (uint8_t)(speeds[i] & 0xFF);
        data[i * 2 + 1] = (uint8_t)((speeds[i] >> 8) & 0xFF);
    }
    return protocol.sync_write(ST3215_REG::RUNNING_SPEED, 2, ids, data, num_servos);
}

bool ST3215_driver::set_angle_speed_sync(uint8_t *ids, uint16_t *angles, uint16_t *speeds, uint8_t num_servos)
{
    // 6 bytes per servo: [pos_low, pos_high, time_low, time_high, speed_low, speed_high]
    // time is set to 0 — motion is speed-controlled
    uint8_t data[num_servos * 6];
    for (uint8_t i = 0; i < num_servos; i++)
    {
        uint16_t raw_angle = (angles[i] * 4096) / 360;
        uint8_t offset = i * 6;
        data[offset]     = (uint8_t)(raw_angle & 0xFF);
        data[offset + 1] = (uint8_t)((raw_angle >> 8) & 0xFF);
        data[offset + 2] = 0x00;
        data[offset + 3] = 0x00;
        data[offset + 4] = (uint8_t)(speeds[i] & 0xFF);
        data[offset + 5] = (uint8_t)((speeds[i] >> 8) & 0xFF);
    }
    return protocol.sync_write(ST3215_REG::TARGET_LOCATION, 6, ids, data, num_servos);
}

// ============================================================
// Status & Safety
// ============================================================

bool ST3215_driver::read_temperature(uint8_t id, uint8_t *temperature)
{
    return protocol.read(id, ST3215_REG::CURRENT_TEMPERATURE, 1, temperature);
}

bool ST3215_driver::read_voltage(uint8_t id, uint8_t *voltage)
{
    return protocol.read(id, ST3215_REG::CURRENT_VOLTAGE, 1, voltage);
}

bool ST3215_driver::read_current(uint8_t id, uint16_t *current)
{
    uint8_t response[2];
    if (!protocol.read(id, ST3215_REG::CURRENT_CURRENT, 2, response))
        return false;

    *current = (response[1] << 8) | response[0];
    return true;
}

bool ST3215_driver::read_load(uint8_t id, uint16_t *load)
{
    uint8_t response[2];
    if (!protocol.read(id, ST3215_REG::CURRENT_LOAD, 2, response))
        return false;

    *load = (response[1] << 8) | response[0];
    return true;
}

bool ST3215_driver::read_status(uint8_t id, uint8_t *status)
{
    return protocol.read(id, ST3215_REG::SERVO_STATUS, 1, status);
}

bool ST3215_driver::is_moving(uint8_t id, bool *moving)
{
    uint8_t response;
    if (!protocol.read(id, ST3215_REG::MOBILE_SIGN, 1, &response))
        return false;

    *moving = (response == 0x01);
    return true;
}

// ============================================================
// Bulk reads
// ============================================================

bool ST3215_driver::read_all_angles(uint8_t *ids, uint16_t *angles, uint8_t num_servos)
{
    bool all_success = true;
    for (uint8_t i = 0; i < num_servos; i++)
    {
        if (!read_angle(ids[i], &angles[i]))
        {
            angles[i] = 0xFFFF; // sentinel value indicating read failure
            all_success = false;
        }
    }
    return all_success;
}

bool ST3215_driver::read_all_status(uint8_t *ids, uint8_t *statuses, uint8_t num_servos)
{
    bool all_success = true;
    for (uint8_t i = 0; i < num_servos; i++)
    {
        if (!read_status(ids[i], &statuses[i]))
        {
            statuses[i] = 0xFF; // sentinel value indicating read failure
            all_success = false;
        }
    }
    return all_success;
}

bool ST3215_driver::read_register(uint8_t id, ST3215_REG reg, uint8_t *out, uint8_t length)
{
    return protocol.read(id, reg, length, out);
}
// ============================================================
// Operation mode
// ============================================================

bool ST3215_driver::set_operation_mode(uint8_t id, ST3215_Mode mode)
{
    if (!eeprom_unlock(id))
        return false;

    delay(100);

    uint8_t value = static_cast<uint8_t>(mode);
    if (!protocol.write(id, ST3215_REG::OPERATION_MODE, &value, 1))
    {
        eeprom_lock(id); // attempt to re-lock even on failure
        return false;
    }

    delay(100);

    if (!eeprom_lock(id))
        return false;

    return true;
}