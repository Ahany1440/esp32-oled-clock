# 🕰️ ESP32 OLED Clock – Analog + Digital + Date

[![PlatformIO](https://img.shields.io/badge/PlatformIO-ESP32-orange)](https://platformio.org/)
[![Arduino](https://img.shields.io/badge/Arduino-C%2B%2B-blue)](https://www.arduino.cc/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green)](LICENSE)

A beautiful **triple‑display clock** for the ESP32 and SSD1306 OLED.  
Shows an **analog clock face**, large **digital time (HH:MM:SS)**, and the **date (DD/MM/YYYY)**.  
Automatically syncs time via **NTP** over Wi‑Fi – accurate and drift‑free.

![Clock Demo](docs/clock_demo.jpg) *(add your own photo)*

---

## ✨ Features

- ⏰ **Analog clock** – smooth hands, tick marks, centered face.
- 🖥️ **Digital time** – 24‑hour format, placed in the top‑right corner.
- 📅 **Date display** – bottom‑left, never overlaps the clock.
- 🌐 **Wi‑Fi + NTP** – fetches precise UTC time and applies your local offset.
- 🧭 **Timezone configurable** – easily change for any region (supports DST).
- 🔁 **Auto‑refresh** – updates every second.

---

## 🧰 Hardware Required

| Component | Quantity | Notes |
|-----------|----------|-------|
| ESP32 Dev Board | 1 | (e.g., NodeMCU‑32S, ESP‑WROOM‑32) |
| SSD1306 OLED (128×64, I2C) | 1 | Address 0x3C (or 0x3D) |
| Breadboard + jumper wires | few | |

### 📡 Wiring (I2C)

| OLED Pin | ESP32 Pin |
|----------|-----------|
| VCC      | 3.3V      |
| GND      | GND       |
| SCL      | GPIO 22   |
| SDA      | GPIO 21   |

*(If your OLED uses a different I2C address, change `SCREEN_ADDRESS` in the code.)*

---

## 🚀 Getting Started

### 1. Install PlatformIO (if you haven't)

```bash
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
export PATH="$HOME/.local/bin:$PATH"   # add to ~/.bashrc if desired
