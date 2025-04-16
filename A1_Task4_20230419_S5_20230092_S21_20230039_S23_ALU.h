/* 20230419 S5
* 20230093 S21
 * 20230039 S23
 */


#ifndef A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU_H
#define A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU_H

#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;
class ALU {
public:
    static string floatToHex(float value) {
        // Step 1: Determine the sign bit
        int signBit = (value < 0) ? 1 : 0;
        value = fabs(value); // Use absolute value for calculations
        // Step 2: Initialize exponent and mantissa
        int exponent = 0;
        // Handle the case for normalization
        if (value == 0.0) {
            return "00"; // Zero in hexadecimal is 00
        }
        // Normalize the value
        while (value >= 1.0) {
            value /= 2;
            exponent++;
        }
        while (value < 0.5) {
            value *= 2;
            exponent--;
        }
        // Here we handle the biasing rules
        int mantissa = static_cast<int>((value - 1.0) * 16); // Get the first four bits of the mantissa
        exponent += 4; // Negative exponent bias
        // Ensure mantissa fits in 4 bits
        mantissa &= 0x0F; // Mask to keep only the last 4 bits
        // Convert biased exponent to binary
        bitset<1> sign(signBit);
        bitset<3> exponentBits(exponent);
        bitset<4> mantissaBits(mantissa);
        // Combine all parts
        string binaryString = sign.to_string() + exponentBits.to_string() + mantissaBits.to_string();
        // Convert the binary string to hexadecimal
        unsigned long hexValue = bitset<8>(binaryString).to_ulong();
        stringstream ss;
        ss << hex << uppercase << hexValue;
        return ss.str();
    }

// Function to convert an 8-bit custom float hex string to a double
    static double toFloatingPoint(const string& hex) {
        // Convert hexadecimal string to an 8-bit binary representation
        bitset<8> binary(stoul(hex, nullptr, 16));
        // Extract sign, exponent, and mantissa
        int sign = binary[7]; // 1-bit for sign (the leftmost bit)
        int exponentBits = stoi(binary.to_string().substr(1, 3), nullptr, 2); // 3-bits for exponent
        int mantissaBits = stoi(binary.to_string().substr(4, 7), nullptr, 2); // 4-bits for mantissa
        // Calculate exponent with bias adjustment
        int exponent = exponentBits - 4; // Bias is 4
        // Calculate mantissa
        double mantissa = static_cast<double>(mantissaBits) / 16.0; // Convert 4-bit mantissa to decimal
        // Return the final result with the correct sign
        return (sign ? -1.0 : 1.0) * mantissa * pow(2, exponent); // Correctly handle sign
    }

    // Function to convert a hexadecimal string to a signed integer (8-bit or 4-bit two's complement)
    static int HexToDecTowsComplement(const string& hexStr, int bits = 8) {
        int decimalValue;
        stringstream ss;
        ss << hex << hexStr;
        ss >> decimalValue;

        // Adjust for two's complement representation
        if (decimalValue >= (1 << (bits - 1))) {
            decimalValue -= (1 << bits);  // Convert to negative value if the number is in the two's complement negative range
        }

        return decimalValue;
    }

// Function to convert a decimal value to a 4-bit or 8-bit two's complement hexadecimal string
    static string DecToHexTowsComplement(int decimalValue, int bits = 8) {
        // Adjust for two's complement representation
        if (decimalValue < 0) {
            decimalValue += (1 << bits);  // Add the 2^bits to get the two's complement
        }

        stringstream ss;
        ss << hex << uppercase << setw(bits / 4) << setfill('0') << decimalValue; // Format as hex digits based on the bit-width
        return ss.str();
    }

    static string HexToDec(const string& hexNum) {
        int decimalValue = stoi(hexNum, nullptr, 16); // Convert hex string to decimal integer
        return to_string(decimalValue);
    }

    static string DecToHex(const string& num) {
        int decNum = stoi(num); // Convert decimal string to integer
        stringstream ss;
        ss << hex << uppercase << decNum; // Convert integer to hexadecimal string in uppercase
        return ss.str();
    }

    // Function to add the contents of two registers (S and T) interpreted as two's complement integers
    static string AddBinary(const string& hexS, const string& hexT, int bits = 8) {
        // Convert hex values to decimal (as two's complement integers)
        int valueS = HexToDecTowsComplement(hexS, bits);
        int valueT = HexToDecTowsComplement(hexT, bits);
        // Perform addition
        int result = valueS + valueT;
        // Ensure the result is within the specified bit-width (wrap around if overflowed)
        result = result & ((1 << bits) - 1);  // Mask to fit within the bit-width
        // Convert the result back to hexadecimal
        return DecToHexTowsComplement(result, bits);
    }

    static string orTwoNums(const string& Num1, const string& Num2) {
        int decNum1 = stoi(HexToDec(Num1));
        int decNum2 = stoi(HexToDec(Num2));
        int res = decNum1 | decNum2; // Perform OR operation directly on decimal
        return DecToHex(to_string(res)); // Return result as a binary string
    }

    static string andTwoNums(const string& Num1, const string& Num2) {
        int decNum1 = stoi(HexToDec(Num1));
        int decNum2 = stoi(HexToDec(Num2));
        int res = decNum1 & decNum2; // Perform AND operation directly on decimal
        return DecToHex(to_string(res)); // Return result as a binary string
    }

    static string xorTwoNums(const string& Num1, const string& Num2) {
        int decNum1 = stoi(HexToDec(Num1));
        int decNum2 = stoi(HexToDec(Num2));
        int res = decNum1 ^ decNum2; // Perform XOR operation directly on decimal
        return DecToHex(to_string(res)); // Return result as a binary string
    }


// Function to add two hexadecimal numbers in custom float format
    static string hexAdditionAndCustomFloat(const string& hex1, const string& hex2) {
        // Step 1: Convert hex strings to float representation
        double n1 = toFloatingPoint(hex1); // Use double for precision
        double n2 = toFloatingPoint(hex2);
        // Step 2: Perform the addition
        double res = n1 + n2;
        // Step 3: Convert result to string without extra zeros
        ostringstream oss;
        oss << fixed << setprecision(6) << res; // Adjust precision as needed
        string result = oss.str();
        // Remove trailing zeros and decimal point if necessary
        result.erase(result.find_last_not_of('0') + 1, string::npos); // Remove trailing zeros
        if (result.back() == '.') {
            result.pop_back(); // Remove decimal point if it's the last character
        }
        return floatToHex(stof(result)); // Return the formatted result
    }

    // Function to perform cyclic right rotation using OR
    static string rotate(const string& hex1, const string& hex2) {
        // Convert hex1 to decimal and hex2 to the shift amount
        int decNum1 = stoi(HexToDec(hex1));
        int shift = stoi(HexToDec(hex2));

        // Determine 'bit' length based on the input size of hex1
        int bitLength = (hex1.size() == 1) ? 4 : 32;  // Use 4 bits for single hex digit, 32 otherwise
        shift = shift % bitLength;  // Ensure shift is within bounds

        // Perform the cyclic right rotation using OR
        int rightShifted = (decNum1 >> shift);                // Right shift
        int leftShifted = (decNum1 << (bitLength - shift));   // Left shift to wrap bits
        int rotatedResult = (rightShifted | leftShifted) & ((1 << bitLength) - 1);  // Combine with OR and mask to bitLength bits

        // Convert the result back to hexadecimal
        return DecToHex(to_string(rotatedResult));
    }
};

#endif //A1_Task4_20230419_S5_20230092_S21_20230039_S23_ALU_H