# 🧹 Flying Broomstick Management System

This project implements a **Flying Broomstick Management System** for the *Office of Transportation, Ministry of Magic*. The system manages thousands of broomstick license records efficiently using a **Red-Black Tree** as the core data structure.  

It supports operations like registration, lookup, removal, range search, and revenue calculation — all based on license plate data.

---

## 📘 Overview

Each broomstick must have a **4-character license plate**, where each character is either a capital letter (`A–Z`) or a digit (`0–9`).  
The system allows both **customized** and **randomly generated** license plates, maintaining them in lexicographical order using a Red-Black Tree for efficient insertion, deletion, and lookup.

Annual fees:
- Standard registration: **4 Galleons/year**
- Custom plate surcharge: **+3 Galleons/year**

---

## ⚙️ Features

- **Add Custom Plate:** `addLicence(plateNum)`  
  Registers a new custom license plate.
- **Add Random Plate:** `addLicence()`  
  Generates a new unused random plate and registers it.
- **Remove Plate:** `dropLicence(plateNum)`  
  Deletes an existing license plate.
- **Lookup Plate:** `lookupLicence(plateNum)`  
  Checks if a plate exists in the system.
- **Find Previous/Next Plate:** `lookupPrev(plateNum)` / `lookupNext(plateNum)`
- **Range Lookup:** `lookupRange(lo, hi)`  
  Lists all plates between two values.
- **Revenue Report:** `revenue()`  
  Displays total annual revenue based on all active registrations.
- **Quit:** `quit()`  
  Exits the program safely.

---

## 🧩 Implementation Details

- **Language:** C++  
- **Data Structure:** Red-Black Tree implemented **from scratch** (no STL map/set used).  
- **Input/Output:**  
  - Input commands are read from a text file.  
  - Output is written to a file named:  
    ```
    <inputFileName>_output.txt
    ```
- **Design Highlights:**
  - Node structure stores plate number and color (RED/BLACK).
  - Rotation and balancing operations maintain RBT properties.
  - Custom string comparison ensures numbers come before letters in lexicographic order.
  - Revenue calculation tracks both standard and custom fees dynamically.

---

## 🧱 File Structure

```
📦 FlyingBroomstickManagement
 ┣ 📜 plateMgmt.cpp
 ┣ 📜 Makefile
 ┣ 📜 README.md
 ┣ 📜 ProjectReport.pdf
 ┣ 📜 input_sample.txt
 ┗ 📜 output_sample.txt
```

---

## 🛠️ Build and Run Instructions

### 🔧 Compilation
To compile the project using the provided **Makefile**, run:
```bash
make
```
This creates an executable named `plateMgmt`.

### ▶️ Execution
Run the program with an input file:
```bash
./plateMgmt input.txt
```
The program will read commands from `input.txt` and write results to:
```
input_output.txt
```

### 🧹 Clean Build Files
To remove generated object and executable files:
```bash
make clean
```

---

## 📄 Example Input

```
addLicence(AB12)
addLicence()
lookupLicence(AB12)
lookupPrev(AB12)
lookupRange(00AA, ZZ99)
revenue()
quit()
```

### Example Output

```
AB12 registered successfully.
Q9L3 created and registered successfully.
AB12 exists.
AB12’s prev is 009Z.
plate numbers between 00AA and ZZ99: 009Z, AB12, Q9L3.
Current annual revenue is 11 Galleons.
```

---

## 🧑‍💻 Author

**Name:** `<NAME>`  
**UFID:** `<UFID>`  
**Course:** COP5536 – Data Structures and Algorithms  
**Semester:** Spring 2025  

---

## 🏆 Acknowledgments

This project was developed as part of the **COP5536 Programming Project** at the University of Florida.  
Special thanks to the course staff for providing the problem specification and grading guidelines.

---

## 📜 License

This project is released for academic and educational use only. Redistribution or plagiarism is strictly prohibited.
