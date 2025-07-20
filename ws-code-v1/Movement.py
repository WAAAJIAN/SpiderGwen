import numpy as np
import time
from Spider import Spider
from leg_config import Config as cfg
from ForwardKinematics import compute_foot_position_from_origin

class GaitController:
    def __init__(self, spider_robot):
        """
        :param spider_robot: An instance of the Spider class.
        """
        self.robot = spider_robot
        self.tripod_group_1 = ['L1', 'R2', 'L3']
        self.tripod_group_2 = ['R1', 'L2', 'R3']

        # --- Gait Parameters ---
        self.step_length = 80.0   # How far each leg moves forward in a step (mm)
        self.step_height = 40.0   # How high a leg lifts off the ground (mm)
        self.body_height = 100.0  # Desired z-height of the robot's body
        self.gait_speed = 1     # Time in seconds to complete one full step cycle

        # Calculate and store the neutral ("home") position for each foot
        self.home_positions = self.calculate_home_positions()

    def calculate_home_positions(self):
        """
        Calculates the default XYZ position for each foot based on the initial
        joint angles in the config. This is the "neutral stance".
        """
        # We can use your existing FK function for this
        print("Calculating neutral foot positions...")
        initial_foot_positions = compute_foot_position_from_origin()
        # Set the Z-coordinate for all home positions to the desired negative body height
        for leg in initial_foot_positions:
            initial_foot_positions[leg][2] = -self.body_height
        return initial_foot_positions

    def tripod_gait(self, vx, vy, v_yaw):
        """
        Executes a continuous tripod gait.
        :param vx: Forward/backward velocity (e.g., -1.0 to 1.0)
        :param vy: Left/right strafing velocity (e.g., -1.0 to 1.0)
        :param v_yaw: Rotational (yaw) velocity (e.g., -1.0 to 1.0)
        """
        # The number of discrete points in a single step trajectory
        num_ticks = 20  
        
        while True:
            # === PHASE 1: Swing Group 1, Stance Group 2 ===
            for tick in range(num_ticks):
                self.execute_gait_tick(self.tripod_group_1, self.tripod_group_2, tick, num_ticks, vx, vy, v_yaw)
                time.sleep(self.gait_speed / (2 * num_ticks))

            # === PHASE 2: Swing Group 2, Stance Group 1 ===
            for tick in range(num_ticks):
                self.execute_gait_tick(self.tripod_group_2, self.tripod_group_1, tick, num_ticks, vx, vy, v_yaw)
                time.sleep(self.gait_speed / (2 * num_ticks))


    def execute_gait_tick(self, swing_group, stance_group, tick, num_ticks, vx, vy, v_yaw):
        """
        Calculates and executes the target position for all 6 legs for a single
        "tick" of the gait cycle.
        """
        # --- SWING GROUP ---
        # A simple trajectory for the swing phase is a half-sine wave for the Z-axis
        # and linear movement for X and Y.
        swing_phase = tick / (num_ticks - 1) # Varies from 0.0 to 1.0
        
        # Calculate how far the foot should move in this tick
        x_delta = vx * self.step_length
        y_delta = vy * self.step_length

        for leg in swing_group:
            # The foot starts at its backward-most position and moves to its forward-most
            start_pos = self.home_positions[leg] - np.array([x_delta / 2, y_delta / 2, 0])
            end_pos = self.home_positions[leg] + np.array([x_delta / 2, y_delta / 2, 0])
            
            # Linear interpolation for X and Y
            target_x = start_pos[0] + (end_pos[0] - start_pos[0]) * swing_phase
            target_y = start_pos[1] + (end_pos[1] - start_pos[1]) * swing_phase
            
            # Sinusoidal interpolation for Z (step height)
            target_z = -self.body_height + self.step_height * np.sin(swing_phase * np.pi)

            # Apply IK to the calculated target position
            getattr(self.robot, leg).IK(target_x, target_y, target_z)

        # --- STANCE GROUP ---
        # The legs on the ground move in the opposite direction of the body's velocity
        stance_phase = 1.0 - swing_phase # Varies from 1.0 down to 0.0
        
        for leg in stance_group:
            # The foot starts at its forward-most position and moves to its backward-most
            start_pos = self.home_positions[leg] + np.array([x_delta / 2, y_delta / 2, 0])
            end_pos = self.home_positions[leg] - np.array([x_delta / 2, y_delta / 2, 0])

            # Linear interpolation for X and Y
            target_x = start_pos[0] + (end_pos[0] - start_pos[0]) * swing_phase
            target_y = start_pos[1] + (end_pos[1] - start_pos[1]) * swing_phase

            # Stance legs stay on the ground
            target_z = -self.body_height

            # Apply IK to the calculated target position
            getattr(self.robot, leg).IK(target_x, target_y, target_z)

        # Move all servos to their new target positions simultaneously
        self.robot.move()

def main():
    # 1. Instantiate the robot
    gwen = Spider()

    # 2. Instantiate the Gait Controller
    gait_controller = GaitController(gwen)

    try:
        print("Starting tripod gait...")
        # Walk forward: vx=1.0, vy=0.0, v_yaw=0.0
        gait_controller.tripod_gait(vx=1.0, vy=0.0, v_yaw=0.0)
        
    except KeyboardInterrupt:
        print("\nGait stopped by user.")
    finally:
        # Clean up and release servos
        gwen.clean()

main()