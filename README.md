# 🚗 SmartPark - Smart Parking Management System
> **This project was developed as part of the Advanced Programming (C) Workshop at HIT.**
**SmartPark** is a console-based parking management application written in **C**.
It simulates a multi-floor parking facility, managing parking spots efficiently using **Linked Lists** and dynamic memory allocation. The system supports real-time vehicle entry/exit and maintains data persistence using text-based file storage.

---

## 📌 Features

* **Automated Spot Allocation:** Automatically finds the first available spot across multiple floors.
* **Multi-Floor Management:** Supports dynamic configuration of floors and spots (Default: 3 Floors).
* **Check-in / Check-out:** Park and release cars using their License Plate Number.
* **Real-Time Status:** View the current occupancy of the entire parking lot.
* **💾 Data Persistence:** Automatically saves and loads the parking state to/from a file (`parking_smart_state.txt`), ensuring data is not lost between sessions.
* **Robust Error Handling:** Manages memory allocation failures and invalid inputs.

---

## 🛠 Technical Implementation

This project demonstrates advanced **C programming** concepts:

* **Data Structures:**
    * **Linked Lists:** Used to manage parking spots dynamically on each floor (`ParkingSpot` struct).
    * **Dynamic Arrays:** Used to manage the floors (`ParkingFloor` array).
* **Memory Management:** Extensive use of `malloc` and `free` to handle resources efficiently without memory leaks.
* **File I/O:** Custom serialization logic to save and parse the parking lot state from a text file.
* **Modular Design:** Separation of logic (`SmartParking.c`) and interface (`main.c`).

---

## 📂 Project Structure

* `main.c` - Entry point. Handles the main menu loop and user input.
* `SmartParking.c` - Core implementation of logic (Park, Release, Save, Load).
* `SmartParking.h` - Header file containing struct definitions and function prototypes.
* `SmartPark.sln` - Visual Studio Solution file.
* `parking_smart_state.txt` - (Generated) Stores the database of parked cars.

---

## 🚀 How to Run

### Prerequisites
* **Windows OS** (Recommended).
* **Visual Studio** (Project allows generic C compilation, but uses Microsoft-safe functions like `scanf_s`).

### Steps
1.  Clone the repository or download the source code.
2.  Open `SmartPark.sln` in Visual Studio.
3.  Build and Run the project (Ctrl + F5).
4.  Use the numbered menu to interact with the system.

---

## 🎮 Usage Example

**Menu Options:**
1.  **Find first available spot:** Checks for the nearest empty spot.
2.  **Reserve a parking spot:** Enter a license plate to park a car.
3.  **Release a parking spot:** Enter a license plate to remove a car.
4.  **Display parking lot state:** Shows all floors and occupied spots.
5.  **Save/Load:** Manually trigger file operations (Auto-save occurs on exit).

---

## 📜 License
This project is provided for educational and portfolio purposes only.


