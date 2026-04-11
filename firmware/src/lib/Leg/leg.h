#ifndef LEG_H
#define LEG_H

#include <Arduino.h>
#include <math.h>
#include "leg_config.h"
#include <ST3215_driver.h>

class Leg
{
public:
    float x, y, z;  // foot position
    float a, b, c;  // coxa, femur, tibia angles (degrees)

    uint8_t coxa_id;
    uint8_t femur_id;
    uint8_t tibia_id;

    Leg(uint8_t coxa_id, uint8_t femur_id, uint8_t tibia_id);

    void set_foot(float nx, float ny, float nz);
    void move(ST3215_driver &driver);    // apply IK angles to servos
    void print_angles();

private:
    void IK();
    float clampf(float val, float minv, float maxv);
};

#endif