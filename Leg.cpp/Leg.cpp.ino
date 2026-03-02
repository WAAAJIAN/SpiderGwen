#include <Arduino.h>
#include <math.h>

// parameter.py 

float cl = 55.65;
float fl = 110.0;
float tl = 145.4;

float x_offset = 0;
float y_offset = 150;
float z_offset = 150;

float coxa_min = -60;
float coxa_max = 60;

float femur_min = -60;
float femur_max = 60;

float tibia_min = 30;
float tibia_max = 150;

// safer clamp
float clampf(float val, float minv, float maxv) {
  if (val < minv) return minv;
  if (val > maxv) return maxv;
  return val;
}

class Leg {
public:
  float x, y, z;
  float a, b, c;

  Leg() {
    x = x_offset;
    y = y_offset;
    z = z_offset;
  }

  void setFoot(float nx, float ny, float nz) {
    x = nx;
    y = ny;
    z = nz;
    IK();
  }

  void IK() {

    float y1 = sqrt(x*x + y*y) - cl;
    float k  = sqrt(y1*y1 + z*z);

    // constrain workspace
    k = clampf(k, fabs(fl - tl), fl + tl);

    float ratio1 = clampf(z / k, -1.0, 1.0);
    float theta = asin(ratio1);

    float ratio2 = clampf((fl*fl + k*k - tl*tl) / (2*fl*k), -1.0, 1.0);
    float theta2 = acos(ratio2);

    a = atan2(x, y) * RAD_TO_DEG;
    b = (theta2 - theta) * RAD_TO_DEG;

    float ratio3 = clampf((fl*fl + tl*tl - k*k) / (2*fl*tl), -1.0, 1.0);
    float tib = acos(ratio3);

    c = 180.0 - tib * RAD_TO_DEG;

    // clamp angles
    a = clampf(a, coxa_min, coxa_max);
    b = clampf(b, femur_min, femur_max);
    c = clampf(c, tibia_min, tibia_max);
  }

  void printAngles() {
    Serial.print("Coxa: ");
    Serial.print(a);
    Serial.print("  Femur: ");
    Serial.print(b);
    Serial.print("  Tibia: ");
    Serial.println(c);
  }
};

Leg leg;

void setup() {
  Serial.begin(115200);
}

void loop() {
  // test position
  leg.setFoot(0, 150, 150);
  leg.printAngles();
  delay(2000);
  leg.setFoot(30, 150, 120);
  leg.printAngles();
  delay(2000);
  leg.setFoot(-30, 150, 120);
  leg.printAngles();
  delay(2000);
  leg.setFoot(0, 180, 100);
  leg.printAngles();
  delay(2000);
}
