/* 20230419 S5
* 20230093 S21
 * 20230039 S23
 */
#ifndef A1_Task4_20230419_S5_20230092_S21_20230039_S23_MEMORY_H
#define A1_Task4_20230419_S5_20230092_S21_20230039_S23_MEMORY_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Memory.h"
#include <bits/stdc++.h>
using namespace std;

class Memory {
    vector<string> memory;
    int size;
    int startLocation;

public:
    Memory() : memory(256, "00"), size(256), startLocation(1) {}

    void setStartLocation(int location) {
        if (location > 0 && location < size) {
            startLocation = location;
            cout << "Starting location set to hexadecimal address : " << ALU::DecToHex(to_string(location) ) << ".\n";
        } else {
            cout << "Invalid starting location. Please enter a valid index between 0 and " << size - 1 << ".\n";
        }
    }

    void set(int index, const string &value = "00") {
        int effectiveIndex = (startLocation + index) % size; // Adjust for startLocation and wrap around
        if (effectiveIndex >= 1 && effectiveIndex < size) { //avoiding out of bounds error.
            memory[effectiveIndex] = value;
        }
    }

    string get(int index) const {
        int effectiveIndex = (startLocation + index) % size; // Adjust for startLocation and wrap around
        if (effectiveIndex >= 0 && effectiveIndex < size) {
            return memory[effectiveIndex];
        }
        return "";
    }

    void display_memory() const {
        cout << endl << "Memory Display (16x16 Matrix)" << endl;

        // Print column headers
        cout << "   "; // Initial space for row header
        for (int col = 0; col < 16; col++) {
            cout << setw(2) << hex << uppercase << col << " "; // Column header (0-F)
        }
        cout << endl;

        // Print memory rows
        for (int row = 0; row < 16; row++) {
            // Calculate the row address based on the starting location and print it
            cout << hex << uppercase << (startLocation + row * 16) % size << ": "; // Adjusted row header

            for (int col = 0; col < 16; col++) {
                int index = (row * 16 + col + startLocation) % size; // Effective index with wrap-around

                // Print memory content
                cout << setw(2) << setfill('0') << memory[index] << " ";
            }
            cout << endl;
        }
    }


};

#endif //A1_Task4_20230419_S5_20230092_S21_20230039_S23_MEMORY_H
