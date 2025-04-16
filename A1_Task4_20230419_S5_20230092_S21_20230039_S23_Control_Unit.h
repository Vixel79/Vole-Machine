/* 20230419 S5
* 20230093 S21
 * 20230039 S23
 */

#ifndef A1_Task4_20230419_S5_20230092_S21_20230039_S23_CONTROL_UNIT_H
#define A1_Task4_20230419_S5_20230092_S21_20230039_S23_CONTROL_UNIT_H
#include<bits/stdc++.h>
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Register.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Memory.h"
using namespace std;


class Control_Unit {
    ALU alu ;

public:
    static void opcode_checker(const string &instruction, Register &R, Memory &M, int &PC) {

        if (instruction[0] == '3' && instruction.substr(2,4) == "00") {
            int m_idx = stoi(ALU::HexToDec(instruction.substr(2,4)));
            int idxReg = instruction[1];
            string value = R.getRegister(idxReg);
            M.set(m_idx, value);
            cout<<"----Screen Display(3R00)----"<<" => " <<R.getRegister(idxReg)<<endl;

        }

    switch (char op_code = instruction[0]) {
        case '1':
            cout << "loaded from memory to register" << endl;
            load(instruction, R, M);
            break;
        case '3':
            cout << "loaded from register to memory" << endl;
            store(instruction, R, M);
            break;
        case '2':
            cout << "loaded memory address to register" << endl;
            load_add(instruction, R);
            break;
        case '4':
            cout << "Copied from register to another one" << endl;
            copy(instruction, R);
            break;
        case '5':
            cout << "Added two registers" << endl;
            Add_content(instruction, R);
            break;
        case '6':
            cout << "Added two float registers" << endl;
            Float_Add_content(instruction, R);
            break;
        case '7':
            cout << "OR-ed two registers" << endl;
            Or_content(instruction, R);
            break;
        case '8':
            cout << "AND-ed two registers" << endl;
            And_content(instruction, R);
            break;
        case '9':
            cout << "XOR-ed two registers" << endl;
            XOR_content(instruction, R);
            break;
        case 'A':
            cout << "-ROTATED-" << endl;
            Rotate_content(instruction, R);
            break;
        case 'B':
            cout << "-JUMPED-" << endl;
            jump(instruction, R, PC); // `jump` sets `PC` directly if condition is met
            return;  // End early if jump changes `PC`
        case 'C':
            if (instruction == "C000") {
                cout << "Program halted due to C000 instruction." << endl;
                return;  // End function on halt
            }
            break;
        case 'D':
            jumpV2(instruction, R, PC); // `jumpV2` also sets `PC` directly if condition is met
            return;  // End early if jumpV2 changes `PC`
        default:
            cout << "Invalid opcode!" << endl; // Handle invalid opcodes
            break;
    }

}



    static void load(const string &instruction, Register &R, const Memory &M) {
        // Validate instruction length
        if (instruction.length() != 4) {
            cout << "Invalid instruction length!" << endl;
            return;
        }

        // Extract register index and memory address
        char idxReg = instruction[1]; // This is 'R'
        string memoryAddressHex = instruction.substr(2, 2); // This is 'XY'

        // Convert the hexadecimal memory address to decimal
        int memoryIndex = stoi(ALU::HexToDec(memoryAddressHex));

        // Retrieve the value from memory at the specified index
        string value = M.get(memoryIndex);

        // Load the value into the specified register
        R.setRegister(idxReg, value);

        // Debug output to confirm the operation
        cout << "Loaded value: " << value
             << " from memory address: " << memoryAddressHex
             << " into register: " << idxReg << endl;
    }
    //Function 3
    static void store(const string &instruction , const Register &R , Memory &M) {

        int m_idx = stoi(ALU::HexToDec(instruction.substr(2,4)));
        int idxReg = instruction[1];
        string value = R.getRegister(idxReg);
        M.set(m_idx, value);


    }
    //Function 2
    static void load_add(const string &instruction ,Register &R ) {
        string value = instruction.substr(2,4);
        int idxReg = instruction[1];

        R.setRegister(idxReg, value);

    }
    //Function 4
    static void copy(const string &instruction , Register &R) {
        int idxReg1 = instruction[2];
        int idxReg2 = instruction[3];
        R.setRegister(idxReg2, R.getRegister(idxReg1));
    }
    //Function 5
    static void Add_content(const string &instruction , Register &R) {
        R.setRegister(instruction[1], ALU::AddBinary(R.getRegister(instruction[2]), R.getRegister(instruction[3])));
    }
    //Function 6
    static void Float_Add_content(const string &instruction , Register &R) {
       R.setRegister(instruction[1], ALU::hexAdditionAndCustomFloat(R.getRegister(instruction[2]), R.getRegister(instruction[3])));
    }
    //Function 7
    static void Or_content(const string &instruction , Register &R) {
        R.setRegister(instruction[1], ALU::orTwoNums(R.getRegister(instruction[2]), R.getRegister(instruction[3])) );
    }
    //Function 8
    static void And_content(const string &instruction , Register &R) {
        R.setRegister(instruction[1], ALU::andTwoNums(R.getRegister(instruction[2]), R.getRegister(instruction[3])) );
    }
    //Function 9
    static void XOR_content(const string &instruction , Register &R) {
        R.setRegister(instruction[1], ALU::xorTwoNums(R.getRegister(instruction[2]), R.getRegister(instruction[3])) );
    }
    //Function A
    static void Rotate_content(const string &instruction , Register &R) {
        R.setRegister(instruction[1], ALU:: xorTwoNums(R.getRegister(instruction[2]), R.getRegister(instruction[3])) );
    }
    //Function B
    static void jump(const string &instruction , const Register &R , int &PC ) {
        const string value = instruction.substr(2,4);
        if (R.getRegister(instruction[1])==R.getRegister('0')) {
            PC = stoi(ALU :: HexToDec(value));
        }
    }
    //Function C
        //Halt
    //Function D
    static void jumpV2(const string &instruction , const Register &R , int &PC ) {
        const string value = instruction.substr(2,4);
        if (R.getRegister(instruction[1]) > R.getRegister(0)) {
            PC = stoi(ALU :: HexToDec(value));
            cout << "Jumping to RAM cell : " << value << endl;

        }

    }


};


#endif //A1_Task4_20230419_S5_20230092_S21_20230039_S23_CONTROL_UNIT_H
