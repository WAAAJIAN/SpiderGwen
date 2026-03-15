#ifndef HEXAPOD_PARAMETER_H
#define HEXAPOD_PARAMETER_H

// ===== Leg Geometry =====
#define COXA_LENGTH 55.65f
#define FEMUR_LENGTH 110.0f
#define TIBIA_LENGTH 145.4f

// ===== Neutral Foot Position =====
#define X_OFFSET 0.0f
#define Y_OFFSET 312.0f
#define Z_OFFSET 0.0f

// ===== Servo Limits (ST3215 reference frame) =====
#define COXA_MIN 135.0f
#define COXA_MAX 225.0f

#define FEMUR_MIN 70.0f
#define FEMUR_MAX 330.0f

#define TIBIA_MIN 60.0f
#define TIBIA_MAX 300.0f

#endif