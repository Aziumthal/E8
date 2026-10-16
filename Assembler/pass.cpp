#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <bitset>
#include <cstdint>
#include <cctype>
#include "pass.hpp"
#include "lists.hpp"
#include "global_var.hpp"


std::vector<struct Positon_op> Positon_code;

//pass 1

void checkstr(const std::vector<std::string> &list){
    int numoperand = static_cast<int>(list.size()) - 1;
    if(opcode_map.count(list[0])){
        switch(operand_count.at(list[0])){
            case 0:
                if(numoperand == 0){
                    Positon_code.push_back({list[0],{},line,adress_counter});
                    adress_counter = adress_counter + operand_size.at(list[0]) + 1;
                }
                else {
                    std::cerr << "line : "<< line <<" : " <<list[0]
                              <<" expect 0 operand,got "<<numoperand << "\n";
                    error = 1;
                }
            break;
            case 1:
                if(numoperand == 1){
                    Positon_code.push_back({list[0],{list[1]},line,adress_counter});
                    adress_counter = adress_counter + operand_size.at(list[0]) + 1;
                }
                else {
                    std::cerr <<"line "<<line<<" : "<<list[0]
                              <<"expects 1 operand,got "<<numoperand<<"\n";
                    error = 1;
                }
            break;
            case 2:
                if(numoperand == 2){
                    Positon_code.push_back({list[0], {list[1], list[2]}, line, adress_counter});
                    adress_counter = adress_counter + operand_size.at(list[0]) + 1;
                }
                else {
                    std::cerr<<"line "<<line<<":"<< list[0]
                              <<" expect 2 operand,got "<<numoperand<<"\n";
                    error = 1;
                }
            break;
            default:
                std::cerr <<"line "<<line<< list[0] <<" has an invalid operand count\n";
                error = 1;
            break;
        }
    }
    else{
        std::cerr << "line " << line << ": unknown instruction" << list[0] << "'\n";
        error =1;
    }
}

//PASS 2

bool tonumber(const std::string &s,long &out){
    bool neg = (s[0] == '-')?1:0;
    std::size_t start =(s[0] =='-'||s[0]=='+')?1:0;
    int base = 10;
    if(s.size() >start + 2 && s[start]=='0' && s[start+1]=='X'){ 
        base= 16;
        start += 2;
    }
    else if(s.size()>start+2 && s[start]=='0'&& s[start + 1] == 'B'){
         base = 2; 
         start +=2;}
   if(start < s.size() && (s[start] == '-'||s[start] == '+')) return false;
    try{    
        std::size_t used = 0;
        long v = std::stol(s.substr(start), &used, base);
        if(used != s.size() - start) {return false;}
        out = neg ? -v : v;
        return true;
    }
    catch(...){ return false; }
}

bool getreg(const std::string &text, int ln){
    if(reg_map.count(text)){
        return true;
    }
    else {
        std::cerr<< "error atline " <<ln << ":"<< text<<"is not a register (use A, B, C or D)\n";
        error = 1;
        return false;
    }
    
}

bool getvalue(const std::string &text, int bits, int ln, int &out){
    long v = 0;
    if(tonumber(text, v)){
        long lo = (bits == 8) ? -128 : 0;
        long hi = (bits == 8) ? 255 : 65535;
        if(v < lo || v > hi){
            std::cerr << "line " << ln << ": value " << text << " does not fit in " << bits << " bits\n";
            error = true;
            return false;
        }
        out = static_cast<int>(v) & ((1 << bits) - 1);
        return true;
    }
    if(std::isdigit(static_cast<unsigned char>(text[0])) || text[0] == '-' || text[0] == '+'){
        std::cerr << "line " << ln << ": bad number '" << text << "'\n";
        error = true;
        return false;
    }
    if(bits == 8){
        std::cerr << "line " << ln << ": label '" << text << "' is an address and does not fit in 8 bits\n";
        error = true;
        return false;
    }
    auto it = label_map.find(text);
    if(it == label_map.end()){
        std::cerr << "line " << ln << ": unknown label '" << text << "'\n";
        error = true;
        return false;
    }
    if(it->second < 0 || it->second > 65535){
        std::cerr << "line " << ln << ": label '" << text << "' is past the end of memory\n";
        error = true;
        return false;
    }
    out = it->second;
    return true;
}

