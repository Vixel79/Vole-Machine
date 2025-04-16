/* 20230419 S5
* 20230093 S21
 * 20230039 S23
 */


#ifndef A1_Task4_20230419_S5_20230092_S21_20230039_S23_REGISTER_H
#define A1_Task4_20230419_S5_20230092_S21_20230039_S23_REGISTER_H
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Register {
    int size ;
    vector<string> Registers;

public:
    Register() :size(16) ,  Registers(16, "00") {}

    static int idx_convert(char index) {
        if (index >= '0' && index <= '9') {
            return index - '0';
        }                              // {'0'-'9' -> 0-9 }
        if (index >= 'A' && index <= 'F')
        {
            return index - 'A' + 10;// 'A'-'F' -> 10-15
        }
        return -1; // Invalid index
    }


    string getRegister(char index) const {
        int idx = idx_convert(index);
        if (idx >= 0 && idx < size) {
            return Registers[idx];
        }
        return "Invalid Index"; // Handle invalid indices
    }

    void setRegister(char index ,  const string &value) {
        int idx = idx_convert(index);
        if (idx >= 0 && idx < size) {
            Registers[idx] = value;
        }
        else {
            cout << "Invalid Index" << endl;
        }
    }

    void display_registers() const {
        for (int i = 0; i < size; ++i) {
            cout << "Register#" << i << " : " << getRegister(i < 10 ? '0' + i : 'A' + (i - 10)) << endl;
        }
    }


};

#endif //A1_Task4_20230419_S5_20230092_S21_20230039_S23_REGISTER_H
