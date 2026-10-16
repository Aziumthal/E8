#ifndef ISA_LIST
#define ISA_LIST

#include<unordered_map>
#include<string>
#include<bitset>
#include<vector>

inline const std::unordered_map<std::string, std::bitset<8>> opcode_map {
    {"NA",    0b00000000},
    {"RUKO",  0b00000001},
    {"RET",   0b00000010},
    {"EI",    0b00000011},
    {"DI",    0b00000100},
    {"LDH",   0b00000101},
    {"INCH",  0b00000110},
    {"DECH",  0b00000111},
    {"PUSHH", 0b00001000},
    {"POPH",  0b00001001},
    {"MOV",   0b00001010},
    {"JMP",   0b00001011},
    {"JZ",    0b00001100},
    {"JNZ",   0b00001101},
    {"JC",    0b00001110},
    {"JNC",   0b00001111},
    {"CALL",  0b00010000},
    {"ADDI",  0b00010001},
    {"SUBI",  0b00010010},
    {"ANDI",  0b00010011},
    {"ORI",   0b00010100},
    {"XORI",  0b00010101},
    {"CMPI",  0b00010110},
    {"LDI",   0b001000},
    {"LD",    0b001001},
    {"ST",    0b001010},
    {"LDHL",  0b001011},
    {"STHL",  0b001100},
    {"ADD",   0b001101},
    {"ADC",   0b001110},
    {"SUB",   0b001111},
    {"SBC",   0b010000},
    {"INC",   0b010001},
    {"DEC",   0b010010},
    {"AND",   0b010011},
    {"OR",    0b010100},
    {"XOR",   0b010101},
    {"NOT",   0b010110},
    {"SHL",   0b010111},
    {"SHR",   0b011000},
    {"ROL",   0b011001},
    {"ROR",   0b011010},
    {"CMP",   0b011011},
    {"PUSH",  0b011100},
    {"POP",   0b011101},
    {"IN",    0b011110},
    {"OUT",   0b011111},
    {"SETH",  0b100001},
    {"SETL",  0b100010},
    {"GETH",  0b100011},
    {"GETL",  0b100100},
    {"FGS",   0b10000000},
    {"FGL",   0b10000001},
    {"ADDHA", 0b10000010}
    };

inline const std::unordered_map<std::string, int> reg_map{
            {"A", 0b00},
            {"B", 0b01},
            {"C", 0b10},
            {"D", 0b11}
    };

inline const std::unordered_map<std::string , int> operand_size {

    {"NA", 0}, {"RUKO", 0}, {"RET", 0}, {"EI", 0}, {"DI", 0},
    {"INCH", 0}, {"DECH", 0}, {"PUSHH", 0}, {"POPH", 0},
    {"FGS", 0}, {"FGL", 0},{"LDHL", 0}, {"STHL", 0},
    {"ADD", 0}, {"ADC", 0}, {"SUB", 0}, {"SBC", 0},
    {"INC", 0}, {"DEC", 0},
    {"AND", 0}, {"OR", 0}, {"XOR", 0}, {"NOT", 0},
    {"SHL", 0}, {"SHR", 0}, {"ROL", 0}, {"ROR", 0},
    {"CMP", 0}, {"PUSH", 0}, {"POP", 0},
    {"ADDHA", 0}, {"SETH", 0}, {"SETL", 0}, {"GETH", 0}, {"GETL", 0},

    {"MOV", 1},{"ADDI", 1}, {"SUBI", 1}, {"ANDI", 1},
    {"ORI", 1}, {"XORI", 1}, {"CMPI", 1},{"LDI", 1},{"IN", 1}, {"OUT", 1},

    {"LDH", 2}, {"JMP", 2}, {"JZ", 2}, {"JNZ", 2}, {"JC", 2}, {"JNC", 2},
    {"CALL", 2}, {"LD", 2}, {"ST", 2}

};

inline const std::unordered_map<std::string , int> req_reg{

    {"NA", 0}, {"RUKO", 0}, {"RET", 0}, {"EI", 0}, {"DI", 0},
    {"LDH", 0}, {"INCH", 0}, {"DECH", 0}, {"PUSHH", 0}, {"POPH", 0},
    {"JMP", 0}, {"JZ", 0}, {"JNZ", 0}, {"JC", 0}, {"JNC", 0}, {"CALL", 0},
    {"ADDI", 0}, {"SUBI", 0}, {"ANDI", 0}, {"ORI", 0}, {"XORI", 0}, {"CMPI", 0},
    {"FGS", 0}, {"FGL", 0}, {"ADDHA", 0},


    {"LDI", 1}, {"LD", 1}, {"ST", 1}, {"LDHL", 1}, {"STHL", 1},
    {"ADD", 1}, {"ADC", 1}, {"SUB", 1}, {"SBC", 1},
    {"INC", 1}, {"DEC", 1}, {"AND", 1}, {"OR", 1}, {"XOR", 1}, {"NOT", 1},
    {"SHL", 1}, {"SHR", 1}, {"ROL", 1}, {"ROR", 1},
    {"CMP", 1}, {"PUSH", 1}, {"POP", 1}, {"IN", 1}, {"OUT", 1},
    {"SETH", 1}, {"SETL", 1}, {"GETH", 1}, {"GETL", 1},


    {"MOV", 2}
};

inline const std::unordered_map<std::string , std::bitset<8>> reg_pair{
    {"A,A", 0b0000}, {"A,B", 0b0001}, {"A,C", 0b0010}, {"A,D", 0b0011},
    {"B,A", 0b0100}, {"B,B", 0b0101}, {"B,C", 0b0110}, {"B,D", 0b0111},
    {"C,A", 0b1000}, {"C,B", 0b1001}, {"C,C", 0b1010}, {"C,D", 0b1011},
    {"D,A", 0b1100}, {"D,B", 0b1101}, {"D,C", 0b1110}, {"D,D", 0b1111}
};

inline std::unordered_map<std::string , int> label_map{



};

inline const std::unordered_map<std::string, int> operand_count {
    {"NA", 0}, {"RUKO", 0}, {"RET", 0}, {"EI", 0}, {"DI", 0},
    {"INCH", 0}, {"DECH", 0}, {"PUSHH", 0}, {"POPH", 0},
    {"FGS", 0}, {"FGL", 0}, {"ADDHA", 0},

    {"LDH", 1}, {"JMP", 1}, {"JZ", 1}, {"JNZ", 1}, {"JC", 1}, {"JNC", 1}, {"CALL", 1},
    {"ADDI", 1}, {"SUBI", 1}, {"ANDI", 1}, {"ORI", 1}, {"XORI", 1}, {"CMPI", 1},
    {"LDHL", 1}, {"STHL", 1},
    {"ADD", 1}, {"ADC", 1}, {"SUB", 1}, {"SBC", 1},
    {"INC", 1}, {"DEC", 1},
    {"AND", 1}, {"OR", 1}, {"XOR", 1}, {"NOT", 1},
    {"SHL", 1}, {"SHR", 1}, {"ROL", 1}, {"ROR", 1},
    {"CMP", 1}, {"PUSH", 1}, {"POP", 1},
    {"SETH", 1}, {"SETL", 1}, {"GETH", 1}, {"GETL", 1},

    {"MOV", 2}, {"LDI", 2}, {"LD", 2}, {"ST", 2}, {"IN", 2}, {"OUT", 2}
};

#endif

