# SpiderGwen 🕷️

A six-legged autonomous hexapod robot with computer vision-guided locomotion, built on a dual-processor architecture using a Raspberry Pi and ESP32-S3.

---

## Overview

SpiderGwen is a hexapod robot designed for autonomous navigation using computer vision. The system splits responsibilities across two processors:

- **Raspberry Pi** — high-level computation: computer vision, path planning, gait decisions
- **ESP32-S3** — low-level real-time control: servo motor communication, battery management, hardware safety

The RPi sends high-level movement commands to the ESP32 over UART. The ESP32 executes them in real time across 18 ST3215 servo motors (6 legs × 3 joints each).

---

## Repository Structure

```
SpiderGwen/
├── firmware/               # ESP32-S3 — PlatformIO project
│   ├── platformio.ini
│   ├── include/
│   │   └── main.h
│   └── src/
│       ├── main.cpp
│       └── lib/
│           ├── ST3215_servo/   # ST3215 servo driver library
│           │   ├── ST3215_cmd.h
│           │   ├── ST3215_registers.h
│           │   ├── ST3215_protocol.h/cpp
│           │   └── ST3215_driver.h/cpp
│           └── Battery/        # Battery management library (WIP)
│
├── ros2_ws/                # Raspberry Pi — ROS2 workspace
│   └── src/
│       ├── hexapod_msgs/   # Custom ROS2 message and action definitions
│       │   ├── msg/
│       │   └── action/
│       └── hexapod_ros/    # Main ROS2 package
│           ├── config/
│           ├── launch/
│           └── src/
│
├── legacy/                 # Previous iterations (kept for reference)
│   ├── cy-code-v1/         # Original Python prototype
│   ├── cy-code-v2/         # C++ rewrite attempt
│   └── ws-code-v1/         # Kinematics experiments
│
├── docs/
│   ├── electrical/
│   ├── firmware/
│   └── mechanical/
│
└── README.md
```

---

## Hardware

| Component | Details |
|---|---|
| Main compute | Raspberry Pi |
| Microcontroller | ESP32-S3-DevKitC-1 |
| Servo motors | ST3215 × 18 (6 legs × 3 joints) |
| Communication bus | RS485 half-duplex UART |
| RPi ↔ ESP32 | UART |

### Pin Assignment (ESP32-S3)

| Pin | Function |
|---|---|
| TX — GPIO 17 | RS485 transmit |
| RX — GPIO 18 | RS485 receive |

---

## Firmware

The ESP32-S3 firmware is built with [PlatformIO](https://platformio.org/) using the Arduino framework.

### Build & Flash

```bash
# Open the firmware workspace
cd firmware

# Build
pio run

# Flash
pio run --target upload

# Monitor serial output
pio device monitor
```

### ST3215 Servo Library

A custom driver for the ST3215 servo motor using the Feetech serial protocol over RS485.

| File | Responsibility |
|---|---|
| `ST3215_cmd.h` | Instruction set enum (`PING`, `READ`, `WRITE`, `SYNC_WRITE`, etc.) |
| `ST3215_registers.h` | Full register map enum (EEPROM + SRAM) |
| `ST3215_protocol.h/cpp` | Packet construction, serial send/receive, checksum |
| `ST3215_driver.h/cpp` | High-level API (set angle, read speed, sync write, etc.) |

Key driver API:

```cpp
driver.ping(id);
driver.set_angle(id, angle);           // degrees
driver.set_speed(id, step_speed);      // steps/s
driver.set_angle_speed_sync(ids, angles, speeds, num_servos);
driver.read_angle(id, &angle);
driver.read_temperature(id, &temp);
driver.read_status(id, &status);
driver.set_torque(id, true/false);
```

---

## ROS2 Workspace

The ROS2 workspace runs on the Raspberry Pi and handles high-level control.

### Packages

| Package | Description |
|---|---|
| `hexapod_msgs` | Custom message types: `ServoTarget`, `ServoTargetArray`, `Walk.action`, `Servo.action` |
| `hexapod_ros` | Main controller: gait planning, IK, teleop, IMU integration |

### Build

```bash
cd ros2_ws
colcon build
source install/setup.bash
```

### Launch

```bash
ros2 launch hexapod_ros hexapod.launch.py
```

---

## System Architecture

```
┌─────────────────────────────────────┐
│           Raspberry Pi              │
│  ┌─────────────┐  ┌──────────────┐  │
│  │  CV Node    │  │  Gait Node   │  │
│  │ (OpenCV /   │→ │ (IK + path   │  │
│  │  inference) │  │  planning)   │  │
│  └─────────────┘  └──────┬───────┘  │
│                          │ UART     │
└──────────────────────────┼──────────┘
                           │
┌──────────────────────────┼──────────┐
│           ESP32-S3       │          │
│  ┌───────────────────────▼───────┐  │
│  │  Core 0 — UART bridge        │  │
│  │  Receives RPi commands        │  │
│  │  Sends telemetry back         │  │
│  └───────────────┬───────────────┘  │
│                  │ FreeRTOS Queue   │
│  ┌───────────────▼───────────────┐  │
│  │  Core 1 — Servo execution    │  │
│  │  sync_write to 18 servos      │  │
│  │  Battery monitoring           │  │
│  │  Watchdog / safety shutdown   │  │
│  └───────────────────────────────┘  │
│                  │ RS485            │
└──────────────────┼──────────────────┘
                   │
        ┌──────────┴──────────┐
        │   18× ST3215        │
        │   Servo Motors      │
        └─────────────────────┘
```

---

## Legacy Code

The `legacy/` directory contains previous versions kept for reference:

| Directory | Description |
|---|---|
| `cy-code-v1/` | Original Python prototype using Maestro servo controller |
| `cy-code-v2/` | C++ rewrite of kinematics |
| `ws-code-v1/` | Forward/inverse kinematics experiments |

These are not part of the active system.

---

## Roadmap

- [x] ST3215 servo protocol driver
- [x] RS485 half-duplex communication
- [x] Sync write for coordinated multi-servo motion
- [ ] Battery management library
- [ ] FreeRTOS dual-core task structure
- [ ] ESP32 ↔ RPi UART protocol
- [ ] ROS2 gait controller (port from legacy)
- [ ] Computer vision navigation

---

## License

Open source. Free to use, modify, and distribute with appropriate attribution.