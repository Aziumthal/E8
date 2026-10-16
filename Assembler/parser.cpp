#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "global_var.hpp"
#include "lists.hpp"
#include "parser.hpp"

void commentrem(std::string &copy){ 
    auto pos1 = copy.find("#");
    if(pos1 != std::string::npos){
        copy.erase(pos1);     
    } 
    return;
}

void labelstr(std::string &copy){
    size_t locate = copy.find(":");
    while(locate != std::string::npos){
        std::string labelval;
        for(std::size_t i = 0; i < locate; i++){
            if(copy[i] != ' ' && copy[i] != '\t'){
                labelval.push_back(copy[i]);
            }
        }
        if(labelval.empty()){
            std::cerr << "Semicolon without a label name" << adress_counter;
            error=1;
        }
        else if(label_map.count(labelval)){
            std::cerr << "Duplicate label at line" << adress_counter;
            error=1;
        }
        else{
            label_map[labelval] =adress_counter;
        }
        copy.erase(0,locate +1);
        locate = copy.find(":");
    }
}

void parsing(std::string &copy,std::vector<std::string> &store){                       
    auto commar = copy.find(",");
    while(commar != std::string::npos){
        copy[commar] = ' ';
        commar = copy.find(",");
    }

    std::stringstream Parser{copy}; 
    std::string temp;
    while(Parser >> temp){
        store.push_back(temp);
        }
}   