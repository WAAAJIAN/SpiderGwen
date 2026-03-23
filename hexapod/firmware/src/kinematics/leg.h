#pragma once
#include <Arduino.h>

class Leg {
public:
  float x, y, z;
  float a, b, c;

  Leg();

  void setFoot(float nx, float ny, float nz);
  void IK();
  void FK(float a_in, float b_in, float c_in, float &fx, float &fy, float &fz);
  void verifyIK();
  void stand(int steps, int current_step);
  void balance(float pitch, float roll);

  void printAngles();
};