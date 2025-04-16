# Vole-Machine Simulation System

A simplified CPU architecture simulation implemented in C++, featuring registers, memory, an ALU, control unit, and a user interface for instruction loading, execution, and state visualization.

---

## Overview

This project models a basic CPU with the following core modules:

- **Registers:** 16 general-purpose registers.
- **Memory:** 256 byte-addressable locations.
- **ALU:** Performs arithmetic, logical, and floating-point operations.
- **Control Unit:** Decodes and executes instructions.
- **MainUI:** Provides an interactive menu for loading instructions, executing them, and viewing system states.

---

## Features

- Load instructions from a file or manual input.
- Execute instructions step-by-step.
- Visualize register contents, memory, program counter (PC), and instruction register (IR).
- Support for floating-point conversions and bitwise operations.
- Wrap-around memory addressing based on user-defined start location.
- Error handling for invalid inputs and instructions.

---

## Project Structure & Files

| File Name | Description |  
| --- | --- |  
| `Register.cpp` / `Register.h` | Manages 16 registers, get/set operations, display |  
| `Memory.cpp` / `Memory.h` | Simulates 256 memory locations, read/write, display |  
| `ALU.cpp` / `ALU.h` | Performs arithmetic, logical, floating-point conversions |  
| `Control_Unit.cpp` / `Control_Unit.h` | Decodes instructions, controls data flow |  
| `CPU.cpp` / `CPU.h` | Integrates all modules, manages instruction flow |  
| `MainUI.cpp` / `MainUI.h` | User interface for interaction and visualization |  
| `main.cpp` | Entry point, initializes system and runs menu |


---

## Usage Instructions

1. **Start the Program**  
   Run the executable to initialize the CPU simulation environment.

2. **Set Memory Start Location**  
   Input a start address (1–255) for memory addressing.

3. **Load Instructions**  
   - From a file: Provide a filename containing 4-hex-character instructions, each on a new line.  
   - Manually: Enter instructions one by one; end with `C000` (HALT instruction).

4. **Execute Instructions**  
   The system fetches, decodes, and executes instructions sequentially, updating registers, memory, PC, and IR.

5. **View System State**  
   Use menu options to display registers, memory, PC, IR, or all combined.

6. **Stop the Program**  
   Exit at any time via the menu.

---

## Important Notes

- Instructions must be exactly 4 hexadecimal characters (e.g., `1A2B`).
- The HALT instruction `C000` stops instruction input and execution.
- Memory addresses wrap around based on the start location and total memory size.
- Floating-point conversions use custom formats; ensure correct input.
- Always keep the README updated to reflect code changes for consistency.

---
