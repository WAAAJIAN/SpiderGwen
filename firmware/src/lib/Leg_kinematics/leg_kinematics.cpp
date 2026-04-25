#include "leg_kinematics.h"
 
// ------------------------------------------------------------------ //
//  Internal helper
// ------------------------------------------------------------------ //
 
static float clampf(float val, float minv, float maxv)
{
    if (val < minv) return minv;
    if (val > maxv) return maxv;
    return val;
}
 
// ------------------------------------------------------------------ //
//  Constructor
// ------------------------------------------------------------------ //
 
Leg::Leg(uint8_t coxa_id, uint8_t femur_id, uint8_t tibia_id)
{
    _coxa_id  = coxa_id;
    _femur_id = femur_id;
    _tibia_id = tibia_id;
}
 
// ------------------------------------------------------------------ //
//  Public interface
// ------------------------------------------------------------------ //
 
void Leg::set_foot(float nx, float ny, float nz)
{
    _x = nx;
    _y = ny;
    _z = nz;
    IK();
    verify_IK();  // keep FK error fresh so is_ik_valid() is always accurate
}
 
// ------------------------------------------------------------------ //
//  Inverse Kinematics
// ------------------------------------------------------------------ //
 
void Leg::IK()
{
    // Planar distance from femur joint to foot tip
    float y1 = sqrt(_x * _x + _y * _y) - COXA_LENGTH;
 
    // Straight-line distance from femur joint to foot tip (3D)
    float k = sqrt(y1 * y1 + _z * _z);
 
    // Clamp k to reachable workspace
    k = clampf(k, fabsf(FEMUR_LENGTH - TIBIA_LENGTH), FEMUR_LENGTH + TIBIA_LENGTH);
 
    // Elevation angle of k above the horizontal plane
    float theta  = asin(clampf(_z / k, -1.0f, 1.0f));
 
    // Angle at femur joint (law of cosines)
    float theta2 = acos(clampf(
        (FEMUR_LENGTH * FEMUR_LENGTH + k * k - TIBIA_LENGTH * TIBIA_LENGTH)
        / (2.0f * FEMUR_LENGTH * k),
        -1.0f, 1.0f));
 
    // Angle at tibia joint (law of cosines)
    float tib = acos(clampf(
        (FEMUR_LENGTH * FEMUR_LENGTH + TIBIA_LENGTH * TIBIA_LENGTH - k * k)
        / (2.0f * FEMUR_LENGTH * TIBIA_LENGTH),
        -1.0f, 1.0f));
 
    // Raw IK angles (degrees, IK reference frame)
    float ia = atan2(_x, _y) * RAD_TO_DEG;
    float ib = (theta2 - theta) * RAD_TO_DEG;
    float ic = 180.0f - tib * RAD_TO_DEG;
 
    // Map to ST3215 servo reference frame (neutral = 180°)
    _a = 180.0f + ia;
    _b = 180.0f + ib;
    _c = 180.0f + ic;
 
    // Safety clamps to servo limits
    _a = clampf(_a, COXA_MIN,  COXA_MAX);
    _b = clampf(_b, FEMUR_MIN, FEMUR_MAX);
    _c = clampf(_c, TIBIA_MIN, TIBIA_MAX);
}
 
// ------------------------------------------------------------------ //
//  Forward Kinematics
// ------------------------------------------------------------------ //
 
void Leg::FK(float a_in, float b_in, float c_in, float &fx, float &fy, float &fz)
{
    // Convert ST3215 servo angles back to IK reference frame
    float ia = a_in - 180.0f;
    float ib = b_in - 180.0f;
    float ic = c_in - 180.0f;
 
    // Reconstruct tibia angle used in IK
    float tib     = 180.0f - ic;
    float tib_rad = tib * DEG_TO_RAD;
    float theta   = ib  * DEG_TO_RAD;
 
    // Reconstruct k (femur-to-foot distance) via law of cosines
    float k = sqrt(
        FEMUR_LENGTH * FEMUR_LENGTH
        + TIBIA_LENGTH * TIBIA_LENGTH
        - 2.0f * FEMUR_LENGTH * TIBIA_LENGTH * cos(tib_rad));
 
    // Reconstruct theta2 (femur elevation angle)
    float theta2 = acos(clampf(
        (FEMUR_LENGTH * FEMUR_LENGTH + k * k - TIBIA_LENGTH * TIBIA_LENGTH)
        / (2.0f * FEMUR_LENGTH * k),
        -1.0f, 1.0f));
 
    // Decompose into vertical and planar components
    float z       = k * sin(theta2 - theta);
    float y1      = k * cos(theta2 - theta);
    float planar  = y1 + COXA_LENGTH;
 
    // Rotate planar reach by coxa angle
    fx = planar * sin(ia * DEG_TO_RAD);
    fy = planar * cos(ia * DEG_TO_RAD);
    fz = z;
}
 
void Leg::verify_IK()
{
    FK(_a, _b, _c, _fk_x, _fk_y, _fk_z);
    _fk_error_x = _fk_x - _x;
    _fk_error_y = _fk_y - _y;
    _fk_error_z = _fk_z - _z;
}
 
bool Leg::is_ik_valid(float threshold)
{
    return fabsf(_fk_error_x) < threshold
        && fabsf(_fk_error_y) < threshold
        && fabsf(_fk_error_z) < threshold;
}
 
// ------------------------------------------------------------------ //
//  Getters
// ------------------------------------------------------------------ //
 
void Leg::get_angles(float &a_out, float &b_out, float &c_out)
{
    a_out = _a;
    b_out = _b;
    c_out = _c;
}
 
void Leg::get_position(float &x_out, float &y_out, float &z_out)
{
    x_out = _x;
    y_out = _y;
    z_out = _z;
}
 
void Leg::get_ids(uint8_t &coxa_id_out, uint8_t &femur_id_out, uint8_t &tibia_id_out)
{
    coxa_id_out  = _coxa_id;
    femur_id_out = _femur_id;
    tibia_id_out = _tibia_id;
}
 
void Leg::get_fk(float &fx_out, float &fy_out, float &fz_out)
{
    fx_out = _fk_x;
    fy_out = _fk_y;
    fz_out = _fk_z;
}
 
void Leg::get_fk_error(float &error_x, float &error_y, float &error_z)
{
    error_x = _fk_error_x;
    error_y = _fk_error_y;
    error_z = _fk_error_z;
}