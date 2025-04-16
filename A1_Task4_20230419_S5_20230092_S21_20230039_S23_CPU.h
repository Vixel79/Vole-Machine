/* 20230419 S5
* 20230093 S21
 * 20230039 S23
 */

#ifndef A1_Task4_20230419_S5_20230092_S21_20230039_S23_CPU_H
#define A1_Task4_20230419_S5_20230092_S21_20230039_S23_CPU_H

#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Register.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU.h"
#include <bits/stdc++.h>
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Control_Unit.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Memory.h"

using namespace std;

class CPU {
    Register *reg = new Register();
    Memory *memory = new Memory();
    ALU *alu = new ALU();
    string IR;         // Instruction Register
    int PC = 0;
public:

    // Load an instruction into memory at the current PC and increment PC
    void loadNextInstruction(const string &instruction) {
        if (instruction.length() == 4) {
            // Split the 4-digit instruction into two parts
            string firstHalf = instruction.substr(0, 2);  // First two characters
            string secondHalf = instruction.substr(2, 2); // Last two characters

            // Store in two consecutive memory cells starting at PC
            memory->set(PC, firstHalf);        // Store the first half at PC
            memory->set(PC + 1, secondHalf);   // Store the second half at PC+1

            cout << "Instruction [" << instruction << "] Stored " << "\n";
            memory->display_memory();  // Show the current state of memory

            // Update the Instruction Register
            IR = instruction;

        } else {
            cout << "Invalid instruction format. Please enter a 4 hex digit instruction.\n";
        }

        // Increment PC by 2 to point to the next instruction location
        PC += 2;
    }


    // Get the current instruction in the Instruction Register
    [[nodiscard]] string getInstructionRegister() const {
        return IR;
    }

    // Get the current value of the Program Counter
    [[nodiscard]] int getPC() const {
        return PC;
    }

    // Set the Program Counter to a specific value
    void setPC(const int &newPC) {
        PC = newPC;
    }
};

#endif //A1_Task4_20230419_S5_20230092_S21_20230039_S23_CPU_H
