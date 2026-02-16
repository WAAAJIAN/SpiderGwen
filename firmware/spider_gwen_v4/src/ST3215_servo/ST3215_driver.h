/**
 * @file ST3215_driver.h
 * @author  Lim Wei Jian
 * @brief   This file contains the declaration of the ST3215_driver class, 
 *          which provides an interface for controlling the ST3215 servo motor.
 * @version 1.0
 * @date    2024-06-01
 */

#ifndef ST3215_DRIVER_H
#define ST3215_DRIVER_H

#include "ST3215_protocol.h"

class ST3215_driver {
    public:
        ST3215_driver();

        /**
         * @brief Initializes all connected ST3215 servo motors by pinging each possible ID and
         * resetting them to default settings.
         * @return true if initialization is successful, false otherwise.
         */
        bool init();

        /**
         * @brief Pings a servo motor with the specified ID to check if it is connected and responsive.
         * @param id The ID of the servo motor to ping.
         * @return true if the servo motor responds, false otherwise.
         */
        bool ping(uint8_t id);

        /**
         * @brief Resets the servo motor with the specified ID to its default settings.
         * @param id The ID of the servo motor to reset.
         * @return true if the reset command is successful, false otherwise.
         */
        bool reset(uint8_t id);


        /**
         * @brief Calibrates the servo motors by moving all of the servos to their maximum angle,
         * then to their minimum angle, and finally back to the center position. 
         * This process helps to ensure that the servo motors are properly aligned 
         * and can achieve their full range of motion.
         * 
         * `Maximum angle` is reached by sensing the load on the servo motor 
         * and moving it until the load exceeds a certain threshold, 
         * indicating that the servo has reached its maximum angle.
         * 
         * `Minimum angle` is reached by sensing the load on the servo motor 
         * and moving it in the opposite direction until the load exceeds 
         * a certain threshold, indicating that the servo has reached its minimum angle.
         * 
         * @return true if the calibration process is successful, false otherwise.
         */
        bool calibrate();

        /**
         * @brief Enables or disables the torque of the servo motor with the specified ID.
         * @param id The ID of the servo motor to control.
         * @param enable true to enable torque, false to disable torque.
         * @return true if the command is successful, false otherwise.
         */
        bool torque_enable(uint8_t id, bool enable);

        /**
         * @brief Writes a byte of data to a specific register address of the servo motor with the specified ID.
         * @param id The ID of the servo motor to write to.
         * @param reg_addr The register address to write to.
         * @param data The byte of data to write to the register.
         * @return true if the write command is successful, false otherwise.
         */
        bool write(uint8_t id, uint8_t reg_addr, uint8_t data);

        /**
         * @brief Reads a byte of data from a specific register address of the servo motor with the specified ID.
         * @param id The ID of the servo motor to read from.
         * @param reg_addr The register address to read from.
         * @param data A reference to a byte variable where the read data will be stored.
         * @return true if the read command is successful and data is stored in the provided variable, false otherwise.
         */
        bool read(uint8_t id, uint8_t reg_addr, uint8_t &data);

        /**
         * @brief Writes data to change angle of servomotor with the specified ID.
         * @param id The ID of the servo motor to control.
         * @param angle The target angle to set for the servo motor.
         * @return true if the command is successful, false otherwise.
         */
        bool ST3215_new_angle(uint8_t id, size_t angle);

        /**
         * @brief Writes data to change speed of servomotor with the specified ID.
         * @param id The ID of the servo motor to control.
         * @param speed The target speed to set for the servo motor.
         * @return true if the command is successful, false otherwise.
         */
        bool ST3215_speed(uint8_t id, size_t speed);

        /**
         * @brief Changes the ID of a servo motor from an old ID to a new ID.
         * @param old_id The current ID of the servo motor.
         * @param new_id The new ID to assign to the servo motor.
         * @return true if the ID change command is successful, false otherwise.
         */
        bool change_id(uint8_t old_id, uint8_t new_id);

        /**
         * @brief Reads the current load on the servo motor with the specified ID.
         * @param id The ID of the servo motor to read from.
         * @param load A reference to a byte variable where the read load value will be stored.
         * @return true if the read command is successful and load value is stored in the provided variable, false otherwise.
         */
        bool read_load(uint8_t id, uint8_t &load);


    private:
        ST3215_protocol protocol;
} ;

#endif // ST3215_DRIVER_H