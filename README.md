## System Architecture

```
Raspberry Pi (Python + ROS)
│
│  High-level planning
│  - gait generation
│  - body dynamics
│  - state machine
│
│  Sends desired leg positions
▼
Communication Layer (UART)
▼
ESP32 (C++ PlatformIO)
│
│  Low-level control
│  - inverse kinematics
│  - servo driver
│  - realtime loop
│
▼
ST3215 Motors
```

## Directory Structure

```
hexapod
│
├── firmware (ESP32 code)
│   ├── platformio.ini
│   └── src
│       ├── drivers
│       │   └── ST3215
│       │       ├── ST3215_driver.cpp
│       │       ├── ST3215_driver.h
│       │       ├── ST3215_protocol.cpp
│       │       └── ST3215_protocol.h
│       │
│       ├── kinematics
│       │   ├── leg.cpp
│       │   └── leg.h
│       │
│       ├── communication
│       │   ├── serial_protocol.cpp
│       │   └── serial_protocol.h
│       │
│       └── main.cpp
│
├── rpi
│   └── hexapod_control
│       ├── gait.py
│       ├── spider.py
│       ├── parameter.py
│       ├── imu_node.py
│       └── esp32_interface.py
│
└── ros
    └── hexapod_ros
```