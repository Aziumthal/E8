#ifndef GLOBAL
#define GLOBAL
#include<cstdint>
#include<vector>
#include<string>

inline int adress_counter{0};
inline size_t line{0}; 
inline bool error{0};
inline bool any_error{0};

struct Positon_op {
    std::string opcode;
    std::vector<std::string> operand;
    size_t line_no;
    int adress;
};


#endif