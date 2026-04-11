#ifndef LEG_CONFIG_H
#define LEG_CONFIG_H

// Link lengths (mm)
constexpr float COXA_LENGTH  = 55.65f;
constexpr float FEMUR_LENGTH = 110.0f;
constexpr float TIBIA_LENGTH = 145.4f;

// Default foot position
constexpr float X_OFFSET = 0.0f;
constexpr float Y_OFFSET = 150.0f;
constexpr float Z_OFFSET = 150.0f;

// Joint limits (degrees)
constexpr float COXA_MIN  = -60.0f;
constexpr float COXA_MAX  =  60.0f;
constexpr float FEMUR_MIN = -60.0f;
constexpr float FEMUR_MAX =  60.0f;
constexpr float TIBIA_MIN =  30.0f;
constexpr float TIBIA_MAX = 150.0f;

#endif