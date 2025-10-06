# 🧹 Flying Broomstick Management System

This project implements a **Flying Broomstick Management System** for the *Office of Transportation, Ministry of Magic*. The system manages thousands of broomstick license records efficiently using a **Red-Black Tree** as the core data structure.  

It supports operations like registration, lookup, removal, range search, and revenue calculation — all based on license plate data.

---

## 📘 Overview

Each broomstick must have a **4-character license plate**, where each character is either a capital letter (`A–Z`) or a digit (`0–9`).  
The system allows both **customized** and **randomly generated** license plates, maintaining them in lexicographical order using a Red-Black Tree for efficient insertion, deletion, and lookup.

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
 ┣ 📜 Makefile
 ┣ 📜 main.cpp
 ┣ 📜 rbt.cpp
 ┣ 📜 rbt.h
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
input-output.txt
```

### 🧹 Clean Build Files
To remove generated object and executable files:
```bash
make clean
```

---

## 📄 Example Input 1

```
addLicence()
addLicence()
addLicence()
revenue()
quit()
```

### Example Output 1

```
<random_plate_num> created and registered successfully.
<random_plate_num> created and registered successfully.
<random_plate_num> created and registered successfully.
Current annual revenue is 12 Galleons.
```

## 📄 Example Input 2

```
addLicence(1111)
addLicence(2222)
addLicence(3333)
addLicence(AAAA)
addLicence(4444)
addLicence(3333)
dropLicence(4444)
dropLicence(1234)
lookupLicence(2222)
lookupLicence(1234)
lookupLicence(4444)
lookupPrev(2222)
lookupNext(3333)
lookupRange(1234, 3333)
revenue()
quit()
```

### Example Output 2

```
1111 registered successfully.
2222 registered successfully.
3333 registered successfully.
AAAA registered successfully.
4444 registered successfully.
Failed to register 3333: already exists.
4444 removed successfully.
Failed to remove 1234: does not exist.
2222 exists.
1234 does not exist.
4444 does not exist.
2222’s prev is 1111.
3333’s next is AAAA.
Plate numbers between 1234 and 3333: 2222, 3333.
current annual revenue is 28 Galleons.
```

---

## 🧑‍💻 Author

**Name:** `Radhey Sharma`    
**Course:** COP5536 – Data Structures and Algorithms  
**Semester:** Spring 2025  

---

## 🏆 Acknowledgments

This project was developed as part of the **COP5536 Programming Project** at the University of Florida.  
Special thanks to the course staff for providing the problem specification and grading guidelines.

---

## 📜 License

This project is released for academic and educational use only. Redistribution or plagiarism is strictly prohibited.
