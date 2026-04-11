#include "leg.h"

Leg::Leg(uint8_t coxa_id, uint8_t femur_id, uint8_t tibia_id)
    : coxa_id(coxa_id), femur_id(femur_id), tibia_id(tibia_id)
{
    x = X_OFFSET;
    y = Y_OFFSET;
    z = Z_OFFSET;
}

void Leg::set_foot(float nx, float ny, float nz)
{
    x = nx;
    y = ny;
    z = nz;
    IK();
}

void Leg::move(ST3215_driver &driver)
{
    // apply computed IK angles to the physical servos
    uint8_t ids[3]    = { coxa_id, femur_id, tibia_id };
    uint16_t angles[3] = {
        (uint16_t)(a + 180),  // offset to servo range if needed
        (uint16_t)(b + 180),
        (uint16_t)(c + 180)
    };
    uint16_t speeds[3] = 
    { 
        500, 
        500, 
        500 
    };
    driver.set_angle_speed_sync(ids, angles, speeds, 3);
}

void Leg::IK()
{
    float y1 = sqrt(x*x + y*y) - COXA_LENGTH;
    float k  = sqrt(y1*y1 + z*z);

    k = clampf(k, fabs(FEMUR_LENGTH - TIBIA_LENGTH), FEMUR_LENGTH + TIBIA_LENGTH);

    float theta  = asin(clampf(z / k, -1.0f, 1.0f));
    float theta2 = acos(clampf((FEMUR_LENGTH*FEMUR_LENGTH + k*k - TIBIA_LENGTH*TIBIA_LENGTH) / (2*FEMUR_LENGTH*k), -1.0f, 1.0f));

    a = atan2(x, y) * RAD_TO_DEG;
    b = (theta2 - theta) * RAD_TO_DEG;

    float tib = acos(clampf((FEMUR_LENGTH*FEMUR_LENGTH + TIBIA_LENGTH*TIBIA_LENGTH - k*k) / (2*FEMUR_LENGTH*TIBIA_LENGTH), -1.0f, 1.0f));
    c = 180.0f - tib * RAD_TO_DEG;

    a = clampf(a, COXA_MIN, COXA_MAX);
    b = clampf(b, FEMUR_MIN, FEMUR_MAX);
    c = clampf(c, TIBIA_MIN, TIBIA_MAX);
}

void Leg::print_angles()
{
    Serial.print("Coxa: ");  Serial.print(a);
    Serial.print("  Femur: "); Serial.print(b);
    Serial.print("  Tibia: "); Serial.println(c);
}

float Leg::clampf(float val, float minv, float maxv)
{
    if (val < minv) return minv;
    if (val > maxv) return maxv;
    return val;
}