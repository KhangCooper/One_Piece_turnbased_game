# Enies Lobby Battle Simulation - C++ OOP Project

## 📌 Project Overview
This project is a turn-based battle simulation inspired by the "Enies Lobby" arc from the *One Piece* series. Developed as a core academic assignment for the **Programming Fundamentals (CO1027)** course at the Ho Chi Minh City University of Technology (HCMUT), it demonstrates a solid foundation in low-level system programming and Object-Oriented Programming (OOP) architectures using C++.

The program models a dynamic environment where the Straw Hat Pirates clash with CP9 agents. The simulation tracks real-time battle attributes (HP, Energy, Speed, Morale, Alarm Level) and incorporates tactical environmental assets like the Courthouse, Main Gate, and the Buster Call Ship, which continuously alter the state of the battlefield.

---

## 🛠️ Technical Architecture & OOP Principles Implemented

To demonstrate a rigorous command of fundamental computer science principles, this project was developed **without using high-level STL containers** (such as `std::vector` or `std::list`), relying entirely on raw pointers and manual memory management.

* **Encapsulation & Polymorphism:** * Designed an abstract base class `Character` and `Building` with pure virtual functions (`attack`, `specialSkill`, `applyEffect`).
    * Leveraged dynamic binding to handle polymorphic character mechanics—such as Luffy's dynamic damage multiplier based on health thresholds, Zoro's execute mechanics, and Chopper's targeted healing logic.
* **Custom Data Structures & Memory Management:**
    * Implemented a custom **Singly Linked List (`TurnNode`)** to manage the dynamic runtime sequence and rotation of character turns.
    * Engineered explicit manual object construction and deep memory cleanup inside the class destructors (`~EniesLobbyBattle`) to prevent any potential memory leaks.
* **Architectural State Design:**
    * Utilized a centralized `BattleContext` object to manage globally altered states (e.g., how destroying the Main Gate triggers rescue progress adjustments, or how the Courthouse raises the automated base alarm level).
    * Integrated a file-parsing engine (`loadFromFile`) to dynamically configure the battlefield and character instances from structured text files.

---

## 🚀 Compilation & Execution

### Prerequisites
* A C++ compiler supporting the **C++11 standard** or higher (e.g., GCC/g++).

### Using the Shell Script
A pre-configured shell script (`run.sh`) is provided for automated compilation and execution:

```bash
bash run.sh
