/**
 * @file spider.h
 * @brief High-level hexapod robot control — orchestrates all 6 legs and the servo bus.
 *        Sole owner of the ST3215_driver bus access, preventing race conditions.
 *
 * @author Lim Wei Jian
 * @author Teh Wei Sheng
 * @date 2026
 *
 * MIT License — see LICENSE file in project root
 * Copyright (c) 2026 Lim Wei Jian
 */

#ifndef SPIDER_H
#define SPIDER_H

#include <Arduino.h>
#include "ST3215_driver.h"
#include "leg_kinematics.h"

// ============================================================
// Hexapod configuration
// ============================================================
#define NUM_LEGS        6
#define JOINTS_PER_LEG  3
#define NUM_SERVOS      (NUM_LEGS * JOINTS_PER_LEG)

namespace Spider
{

    static ST3215_driver *_driver   = nullptr;
    static Leg *_legs[NUM_LEGS]     = { nullptr };
    static bool _initialised        = false;
    /**
     * @brief Initialise the spider with a shared servo driver. Must be called before any other Spider function.
     * @param driver    Reference to the ST3215 driver instance
     * @param coxa_ids  Array of 6 coxa servo IDs
     * @param femur_ids Array of 6 femur servo IDs
     * @param tibia_ids Array of 6 tibia servo IDs
     */
    void init(ST3215_driver &driver, uint8_t *coxa_ids, uint8_t *femur_ids, uint8_t *tibia_ids);

    /**
     * @brief Ping all 18 servos and report which ones respond.
     * @return true if all servos respond
     */
    bool ping_all();

    /**
     * @brief Set target foot position for a single leg. Runs IK internally — does not send to bus yet.
     * @param leg_index 0-5
     * @param x         foot x position (mm)
     * @param y         foot y position (mm)
     * @param z         foot z position (mm)
     */
    void set_foot(uint8_t leg_index, float x, float y, float z);

    /**
     * @brief Move all legs to neutral standing position.
     * @param speed steps/s
     */
    void stand(uint16_t speed = 1000);

    /**
     * @brief Adjust all leg positions in response to IMU pitch and roll.
     * @param pitch pitch angle (degrees)
     * @param roll  roll angle (degrees)
     * @param speed steps/s
     */
    void balance(float pitch, float roll, uint16_t speed = 1000);

    /**
     * @brief Execute the computed movements for all legs by sending appropriate commands to the servo driver.
     */
    void execute_movements(uint16_t speed = 1000);

    /**
     * @brief Enable or disable torque on all 18 servos. For hexapod to go into limping if needed.
     * @param enable true = torque on, false = torque off
     */
    void enable_torque(bool enable);

    /**
     * @brief Emergency stop — disable torque on all servos immediately.
     */
    void estop();

    /**
     * @brief Read current angles from all 18 servos.
     * @param angles output array of 18 angles in degrees
     * @return true if all reads succeeded
     */
    bool read_all_angles(uint16_t *angles);

    /**
     * @brief Read status byte from all 18 servos.
     * @param statuses output array of 18 status bytes
     * @return true if all reads succeeded, false if any servo has a fault
     */
    bool read_all_status(uint8_t *statuses);


};
#endif