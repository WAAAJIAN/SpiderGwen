/**
 * @file ST3215_driver.h
 * @author  Lim Wei Jian
 * @brief   This file contains the declaration of the ST3215_driver class, 
 *          which provides an interface for controlling the ST3215 servo motor.
 * @version 1.0
 * @date    2026-02-17
 */

#ifndef ST3215_DRIVER_H
#define ST3215_DRIVER_H

#include "ST3215_protocol.h"
#include <Arduino.h>


class ST3215_driver {
    public:
        ST3215_driver(HardwareSerial &serial);
        /**
         * Misc functions
         */
        bool change_id(uint8_t old_id, uint8_t new_id);
        bool ping(uint8_t id);  // ping will check the presence of a servo motor through their ID.
        
        /**
         * angle functions
         */
        bool set_angle(uint8_t id, size_t angle);
        bool read_angle(uint8_t id, size_t *angle);
        bool hardware_zero_calibration(uint8_t id, size_t angle);

        /**
         * speed functions
         */
        bool set_speed(uint8_t id, size_t speed);
        bool read_speed(uint8_t id, size_t *speed);

        /**
         * load functions
         */
        bool read_load(uint8_t id, uint8_t *load);

    protected:
        HardwareSerial &_serial;
        ST3215_protocol protocol;
} ;

#endif // ST3215_DRIVER_H