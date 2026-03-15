#include "leg.h"
#include <math.h>
#include "parameter.h"

// parameters
float cl = 55.65;
float fl = 110.0;
float tl = 145.4;

// Neutral position when leg is horizontally straight is (0, 312, 0)
float x_offset = 0;
float y_offset = 312;
float z_offset = 0;

float coxa_min = 135;
float coxa_max = 225;

float femur_min = 70;
float femur_max = 330;

float tibia_min = 60;
float tibia_max = 300;

float clampf(float val, float minv, float maxv) {
  if (val < minv) return minv;
  if (val > maxv) return maxv;
  return val;
}

Leg::Leg() {
  x = x_offset;
  y = y_offset;
  z = z_offset;
}

void Leg::setFoot(float nx, float ny, float nz) {
  x = nx;
  y = ny;
  z = nz;
  IK();
}

void Leg::IK() {

  float y1 = sqrt(x*x + y*y) - cl;
  float k  = sqrt(y1*y1 + z*z);

  k = clampf(k, fabs(fl - tl), fl + tl);

  float ratio1 = clampf(z / k, -1.0, 1.0);
  float theta = asin(ratio1);

  float ratio2 = clampf((fl*fl + k*k - tl*tl) / (2*fl*k), -1.0, 1.0);
  float theta2 = acos(ratio2);

  float ratio3 = clampf((fl*fl + tl*tl - k*k) / (2*fl*tl), -1.0, 1.0);
  float tib = acos(ratio3);

  // IK angles
  float ia = atan2(x, y) * RAD_TO_DEG;
  float ib = (theta2 - theta) * RAD_TO_DEG;
  float ic = 180 - tib * RAD_TO_DEG;

  // map to servo reference frame, +180 because we set 180 to be neutral for ST3215
  a = 180.0 + ia;
  b = 180.0 + ib;
  c = 180.0 + ic;

  // safety clamps
  a = clampf(a, coxa_min, coxa_max);
  b = clampf(b, femur_min, femur_max);
  c = clampf(c, tibia_min, tibia_max);
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

  float k = sqrt(fl*fl + tl*tl - 2*fl*tl*cos(tib_rad));

  float theta2 = acos((fl*fl + k*k - tl*tl)/(2*fl*k));

  float z = k * sin(theta2 - theta);
  float y1 = k * cos(theta2 - theta);

  float planar = y1 + cl;

  fx = planar * sin(ia * DEG_TO_RAD);
  fy = planar * cos(ia * DEG_TO_RAD);
  fz = z;
}

void Leg::verifyIK()
{
  float fx, fy, fz;

  FK(a, b, c, fx, fy, fz);

  Serial.print("Target: ");
  Serial.print(x); Serial.print(" ");
  Serial.print(y); Serial.print(" ");
  Serial.println(z);

  Serial.print("FK: ");
  Serial.print(fx); Serial.print(" ");
  Serial.print(fy); Serial.print(" ");
  Serial.println(fz);

  Serial.print("Error: ");
  Serial.print(fx - x); Serial.print(" ");
  Serial.print(fy - y); Serial.print(" ");
  Serial.println(fz - z);
}

void Leg::stand(int steps, int current_step)
{
  IK();

  float d = 20 - (20.0 / steps) * current_step;

  b += d;
  c += d;

  b = clampf(b, femur_min, femur_max);
  c = clampf(c, tibia_min, tibia_max);
}

void Leg::balance(float pitch, float roll)
{
  float dx = pitch * 2;
  float dy = roll * 2;

  x = x_offset + dx;
  y = y_offset + dy;
  z = z_offset;

  IK();
}

void Leg::balance(float pitch, float roll)
{
  float dx = pitch * 2;
  float dy = roll * 2;

  x = x_offset + dx;
  y = y_offset + dy;
  z = z_offset;

  IK();
}

void Leg::printAngles() {
  Serial.print("  Coxa: ");
  Serial.print(a);
  Serial.print("  Femur: ");
  Serial.print(b);
  Serial.print("  Tibia: ");
  Serial.println(c);
}
