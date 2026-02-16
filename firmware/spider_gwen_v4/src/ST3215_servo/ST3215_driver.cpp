#ifndef ST3215_DRIVER_CPP
#define ST3215_DRIVER_CPP

#include "ST3215_driver.h"

ST3215_driver::ST3215_driver(HardwareSerial &serial) : _serial(serial), protocol(serial) {}

// to do: init will calibrate all servo motors after pinging each one of them, then set them to their max height angle, 
// then to their min height angle, and finally back to the center position.
bool ST3215_driver::init() 
{

    return true; // Placeholder return value
}

bool ST3215_driver::ping(uint8_t id) 
{
    uint8_t data[1] = {0x01};
    if(!protocol.ST3215_write(id, 0x01, ST3215_PROTOCOL_PING, data))
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
    uint8_t unlock_data[2] = {ST3215_REG_LOCK_PROTECTION, 0x01};    // opens the lock
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
    uint8_t lock_data[2] = {ST3215_REG_LOCK_PROTECTION, 0x00};    // locks the register
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
    // to be continued...
    // angle has not been calculated properly yet, just a placeholder for now
    uint8_t data[3] = {ST3215_REG_TARGET_LOCATION, (uint8_t)(angle & 0xFF), (uint8_t)((angle >> 8) & 0xFF)};
    if(!protocol.ST3215_write(id, 0x03, ST3215_PROTOCOL_WRITE, data))
    {
        return false;
    }
    return true; // Placeholder return value
}


#endif