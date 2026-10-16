#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include "global_var.hpp"
#include "lists.hpp"
#include "pass.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]){
  if(argc != 3){
    std::cerr << "NOT enough files passed. Please provide the input and output files."; //did this to ensure 3 files are passed: input assembler and output file
    return 1;
  }

  std::string Line{};  
  std::ifstream Assembly{"code.asm"};
  
    while(std::getline(Assembly,Line)){ 
      
      line++;
      error = 0;

      for (char &c : Line) {
          c = std::toupper(c);
      }

      if(Line.empty()){ continue; } 

      commentrem(Line); 
      if(Line.empty()){ continue; } 

      labelstr(Line);
      if(Line.empty()){ continue; }

      if(error){
      any_error = true;
      continue;}
      
      std::vector <std::string> words{};
      
      parsing(Line,words);
      if(words.empty()) {continue;}

      checkstr(words);

      if(error){
      any_error = true;
      continue;}
  }      

  if(any_error){return 1;}  
  convbinary();
  return error ? 1 : 0;
}