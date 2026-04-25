## legstate.py
## Lightweight leg state tracker and pure foot trajectory math for SpiderGwen RPi side.
##
## This is the RPi equivalent of leg_kinematics.cpp on the ESP32.
## Key difference: no IK, no servo angles, no PWM — this file only deals with
## (x, y, z) foot positions in body-frame coordinates.
## The ESP32 receives those positions and handles IK + servo execution.

from math import sin, cos, radians
from .parameter import (
    x_offset, y_offset, z_offset,
    offset_angle_map, leg_type_map,
    transformLegtoBody, R,
    walk_distance
)


class LegState:
    """
    Tracks the current foot position (x, y, z) for a single leg.

    Mirrors the role of the Leg class in leg_kinematics.cpp on the ESP32,
    but contains no IK or servo logic — only body-frame position state
    and the transform parameters needed for trajectory calculations.
    """

    def __init__(self, leg_id: int):
        self.leg_id       = leg_id
        self.x            = x_offset
        self.y            = y_offset
        self.z            = z_offset
        self.offset_angle = offset_angle_map[leg_id]
        self.offset       = leg_type_map[leg_id]

    def set_position(self, x: float, y: float, z: float):
        self.x = x
        self.y = y
        self.z = z

    def get_position(self) -> tuple:
        return (self.x, self.y, self.z)


def calculate_walk_xyz(
    leg: LegState,
    phase: float,
    direction: list,
    distance: float,
    pitch: float,
    roll: float,
    yaw: float,
    rotate: bool
) -> tuple:
    """
    Computes the target foot position (x, y, z) for a given gait phase.
    Ported from legacy leg.py calculateWalk() — math is identical,
    hardware references removed.

    Phase 0–180:   Swing phase — foot arcs upward and steps forward.
    Phase 180–360: Stance phase — foot stays on ground, body is pushed forward.
                   Balance corrections (roll/pitch/yaw) applied during stance.

    Args:
        leg:       LegState for this leg (provides transform params)
        phase:     Current gait phase in degrees [0, 360]
        direction: [dx, dy] or [dx, dy, 1] for rotation moves
        distance:  Step distance in mm (walk_distance from parameter.py)
        pitch:     PID pitch correction angle (degrees)
        roll:      PID roll correction angle (degrees)
        yaw:       PID yaw correction angle (degrees)
        rotate:    True if this is a rotational move (direction has 3 elements)

    Returns:
        (x, y, z) foot position in body frame (mm)
    """
    if phase <= 180:
        # Swing phase: foot traces a forward semicircle arc above ground
        turn_distance = 0.5 * distance
        x = direction[0] * ( turn_distance * cos(radians(180 - phase)) + turn_distance)
        y = direction[1] * -( turn_distance * cos(radians(180 - phase)) + turn_distance)
        z = -distance * sin(radians(phase)) + z_offset
    else:
        # Stance phase: foot moves backward linearly along the ground
        turn_distance = distance
        x = direction[0] * (-1 * turn_distance * ((phase / 180) - 1) + distance)
        y = direction[1] * -(-1 * turn_distance * ((phase / 180) - 1) + distance)
        z = z_offset

    # Transform leg-local XY vector into body frame
    if not rotate:
        new_vec = transformLegtoBody(leg.leg_id, [x, y])
    else:
        new_vec = [x, y]

    foot_x = x_offset + new_vec[0]
    foot_y = y_offset + new_vec[1]
    foot_z = z

    # Compute balance correction vectors
    R_c = R(leg.offset, leg.offset_angle, roll, pitch, yaw, [foot_x, foot_y])

    # Roll/pitch corrections only applied during stance phase
    if phase > 180:
        roll_vec  = transformLegtoBody(leg.leg_id, R_c[0][:2])
        pitch_vec = transformLegtoBody(leg.leg_id, R_c[1][:2])
        foot_x += roll_vec[0]  + pitch_vec[0]
        foot_y += roll_vec[1]  + pitch_vec[1]
        foot_z += R_c[0][2]   + R_c[1][2]

    # Yaw correction applied in both swing and stance
    yaw_vec = transformLegtoBody(leg.leg_id, R_c[2][:2])
    foot_x += yaw_vec[0]
    foot_y += yaw_vec[1]

    return (foot_x, foot_y, foot_z)


def calculate_balance_xyz(leg: LegState, pitch: float, roll: float) -> tuple:
    """
    Computes a stationary balance correction foot position (x, y, z).
    Used when a leg is not stepping — keeps the body level using IMU PID output.
    Ported from legacy leg.py balance() — math identical, hardware references removed.

    Only roll and pitch are applied (no yaw correction for a stationary leg).

    Args:
        leg:   LegState for this leg
        pitch: PID pitch correction angle (degrees)
        roll:  PID roll correction angle (degrees)

    Returns:
        (x, y, z) corrected foot position in body frame (mm)
    """
    R_c = R(leg.offset, leg.offset_angle, roll, pitch)
    roll_vec  = transformLegtoBody(leg.leg_id, R_c[0][:2])
    pitch_vec = transformLegtoBody(leg.leg_id, R_c[1][:2])
    foot_x = x_offset + roll_vec[0]  + pitch_vec[0]
    foot_y = y_offset + roll_vec[1]  + pitch_vec[1]
    foot_z = z_offset + R_c[0][2]   + R_c[1][2]
    return (foot_x, foot_y, foot_z)