#pragma once
#include <Arduino.h>

class Leg {
public:
  float x, y, z;
  float a, b, c;

  Leg();

  void setFoot(float nx, float ny, float nz);
  void IK();
  void printAngles();
};