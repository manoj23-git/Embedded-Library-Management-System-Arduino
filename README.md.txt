# 📚 Embedded Library Management System (Arduino)

## 📌 Project Overview
This project implements a **mini embedded library management system** using an **Arduino Uno**, **16×2 I2C LCD**, **4×4 keypad**, and **EEPROM** for permanent data storage.

The system allows users to:
- ➕ Add new books  
- 📖 View stored books with **next/previous navigation**  
- ❌ Delete the last stored book  
- 🔍 Search books by **title**  

It demonstrates **real embedded system concepts** such as:
- Human-Machine Interface (LCD + Keypad)
- Non-volatile memory handling using EEPROM
- Menu-driven embedded programming
- Structured data storage with C structures

---

## 🛠️ Hardware Components
- Arduino Uno  
- 16×2 LCD with I2C module  
- 4×4 Matrix Keypad  
- Jumper wires / Breadboard  

---

## 💻 Software & Tools
- Arduino Embedded C  
- Wokwi Arduino Simulator  
- VS Code / Arduino IDE  
- Git & GitHub  

---

## ⚙️ Features
- EEPROM-based **permanent book storage**
- **Menu-driven LCD interface**
- **Navigation controls** using keypad buttons
- **Search functionality** for quick retrieval
- Designed as a **college mini-project in Embedded Systems**

---

## ▶️ How to Run the Project

### 🔹 Option 1 — Wokwi Simulation
1. Open the Wokwi project link.
2. Click **Start Simulation**.
3. Use keypad:
   - `1` → Add Book  
   - `2` → View Books (`A` next, `B` previous, `*` exit)  
   - `3` → Delete Book  
   - `4` → Search by Title  

### 🔹 Option 2 — Real Arduino Hardware
1. Connect LCD and keypad to Arduino as per circuit diagram.
2. Upload `sketch.ino` using **Arduino IDE**.
3. Power the Arduino and operate using keypad.

---

## 🔌 Circuit Connections

### LCD (I2C)
| LCD Pin | Arduino |
|---------|---------|
| VCC     |   5V    |
| GND     |   GND   |
| SDA     |   A4    |
| SCL     |   A5    |

### Keypad
| Keypad Pin | Arduino Pin |
|------------|-------------|
|   R1–R4    |  9, 8, 7, 6 |
|   C1–C4    |  5, 4, 3, 2 |

---