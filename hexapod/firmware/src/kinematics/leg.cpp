#include "leg.h"
#include <math.h>

// parameters
float cl = 55.65;
float fl = 110.0;
float tl = 145.4;

float x_offset = 0;
float y_offset = 325;
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

  // map to servo reference frame
  a = 180.0 + ia;
  b = 180.0 + ib;
  c = 180.0 + ic;

  // safety clamps
  a = clampf(a, coxa_min, coxa_max);
  b = clampf(b, femur_min, femur_max);
  c = clampf(c, tibia_min, tibia_max);
}

void Leg::printAngles() {
  Serial.print("  Coxa: ");
  Serial.print(a);
  Serial.print("  Femur: ");
  Serial.print(b);
  Serial.print("  Tibia: ");
  Serial.println(c);
}


// #include "leg.h"
// #include <math.h>

// // ==============================
// // Physical geometry parameters
// // ==============================

// float cl = 55.65;
// float fl = 110.0;
// float tl = 145.4;

// // ==============================
// // Measured robot neutral offset
// // ==============================

// float x_offset = 0;
// float y_offset = 325;
// float z_offset = 0;

// // ==============================
// // Servo safety limits
// // ==============================

// float coxa_min = 135;
// float coxa_max = 225;

// float femur_min = 70;
// float femur_max = 330;

// float tibia_min = 60;
// float tibia_max = 300;

// // ==============================
// // Clamp helper
// // ==============================

// float clampf(float val, float minv, float maxv) {
//   if (val < minv) return minv;
//   if (val > maxv) return maxv;
//   return val;
// }

// // ==============================
// // Constructor
// // ==============================

// Leg::Leg() {
//   x = x_offset;
//   y = y_offset;
//   z = z_offset;
// }

// // ==============================
// // Set desired foot position
// // ==============================

// void Leg::setFoot(float nx, float ny, float nz) {
//   x = nx;
//   y = ny;
//   z = nz;
//   IK();
// }

// // ==============================
// // Inverse Kinematics Solver
// // ==============================

// void Leg::IK() {

//   // ------------------------------------------------
//   // Transform world frame → leg local frame
//   // ------------------------------------------------

//   float Xr = x - x_offset;
//   float Yr = y - y_offset;
//   float Zr = z - z_offset;

//   // ------------------------------------------------
//   // Horizontal projection distance (coxa plane)
//   // ------------------------------------------------

//   float planar_dist = sqrt(Xr*Xr + Yr*Yr);

//   float y1 = planar_dist - cl;

//   float k = sqrt(y1*y1 + Zr*Zr);

//   // Geometry clamp
//   k = clampf(k, fabs(fl - tl), fl + tl);

//   // ------------------------------------------------
//   // IK solving
//   // ------------------------------------------------

//   float ratio1 = clampf(Zr / k, -1.0, 1.0);
//   float theta = asin(ratio1);

//   float ratio2 = clampf((fl*fl + k*k - tl*tl) / (2*fl*k), -1.0, 1.0);
//   float theta2 = acos(ratio2);

//   float ratio3 = clampf((fl*fl + tl*tl - k*k) / (2*fl*tl), -1.0, 1.0);
//   float tib = acos(ratio3);

//   // ------------------------------------------------
//   // IK angles (robot joint space)
//   // ------------------------------------------------

//   float ia = atan2(Xr, Yr) * RAD_TO_DEG;
//   float ib = (theta2 - theta) * RAD_TO_DEG;
//   float ic = 180.0 - tib * RAD_TO_DEG;

//   // ------------------------------------------------
//   // Safety clamp
//   // ------------------------------------------------

//   a = clampf(ia, coxa_min, coxa_max);
//   b = clampf(ib, femur_min, femur_max);
//   c = clampf(360-ic, tibia_min, tibia_max);
// }

// // ==============================
// // Debug print
// // ==============================

// void Leg::printAngles() {
//   Serial.print("  Coxa: ");
//   Serial.print(a);
//   Serial.print("  Femur: ");
//   Serial.print(b);
//   Serial.print("  Tibia: ");
//   Serial.println(c);
// }