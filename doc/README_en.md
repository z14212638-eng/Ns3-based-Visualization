# Ns-3 PPDU Visualizer

[English](README_en.md) | [中文](README_ch.md)

A Qt-based visualization tool for **ns-3 PHY/MAC PPDU activity**, designed to provide **interactive, time-aligned PPDU-level analysis** for wireless simulations.

This project focuses on **PPDU timelines, throughput plots, and custom simulation scenarios**, supporting:
- Node-centric PPDU transmissions
- Channel-centric PPDU transmissions
- PPDU collision indication
- Frame type inspection
- Time range selection with auto-zoom
- Throughput / channel utilization statistics

It is intended as a **research and debugging tool**, not a full simulator or NetAnim replacement.

---

## ✨ Features

- 📊 **PPDU Timeline View**  
  Visualize PPDU transmissions along the time axis in **node view** and **channel view**.

- 🧠 **Lane-based Overlap Layout**  
  Overlapping PPDUs are split into lanes to avoid occlusion, with overlap indicators.

- 🖱 **Rich Interaction**
  - Hover to inspect PPDU details (frame type, duration, fail-reason, node MAC, etc.)
  - Left-drag to pan the timeline
  - Mouse wheel to zoom and adjust time granularity
  - Right-drag to select a time range and compute statistics

- 📐 **Time Range Analysis**
  For a selected interval (requires full-data mode):
  - Channel busy time
  - Idle time
  - Utilization
  - Throughput (Mbps)

- 🪟 **Overlay UI (NetAnim-style)**
  Semi-transparent overlays for:
  - PPDU info
  - Legend
  - Statistics

- 🖼 **Export as Image**  
  Save the current timeline view as PNG/JPG.

---


> ⚠️ **Note**  
> When using the AppImage version, the relative positions of the Qt UI and the ns-3 simulation are not fixed. The user needs to manually set the paths in the UI.

---

## 🔧 Dependencies

- **Qt 6** (Qt 5 may work with minor tweaks)
- **C++17** or newer
- **ns-3.46** or higher
- Linux environment

> ⚠️ **Note**  
> This repo does **not** ship the full ns-3 source. Only contrib modules are included. Please download the full ns-3 source from the [ns-3 official site](https://www.nsnam.org/).

---

## 🚀 Quick Run (Prebuilt)

- **AppImage** (desktop)  
  Run Ns3Visualizer.AppImage to launch the UI.

- **Headless executable package**  

```bash
# download the source code, then navigate to the ns3 root directory
./ns3 configure
./ns3 build
./build/Ns3VisualizerApp

```

---


> The Qt app only handles visualization; it does **not** build or run ns-3.
> If you want to know more about how to use this tool, please refer to the [User Guide](Tutorial_en.md) or [用户指南](Tutorial_ch.md).

---

## 📥 Data Input

PPDU data typically comes from ns-3 trace hooks or custom logs (JSON/CSV).
Each PPDU record usually includes:
- Node/AP identifier
- Start/end time (ns)
- Frame type
- Aggregated MPDU count
- Payload size

---

## 🧪 Project Status

- ✔ PPDU timeline and overlays
- ✔ Time-range statistics
- ✔ Interactive operations
- ⏳ Complex traffic configuration
- ⏳ MLO

---

## 🎯 Design Goals

- Focus on PHY/MAC behavior rather than topology animation
- Nanosecond-level time alignment
- Research-friendly and extensible

---

## 📜 License

Released under the **MIT License**.

---

## 🙋 Authors

- **Kai Zhang**  
  u202414527@hust.edu.cn
- **Chengxiang Mi**  
  michengxiang@hust.edu.cn

---

## ⭐ Acknowledgements

- ns-3 Simulator
- NetAnim (UI inspiration)
- Qt Framework

> If you use this project in research, coursework, or tooling, a citation or mention would be appreciated.
