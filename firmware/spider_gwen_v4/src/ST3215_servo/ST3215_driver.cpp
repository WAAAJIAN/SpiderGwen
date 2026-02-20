#ifndef ST3215_DRIVER_CPP
#define ST3215_DRIVER_CPP

#include "ST3215_driver.h"

ST3215_driver::ST3215_driver(HardwareSerial &serial) : _serial(serial), protocol(serial) {}

// to do: init will calibrate all servo motors after pinging each one of them, then set them to their max height angle, 
// then to their min height angle, and finally back to the center position.

bool ST3215_driver::ping(uint8_t id) 
{
    if(!protocol.ST3215_write(id, 0x00, ST3215_PROTOCOL_PING, nullptr))
    {
        return false;
    }
    uint8_t response[1];
    if (!protocol.ST3215_receive(id, response)) 
    {
        return false;
        
    }
    
    if(response[0] != 0x00) // Assuming 0x00 is the expected response for a successful ping
    {
        return false;
    }

    return true;
}

bool ST3215_driver::change_id(uint8_t old_id, uint8_t new_id) 
{
    // First need to unlock register
    uint8_t unlock_data[2] = {ST3215_REG_LOCK_PROTECTION, 0x00};    // opens the lock
    if(!protocol.ST3215_write(old_id, 0x04, ST3215_PROTOCOL_WRITE, unlock_data))
    {
        return false;
    }
    
    uint8_t first_response[1];
    if (!protocol.ST3215_receive(old_id, first_response))
    {
        return false;
    }

    if (first_response[0] != 0x00)
    {
        return false;
    }

    // Then write new ID to the ID register
    uint8_t data[2] = {ST3215_REG_ID, new_id};
    if(!protocol.ST3215_write(old_id, 0x04, ST3215_PROTOCOL_WRITE, data))
    {
        return false;
    }

    // Finally, lock the register again with the new ID
    uint8_t lock_data[2] = {ST3215_REG_LOCK_PROTECTION, 0x01};    // locks the register
    if(!protocol.ST3215_write(new_id, 0x04, ST3215_PROTOCOL_WRITE, lock_data))
    {
        return false;
    }

    uint8_t second_response[1];
    if (!protocol.ST3215_receive(new_id, second_response))
    {
        return false;
    }

    if (second_response[0] != 0x00)
    {
        return false;
    }

    return true;
}

bool ST3215_driver::set_angle(uint8_t id, size_t angle) 
{
    // convert angle to the bytes required by the protocol
    size_t raw_value = (angle * 4096) / 360;

    uint8_t data[3] = {ST3215_REG_TARGET_LOCATION, (uint8_t)(raw_value & 0xFF), (uint8_t)((raw_value >> 8) & 0xFF)};

    if(!protocol.ST3215_write(id, 0x05, ST3215_PROTOCOL_WRITE, data))
    {
        return false;
    }

    return true; // Placeholder return value
}

bool ST3215_driver::read_angle(uint8_t id, size_t *angle) 
{
    uint8_t raw_data[2] = {ST3215_REG_CURRENT_LOCATION, 0x02};
    if (!protocol.ST3215_write(id, 0x04, ST3215_PROTOCOL_READ, raw_data))
    {
        return false;
    }

    uint8_t response[2];
    if (!protocol.ST3215_receive(id, response)) 
    {
        return false;
    }

    size_t raw_value = (response[1] << 8) | response[0];
    *angle = (size_t)((raw_value * 360) / 4096);

    return true; // Placeholder return value
}

bool ST3215_driver::hardware_zero_calibration(uint8_t id, size_t angle) 
{
    // convert angle to the bytes required by the protocol
    size_t raw_value = (angle * 4096) / 360;

    uint8_t data[3] = {ST3215_REG_POS_CORRECTION, (uint8_t)(raw_value & 0xFF), (uint8_t)((raw_value >> 8) & 0xFF)};

    if(!protocol.ST3215_write(id, 0x05, ST3215_PROTOCOL_REGWRITE, data))
    {
        return false;
    }

    return true; // Placeholder return value
}

bool ST3215_driver::set_speed(uint8_t id, size_t step_speed) 
{
    // bytes are direct to the amount of steps per second
    uint8_t data[3] = {ST3215_REG_RUNNING_SPEED, (uint8_t)(step_speed & 0xFF), (uint8_t)((step_speed >> 8) & 0xFF)};

    if(!protocol.ST3215_write(id, 0x05, ST3215_PROTOCOL_WRITE, data))
    {
        return false;
    }

    return true;
}

bool ST3215_driver::read_speed(uint8_t id, size_t *step_speed) 
{
    uint8_t raw_data[2] = {ST3215_REG_CURRENT_SPEED, 0x02};
    if (!protocol.ST3215_write(id, 0x04, ST3215_PROTOCOL_READ, raw_data))
    {
        return false;
    }

    uint8_t response[2];
    if (!protocol.ST3215_receive(id, response)) 
    {
        return false;
    }

    *step_speed = (size_t)((response[1] << 8) | response[0]);

    return true;
}

bool ST3215_driver::read_load(uint8_t id, uint8_t *load) 
{
    uint8_t raw_data[2] = {ST3215_REG_CURRENT_LOAD, 0x02};
    if (!protocol.ST3215_write(id, 0x04, ST3215_PROTOCOL_READ, raw_data))
    {
        return false;
    }

    uint8_t response[2];
    if (!protocol.ST3215_receive(id, response)) 
    {
        return false;
    }

    *load = (size_t)((response[1] << 8) | response[0]);
    return true;
}

#endif