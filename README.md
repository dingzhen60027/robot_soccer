# ⚽ 5v5 Robot Soccer System

A complete **5v5 robot soccer software stack** integrating perception, strategy, communication, GUI, and simulation.

This project uses:

* **ROS 2** for distributed robotics middleware
* **Qt** for the operator GUI
* **Isaac Sim** for high-fidelity simulation and testing

The system is designed for real-time multi-robot coordination and can run in both **simulation** and **real robot** modes.

---

## 🚀 Features

* ✅ Multi-robot (5v5) architecture
* ✅ Vision processing pipeline
* ✅ Strategy & decision making
* ✅ Real-time robot communication
* ✅ Qt-based control GUI
* ✅ Isaac Sim integration
* ✅ ROS 2 modular design
* ✅ Simulation ↔ real robot consistency

---

## 🧠 System Architecture

```
Vision → World Model → Strategy → Communication → Robots
                         ↓
                        GUI
                         ↓
                     Isaac Sim
```

### Modules

| Module        | Description                         |
| ------------- | ----------------------------------- |
| Vision        | Ball & robot detection and tracking |
| World Model   | State estimation and fusion         |
| Strategy      | Team tactics and behavior planning  |
| Communication | Robot command transmission          |
| GUI (Qt)      | Operator interface                  |
| Isaac Sim     | Physics-based simulation            |

---

## 🏗️ Repository Structure

```
.
├── src/
│   ├── vision/
│   ├── strategy/
│   ├── communication/
│   ├── message_interface_robosoccer/
│   └── gui_qt/
├── isaac_sim/
├── config/
├── launch/
└── README.md
```

> Adjust to match your actual tree.

---

## 🔧 Requirements

### System

* Ubuntu 22.04 (recommended)
* ROS 2 Humble / Iron
* Qt 5 or Qt 6
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
mkdir -p ~/elong_ws
cd ~/elong_ws

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
ros2 launch <your_package> bringup.launch.py
```

---

### 2️⃣ Start Qt GUI

```bash
ros2 run gui_qt soccer_gui
```

---

### 3️⃣ Run Isaac Sim

Start Isaac Sim and load the provided scene:

```
isaac_sim/scenes/robosoccer_5v5.usd
```

Then bridge ROS 2 topics.

---

## 🎮 GUI Overview

The Qt GUI provides:

* 🟢 Real-time field visualization
* 🤖 Robot status monitoring
* 🎯 Strategy control
* 📡 Communication diagnostics
* ▶️ Simulation control

*(Add screenshots here — highly recommended)*

---

## 🔌 ROS 2 Interfaces

### Topics (examples)

| Topic                | Type       | Description        |
| -------------------- | ---------- | ------------------ |
| `/vision/detections` | custom msg | Raw detections     |
| `/world_model`       | custom msg | Fused state        |
| `/robot_commands`    | custom msg | Commands to robots |

---

## 🧪 Simulation with Isaac Sim

The project supports full closed-loop simulation:

* Physics-accurate robots
* Camera simulation
* Multi-robot interaction
* Strategy validation

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

## 📄 License

Specify your license here (MIT / BSD / Apache-2.0 recommended).

---

---

# 👍 Optional upgrades (if you want to look pro)

If you want, I can next help you add:

* 🔥 architecture diagram (very impressive)
* 🔥 ROS graph diagram
* 🔥 multi-robot behavior tree
* 🔥 Isaac Sim bridge diagram
* 🔥 competition-ready README

Just tell me your target (research paper / RoboCup / GitHub showcase).
