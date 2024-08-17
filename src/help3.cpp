#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

 
using namespace std;
// 定义一个函数来执行指令
void executeInstruction(const std::string &line, std::unordered_map<std::string, int> &registers) {
    std::istringstream iss(line);
    std::string opcode, reg, src0, src1;
    int immediate = 0;
    char space;

    // 读取操作码和第一个寄存器
    iss >> opcode >> reg;

    if (opcode == "MOV") {
        iss >> src0;
        if (std::isdigit(src0[0]) ) { // 检查是否有字母，以确定src0是寄存器还是立即数
            registers[reg] = std::stoi(src0); // 立即数
        } else {
            registers[reg] = registers[src0]; // 寄存器
        }
    }
    else if (opcode == "ADD" || opcode == "SUB" || opcode == "MUL" || opcode == "DIV") {
        // 读取两个源操作数
        iss >> src0 >> src1;
        int src0_value = std::isdigit(src0[0]) ? std::stoi(src0) : registers[src0];
        int src1_value = std::isdigit(src1[0]) ? std::stoi(src1) : registers[src1];

        if (opcode == "ADD") {
            registers[reg] = src0_value + src1_value;
        } else if (opcode == "SUB") {
            registers[reg] = src0_value - src1_value;
        } else if (opcode == "MUL") {
            registers[reg] = src0_value * src1_value;
        } else if (opcode == "DIV") {
            registers[reg] = src0_value / src1_value;
        }
    } 
    else if (opcode == "PRINT") {
        std::cout << registers[reg] << std::endl;
    }
}

int main() {
    std::unordered_map<std::string, int> registers;
    std::string line;

    while (std::getline(std::cin, line)) {
        executeInstruction(line, registers);
    }

    return 0;
}