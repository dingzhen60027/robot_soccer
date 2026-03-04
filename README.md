# 5v5 Robot Soccer System

A complete **5v5 robot soccer software stack** integrating perception, strategy, communication, GUI, and simulation.

This project uses:

* **ROS 2** for distributed robotics middleware
* **Qt** for the operator GUI
* **Isaac Sim** for high-fidelity simulation and testing

The system is designed for real-time multi-robot coordination and can run in both **simulation** and **real robot** modes.

---

## Features

* ✅ Multi-robot (5v5) architecture
* ✅ Vision processing pipeline
* ✅ Strategy & decision making
* ✅ Real-time robot communication
* ✅ Qt-based control GUI
* ✅ Isaac Sim integration
* ✅ ROS 2 modular design
* ✅ Simulation ↔ real robot consistency

---

## Overview

```
Isaac Sim
   │  (ROS 2 Bridge: camera / ground truth / physics)
   ▼
Vision → Vision processed results → Strategy → Communication → Robots
                                   ▲
                                   │
                                  GUI

```
### Data Flow

* **Isaac Sim**

  * publishes simulated camera images via ROS 2 bridge
  * publishes robot & ball ground truth (optional)
  * receives robot command topics
* **Vision**

  * consumes real-time images from Isaac Sim or real cameras
* **Strategy**

  * computes team behaviors
* **Communication**

  * sends commands to robots **or back to Isaac Sim robots**
* **GUI**

  * monitors and controls the full pipeline

### Modules

| Module        | Description                         |
| ------------- | ----------------------------------- |
| Vision        | Ball & robot detection and tracking |
| Strategy      | Team tactics and behavior planning  |
| Communication | Robot command transmission          |
| GUI (Qt)      | Operator interface                  |
| Isaac Sim     | Physics-based simulation            |

---

## Repository Structure

```
.
├── src/
│   ├── vision/
│   ├── strategy/
│   ├── communication_robosoccer/
│   ├── message_interface_robosoccer/launch/launch.py
│   └── gui_robosoccer/
├── isaac_sim/
└── README.md
```


---

## 🔧 Requirements

### System

* Ubuntu 22.04 (recommended)
* ROS 2 Humble 
* Qt 5 >= 14.0
* NVIDIA GPU (for Isaac Sim) 

### ROS 2 Dependencies

Install ROS 2 first:

```bash
sudo apt install ros-humble-desktop
```

Install additional packages as needed:

```bash
rosdep install --from-paths src --ignore-src -r -y
```

---

## ⚙️ Build

```bash
mkdir -p ~/robosoccer_ws
cd ~/robosoccer_ws

# clone repo
git clone <your-repo-url> src

# install deps
rosdep install --from-paths src --ignore-src -r -y

# build
colcon build --symlink-install

# source
source install/setup.bash
```

---

## 🖥️ Run the System

### 1️⃣ Launch Core System

```bash
ros2 launch gui_robosoccer launch.py
```


### 2️⃣ Run Isaac Sim

Start Isaac Sim and load the provided scene:

```
isaac_sim/scenes/robosoccer_5v5.usd
```

---

## 🎮 GUI Overview

The Qt GUI provides:

* 🟢 Real-time field visualization
* 🤖 Robot status monitoring
* 🎯 Strategy control
* 📡 Communication diagnostics
* ▶️ Simulation control
<img width="1820" height="1055" alt="image" src="https://github.com/user-attachments/assets/c42548a7-e24d-4aa7-b8d1-aa1eb246bed1" />

---

## 🧪 Simulation with Isaac Sim

The project supports full closed-loop simulation:

* Physics-accurate robots
* Camera simulation
* Multi-robot interaction
* Strategy validation

<img width="1460" height="955" alt="image" src="https://github.com/user-attachments/assets/c75a8309-9f59-44c9-b126-c7d4b4d79b43" />

### Workflow

1. Launch Isaac Sim
2. Start ROS 2 bridge
3. Run soccer stack
4. Observe in GUI

---

## 🛠️ Development Notes

* Built with ROS 2 component architecture
* Real-time friendly design
* Modular strategy framework
* Supports both simulation and hardware

---

## 📌 TODO / Roadmap

* [ ] Improve multi-robot coordination
* [ ] Add referee box support
* [ ] Hardware bring-up
* [ ] Auto-tuning for strategy
* [ ] CI pipeline

---

## 🤝 Contributing

PRs and issues are welcome.

Please:

* follow ROS 2 style
* run `colcon build` before PR
* add tests when possible

---

