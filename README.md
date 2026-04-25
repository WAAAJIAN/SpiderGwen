# SpiderGwen

A six-legged autonomous hexapod robot with computer vision-guided locomotion, built on a dual-processor architecture using a Raspberry Pi and ESP32-S3.

---

## Overview

SpiderGwen is a hexapod robot designed for autonomous navigation using computer vision. The system splits responsibilities across two processors:

- **Raspberry Pi** — high-level computation: computer vision, path planning, gait decisions
- **ESP32-S3-WROOM-1** — low-level real-time control: servo motor communication, battery management, hardware safety

The RPi sends high-level movement commands to the ESP32 over UART. The ESP32 executes them in real time across 18 ST3215 servo motors (6 legs × 3 joints each).

---

## Repository Structure

```
SpiderGwen
├── README.md
├── docs
│   ├── electrical
│   ├── firmware
│   └── mechanical
├── firmware
│   ├── include
│   │   └── main.h
│   ├── platformio.ini
│   └── src
│       ├── lib
│       │   ├── Battery
│       │   ├── Leg_kinematics
│       │   │   ├── leg_kinematics_config.h
│       │   │   ├── leg_kinematics.cpp
│       │   │   └── leg_kinematics.h
│       │   ├── Spider
│       │   │   ├── spider.cpp
│       │   │   └── spider.h
│       │   └── ST3215_servo
│       │       ├── ST3215_cmd.h
│       │       ├── ST3215_driver.cpp
│       │       ├── ST3215_driver.h
│       │       ├── ST3215_protocol.cpp
│       │       ├── ST3215_protocol.h
│       │       └── ST3215_registers.h
│       └── main.cpp
├── legacy
│   ├── cy-code-v1
│   ├── cy-code-v2
│   ├── miscellaneous
│   ├── hexapod_msgs
│   └── ws-code-v1
├── ros2_ws
│   ├── hexapod_ros
│   │   └── hexapod_ros
│   │       ├── config
│   │       │   └── pid_params.yaml
│   │       ├── launch
│   │       │   └── hexapod.launch.py
│   │       ├── resource
│   │       │   └── hexapod_ros
│   │       ├── package.xml
│   │       ├── setup.cfg
│   │       ├── setup.py
│   │       ├── src
│   │       │   ├── __init__.py
│   │       │   ├── esp32_interface.py
│   │       │   ├── gyroscope.py
│   │       │   ├── hexapod_controller.py
│   │       │   ├── hexapod_teleop.py
│   │       │   ├── imu_node.py
│   │       │   ├── leg_state.py
│   │       │   ├── parameter.py
│   │       │   ├── spider.py
│   │       └── test
│   │           ├── test_copyright.py
│   │           ├── test_flake8.py
│   │           └── test_pep257.py
│   └── Readme
└── SpiderGwen.code-workspace
```

## Firmware

The ESP32-S3 firmware is built with [PlatformIO](https://platformio.org/) using the Arduino framework.

## ROS2 Workspace

The ROS2 workspace runs on the Raspberry Pi and handles high-level control.

## Legacy Code

The `legacy/` directory contains previous versions kept for reference:

## Roadmap

- [x] ST3215 servo protocol driver
- [x] RS485 half-duplex communication
- [x] Sync write for coordinated multi-servo motion
- [ ] Battery management library
- [ ] ESP32 ↔ RPi UART protocol 
- [x] ROS2 gait controller 
- [ ] Computer vision navigation

---

## License

MIT License

Copyright (c) 2026 SpiderGwen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---
All firmware and ROS library are co-authored by Lim Wei Jian, Teh Wei Sheng and
Song Cheng Yan, Copyright (c) 2026.