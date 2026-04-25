#ifndef LEG_KINEMATICS_CONFIG_H
#define LEG_KINEMATICS_CONFIG_H

// ===== Leg Geometry (mm) =====
#define COXA_LENGTH     55.65f
#define FEMUR_LENGTH   110.0f
#define TIBIA_LENGTH   145.4f

// ===== Neutral Foot Position (mm) =====
#define X_OFFSET         0.0f
#define Y_OFFSET       312.0f
#define Z_OFFSET         0.0f

// ===== Servo Angle Limits (ST3215 reference frame, degrees) =====
// ST3215 neutral is 180°. IK output is mapped into this frame (+180 offset).
#define COXA_MIN       135.0f
#define COXA_MAX       225.0f

#define FEMUR_MIN       70.0f
#define FEMUR_MAX      330.0f

#define TIBIA_MIN       60.0f
#define TIBIA_MAX      300.0f

#endif // LEG_KINEMATICS_CONFIG_H