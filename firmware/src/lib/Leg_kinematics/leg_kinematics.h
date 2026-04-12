/**
 * @file leg.h
 * @brief Inverse and forward kinematics for a single hexapod leg
 *
 * @author Teh Wei Sheng
 * @author Lim Wei Jian
 * @date 2026
 *
 * MIT License — see LICENSE file in project root
 * Copyright (c) 2026 Teh Wei Sheng, Lim Wei Jian
 */

#ifndef LEG_KINEMATICS_H
#define LEG_KINEMATICS_H

#include "leg_kinematics_config.h"

#include <Arduino.h>
#include <math.h>

class Leg 
{
public:
    // constructor takes the IDs of the coxa, femur, and tibia servos
    Leg(uint8_t coxa_id, uint8_t femur_id, uint8_t tibia_id);

    void set_foot(float nx, float ny, float nz);

    // dont think these should be here, should be under Spider namespace. 
    void stand(int steps, int current_step);
    void balance(float pitch, float roll);

    void IK();
    void verify_IK();
    void FK(float a_in, float b_in, float c_in, float &fx, float &fy, float &fz);

    // get functions
    void get_angles(float &a_out, float &b_out, float &c_out);
    void get_position(float &x_out, float &y_out, float &z_out);
    void get_ids(uint8_t &coxa_id_out, uint8_t &femur_id_out, uint8_t &tibia_id_out);
    void get_fk(float &fx_out, float &fy_out, float &fz_out);
    void get_fk_error(float &error_x, float &error_y, float &error_z);

    bool is_ik_valid(float threshold = 1.0f);

private:
    // servo IDs
    uint8_t _coxa_id    = 0;
    uint8_t _femur_id   = 0;
    uint8_t _tibia_id   = 0;

    // coordinates of the foot relative to the coxa joint
    float _x            = X_OFFSET;
    float _y            = Y_OFFSET;
    float _z            = Z_OFFSET;

    // computed joint angles
    float _a            = 0.0f; // coxa angle
    float _b            = 0.0f; // femur angle
    float _c            = 0.0f; // tibia angle

    // FK verification result (set by verify_IK)
    float _fk_x         = 0.0f;
    float _fk_y         = 0.0f;
    float _fk_z         = 0.0f;
    float _fk_error_x   = 0.0f;
    float _fk_error_y   = 0.0f;
    float _fk_error_z   = 0.0f;
};

#endif