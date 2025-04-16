/* 20230419 S5
* 20230093 S21
 * 20230039 S23
 */

#ifndef A1_Task4_20230419_S5_20230092_S21_20230039_S23_MAINUI_H
#define A1_Task4_20230419_S5_20230092_S21_20230039_S23_MAINUI_H

#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Register.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Control_Unit.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Memory.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_CPU.h"
#include <bits/stdc++.h>

using namespace std;

class MainUI {
    static Memory memory;
    static Register register_;
    static ALU alu;
    static Control_Unit control_unit;
    static CPU cpu;
    static int PC;  // Declaration (no need for initialization here)
public:

    // Static function to validate and load instructions from a file
    static vector<string> fileInstructions(ifstream &inputFile) {
        vector<string> instructions;
        string line;
        while (getline(inputFile, line)) {
            line = toUpperCase(line);
            if (isValidInstruction(line)) {
                instructions.push_back(line);
                if (line == "C000") {  // Stop at HALT command
                    break;
                }
            } else {
                cout << "Invalid instruction in file: " << line << " (must be 4 hex characters).\n";
            }
        }
        return instructions;
    }

    static string toUpperCase(string &str) {
        ranges::transform(str, str.begin(), ::toupper);
        return str;
    }

    static void outputState() {
        string choice;

        // Loop until a valid choice is entered
        while (true) {
            cout << "What would you like to view? \n(A) register\n(B) IR\n(C) PC\n";
            cin >> choice;
            choice = toUpperCase(choice);

            if (choice == "A") {
                register_.display_registers();
                break;
            }
            if (choice == "B") {
                cout << "Instruction Register (IR): " << cpu.getInstructionRegister() << "\n";
                break;
            }
            if (choice == "C") {
                cout << "Program Counter (PC): " << PC << "\n";
                break;
            }

            cout << "Invalid choice, please enter A, B, C, or D.\n";
            cin.clear();  // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // discard invalid input
        }
    }


    static bool isValidInstruction(const string &instruction) {
        return instruction.length() == 4 && ranges::all_of(instruction, [](char c) {
            return isxdigit(c); // Check if each character is a hexadecimal digit
        });
    }

    static bool isValidFilename(const string &filename) {
        ifstream file(filename);
        bool exists = file.good();
        file.close();
        return exists;
    }

    static void executeInstructions(const vector<string> &instructions, int &PC) {
        int maxMemoryLocation = 255; // Maximum memory location available
        for (const auto &instruction : instructions) {
            if (PC > maxMemoryLocation - 1) {
                cout << "Memory overflow! Not enough space to load more instructions.\n";
                break;
            }

            cpu.loadNextInstruction(instruction);  // Load instruction into memory and update IR
            Control_Unit::opcode_checker(instruction, register_, memory, PC); // Execute with the updated PC
        }
    }


   static void menu() {
    cout << "===========================================================================\n";
    int location;

    // Validate start location input
    while (true) {
        cout << "Enter the memory start location (1 to 255): ";
        if (!(cin >> location) || location < 1 || location > 255) {
            cout << "Invalid location! Please enter a number between 1 and 255.\n";
            cin.clear();  // clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore last input
        } else {
            break;
        }
    }

    memory.setStartLocation(location);
    cpu.setPC(location);  // Set initial PC
    cout << "===========================================================================\n";

    while (true) {
        cout << "Enter your choice: " << endl;
        cout << "(A) Load Instructions from File\n"
             << "(B) Enter Instructions Manually\n"
             << "(C) Display State\n"
             << "(D) Execute Instructions\n"
             << "(E) Exit\n";

        char choice;
        cin >> choice;
        choice = toupper(choice);  // Convert to uppercase for consistency

        static vector<string> instructions;

        if (choice == 'A') {
            string filename;
            cout << "Enter the file name (e.g., instructions.txt): ";
            cin >> filename;
            if (isValidFilename(filename)) {
                ifstream inputFile(filename);
                instructions = fileInstructions(inputFile);
            } else {
                cout << "File does not exist. Please try again.\n";
            }

        } else if (choice == 'B') {
            cout << "Enter instructions (4 hexadecimal characters each). Type 'C000' to end.\n";
            while (true) {
                string inputIns;
                cin >> inputIns;
                inputIns = toUpperCase(inputIns);
                if (isValidInstruction(inputIns)) {
                    if ((255 - location) < instructions.size()) { //avoiding over flow
                        cout << "Number of instructions exceeds available cells in memory!\n";
                        break;
                    }
                    instructions.push_back(inputIns);

                    if (inputIns == "C000") {  // HALT command
                        break;
                    }

                } else {
                    cout << "Invalid instruction! Must be exactly 4 hexadecimal characters.\n";
                }
            }

        } else if (choice == 'C') {
            outputState();

        } else if (choice == 'D') {
            if (!instructions.empty()) {
                executeInstructions(instructions, PC);  // Execute loaded instructions one by one
                instructions.clear();  // Clear after execution if you want to reload a new set
            } else {
                cout << "No instructions loaded. Please load or enter instructions first.\n";
            }

        } else if (choice == 'E') {
            cout << "Program stopped.\n";
            break;

        } else {
            cout << "Invalid choice, please try again.\n";
            cin.clear();  // clear input buffer in case of invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ignore invalid input
        }
    }
}


};

#endif //20230419_S5_20230092_S21_20230039_S23_MAINUI_H
