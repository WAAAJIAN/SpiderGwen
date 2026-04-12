#include "leg_kinematics.h"

float clampf(float val, float minv, float maxv) 
{
  if (val < minv) 
  {
    return minv;
  }

  if (val > maxv) 
  {
    return maxv;
  }

  return val;
}

Leg::Leg(uint8_t coxa_id, uint8_t femur_id, uint8_t tibia_id) 
{
  _coxa_id = coxa_id;
  _femur_id = femur_id;
  _tibia_id = tibia_id;
}

void Leg::set_foot(float nx, float ny, float nz) 
{
  _x = nx;
  _y = ny;
  _z = nz;
  IK();
}

void Leg::stand(int steps, int current_step)
{
  IK();

  float d = 20 - (20.0 / steps) * current_step;

  _b += d;
  _c += d;

  _b = clampf(_b, FEMUR_MIN, FEMUR_MAX);
  _c = clampf(_c, TIBIA_MIN, TIBIA_MAX);
}

void Leg::balance(float pitch, float roll)
{
  float dx = pitch * 2;
  float dy = roll * 2;

  _x = X_OFFSET + dx;
  _y = Y_OFFSET + dy;
  _z = Z_OFFSET;

  IK();
}

void Leg::IK() 
{

  float y1 = sqrt(_x*_x + _y*_y) - COXA_LENGTH;
  float k  = sqrt(y1*y1 + _z*_z);

  k = clampf(k, fabs(FEMUR_LENGTH - TIBIA_LENGTH), FEMUR_LENGTH + TIBIA_LENGTH);

  float ratio1 = clampf(_z / k, -1.0, 1.0);
  float theta = asin(ratio1);

  float ratio2 = clampf((FEMUR_LENGTH*FEMUR_LENGTH + k*k - TIBIA_LENGTH*TIBIA_LENGTH) / (2*FEMUR_LENGTH*k), -1.0, 1.0);
  float theta2 = acos(ratio2);

  float ratio3 = clampf((FEMUR_LENGTH*FEMUR_LENGTH + TIBIA_LENGTH*TIBIA_LENGTH - k*k) / (2*FEMUR_LENGTH*TIBIA_LENGTH), -1.0, 1.0);
  float tib = acos(ratio3);

  // IK angles
  float ia = atan2(_x, _y) * RAD_TO_DEG;
  float ib = (theta2 - theta) * RAD_TO_DEG;
  float ic = 180 - tib * RAD_TO_DEG;

  // map to servo reference frame, +180 because we set 180 to be neutral for ST3215
  _a = 180.0 + ia;
  _b = 180.0 + ib;
  _c = 180.0 + ic;

  // safety clamps
  _a = clampf(_a, COXA_MIN, COXA_MAX);
  _b = clampf(_b, FEMUR_MIN, FEMUR_MAX);
  _c = clampf(_c, TIBIA_MIN, TIBIA_MAX);
}

void Leg::FK(float a_in, float b_in, float c_in, float &fx, float &fy, float &fz)
{
  // Convert servo angles back to IK reference
  float ia = a_in - 180;
  float ib = b_in - 180;
  float ic = c_in - 180;

  float tib = 180 - ic;

  float theta = ib * DEG_TO_RAD;
  float tib_rad = tib * DEG_TO_RAD;

  float k = sqrt(FEMUR_LENGTH*FEMUR_LENGTH + TIBIA_LENGTH*TIBIA_LENGTH - 2*FEMUR_LENGTH*TIBIA_LENGTH*cos(tib_rad));

  float theta2 = acos((FEMUR_LENGTH*FEMUR_LENGTH + k*k - TIBIA_LENGTH*TIBIA_LENGTH) / (2*FEMUR_LENGTH*k));

  float z = k * sin(theta2 - theta);
  float y1 = k * cos(theta2 - theta);

  float planar = y1 + COXA_LENGTH;

  fx = planar * sin(ia * DEG_TO_RAD);
  fy = planar * cos(ia * DEG_TO_RAD);
  fz = z;
}

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
  coxa_id_out = _coxa_id;
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

bool Leg::is_ik_valid(float threshold)
{
  return fabs(_fk_error_x) < threshold && fabs(_fk_error_y) < threshold && fabs(_fk_error_z) < threshold;
}

void Leg::verify_IK()
{
  FK(_a, _b, _c, _fk_x, _fk_y, _fk_z);
  _fk_error_x = _fk_x - _x;
  _fk_error_y = _fk_y - _y;
  _fk_error_z = _fk_z - _z;
}
