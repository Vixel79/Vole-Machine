/* 20230419 S5
 * 20230093 S21
 * 20230039 S23
 */

#include <iostream>
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Register.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Control_Unit.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_Memory.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_CPU.h"
#include "A1_Task4_20230419_S5_20230092_S21_20230039_S23_MainUI.h"
using namespace std;

// Define static members
Memory MainUI::memory;
Register MainUI::register_;
ALU MainUI::alu;
Control_Unit MainUI::control_unit;
CPU MainUI::cpu; // Assuming CPU has a default constructor
int MainUI::PC = 0; // You can change 0 to any default value you prefer


int main() {
    MainUI::menu();
}