void emit8(std::ostringstream &o,int v){
    o<< std::bitset<8>(v) <<'\n';
}

void emit16(std::ostringstream &o, int v){
    emit8(o, v & 0xFF);
    emit8(o, (v >> 8) &0xFF);
}

void emitregvalue(std::ostringstream &o, const std::string &m, const std::string &regtext,
                  const std::string &valtext, int bits, int ln){
    int value = 0;
    if(!getreg(regtext, ln)) {
        return;
    }
    if(!getvalue(valtext, bits, ln, value)) {
        return;
    }
    emit8(o, static_cast<int>(opcode_map.at(m).to_ulong() << 2) | reg_map.at(regtext));
    if(bits == 8) {
        emit8(o, value);
    }
    else{
        emit16(o, value);
    }    
}

void convbinary(){
    std::ostringstream output;
    for(const Positon_op &bitconv : Positon_code){
        const std::vector<std::string> &ops = bitconv.operand;
        int value = 0;  

        switch(10*(req_reg.at(bitconv.opcode)) + (operand_size.at(bitconv.opcode))){
            case 0:
                output << opcode_map.at(bitconv.opcode) << '\n';
            break;
            case 10: {
                if(getreg(ops[0],bitconv.line_no)){
                    emit8(output,static_cast<int>(opcode_map.at(bitconv.opcode).to_ulong() << 2)| reg_map.at(ops[0]));
                    }
                else{
                    std::cerr<< "line " << bitconv.line_no << ops[0] << "' is not a register\n";
                    error = true;
                    continue;
                }
            }
            break;
            case 1:
                if(getvalue(ops[0], 8, bitconv.line_no, value)){
                    output << opcode_map.at(bitconv.opcode) << '\n';
                    emit8(output, value);
                }
            break;
            case 2:
                if(getvalue(ops[0], 16, bitconv.line_no, value)){
                    output << opcode_map.at(bitconv.opcode) << '\n';
                    emit16(output, value);
                }
            break;
            case 21: {
                std::string Regpair{ops[0] + "," + ops[1]};
                if(reg_pair.count(Regpair)){
                    output << opcode_map.at(bitconv.opcode) << '\n';
                    output << reg_pair.at(Regpair) << '\n';
                }
                else{
                    std::cerr << "line " << bitconv.line_no << ": invalid register pair '"
                              << ops[0] << ", " << ops[1] << "'\n";
                    error = true;
                }
            }
            break;
            case 11:  switch((opcode_map.at(bitconv.opcode)).to_ulong()){
                            case 8:   // LDI reg, value
                            case 30:  // IN reg, port
                                emitregvalue(output, bitconv.opcode, ops[0], ops[1], 8, bitconv.line_no);
                            break;
                            case 31:  // OUT port, reg
                                emitregvalue(output, bitconv.opcode, ops[1], ops[0], 8, bitconv.line_no);
                            break;
                            default:
                            break;}
            break;
            case 12:  switch((opcode_map.at(bitconv.opcode)).to_ulong()){
                            case 9:   // LD reg, addr
                                emitregvalue(output, bitconv.opcode, ops[0], ops[1], 16, bitconv.line_no);
                            break;
                            case 10:  // ST addr, reg
                                emitregvalue(output, bitconv.opcode, ops[1], ops[0], 16, bitconv.line_no);
                            break;
                            default:
                            break;}
            break;
        }
    }

    if(!error){
        std::ofstream file("program.asm");
        if(!file){
            std::cerr << "cannot open program.asm for writing\n";
            return;
        }
        file << output.str();
    }
}
