#ifndef LEG_KINEMATICS_H
#define LEG_KINEMATICS_H
 
#include "leg_kinematics_config.h"
#include <Arduino.h>
#include <math.h>
 
class Leg
{
public:
    /**
     * @brief Construct a Leg with its three servo IDs.
     * @param coxa_id   RS-485 ID of the coxa  servo
     * @param femur_id  RS-485 ID of the femur servo
     * @param tibia_id  RS-485 ID of the tibia servo
     */
    Leg(uint8_t coxa_id, uint8_t femur_id, uint8_t tibia_id);
 
    /**
     * @brief Set desired foot position and recompute IK + FK verification.
     * @param nx  Target X coordinate (mm, lateral)
     * @param ny  Target Y coordinate (mm, forward reach)
     * @param nz  Target Z coordinate (mm, vertical)
     */
    void set_foot(float nx, float ny, float nz);
 
    /**
     * @brief Run IK to compute joint angles from current (x, y, z).
     *        Called automatically by set_foot(). Exposed for direct use if needed.
     */
    void IK();
 
    /**
     * @brief Run FK on current joint angles and compute error vs target position.
     *        Called automatically by set_foot(). Results accessible via get_fk_error().
     */
    void verify_IK();
 
    /**
     * @brief Forward kinematics: compute foot position from joint angles.
     * @param a_in   Coxa  servo angle (degrees, ST3215 frame)
     * @param b_in   Femur servo angle (degrees, ST3215 frame)
     * @param c_in   Tibia servo angle (degrees, ST3215 frame)
     * @param fx     Output X position (mm)
     * @param fy     Output Y position (mm)
     * @param fz     Output Z position (mm)
     */
    void FK(float a_in, float b_in, float c_in, float &fx, float &fy, float &fz);
 
    /**
     * @brief Returns true if FK error is within threshold (default 1.0mm).
     *        Used by Spider::execute_movements() to validate all legs before
     *        sending a sync write to the servo bus.
     */
    bool is_ik_valid(float threshold = 1.0f);
 
    // ----- Getters -----
    void get_angles(float &a_out, float &b_out, float &c_out);
    void get_position(float &x_out, float &y_out, float &z_out);
    void get_ids(uint8_t &coxa_id_out, uint8_t &femur_id_out, uint8_t &tibia_id_out);
    void get_fk(float &fx_out, float &fy_out, float &fz_out);
    void get_fk_error(float &error_x, float &error_y, float &error_z);
 
private:
    // Servo RS-485 IDs
    uint8_t _coxa_id  = 0;
    uint8_t _femur_id = 0;
    uint8_t _tibia_id = 0;
 
    // Target foot position (mm, leg-local frame)
    float _x = X_OFFSET;
    float _y = Y_OFFSET;
    float _z = Z_OFFSET;
 
    // Computed joint angles (degrees, ST3215 reference frame)
    float _a = 0.0f;  // coxa
    float _b = 0.0f;  // femur
    float _c = 0.0f;  // tibia
 
    // FK verification results (set by verify_IK)
    float _fk_x       = 0.0f;
    float _fk_y       = 0.0f;
    float _fk_z       = 0.0f;
    float _fk_error_x = 0.0f;
    float _fk_error_y = 0.0f;
    float _fk_error_z = 0.0f;
};
 
#endif // LEG_KINEMATICS_H