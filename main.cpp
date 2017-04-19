//
//  main.cpp
//  Lexical_Analyzer_p1
//
//  Created by William Pinkston on 2/2/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <ctype.h>

#include "Analyzer.h"
#include "Parser.h"
#include "Database.h"

void ReadFile(std::string filename, std::vector<char>& Input)
{
    std::ifstream inFile(filename.c_str());
    if (inFile.fail())
    {
        return;
    }
    char inChar = inFile.get();
    while (inFile.good())
    {
        Input.push_back(inChar);
        //std::cout << inChar;
        inChar = inFile.get();
    }
    if (inFile.eof())
    {
        Input.push_back('\0');
    }
}


int main(int argc, const char * argv[])
{

    if (argc != 2)
    {
        std::cout << "Incorrect usage. Expected " << argv[0] << " <filename>" << std::endl;
        return 0;
    }

    analyzer lexer;
    
    std::vector<char> Input;
    ReadFile(argv[1]/*"/Users/Howl/Documents/BYU/CS/CS_236/Projects/Datalong_Interpreter/Datalog_Interpreter_part2/datalogTest2.txt"*/,Input);
    
    if (Input.size() == 0)
    {
        std::cout << "Program is empty, nothing to parse." << std::endl;
        return 0;
    }
    
    std::stack<std::string> tokens;
    tokens = lexer.run(Input);
    
    parser logParser(tokens);
    if (!logParser.run())
    {
        std::cout << "Failure to parse." << std::endl;
        return 0;
    }
    
    database relationalDatabase(*logParser.getProgram());
    
    //project 4
    std::cout << relationalDatabase.fillRules() << std::endl;
    //end 4
    
    std::cout << relationalDatabase.answerQueries() << std::endl;
    return 0;
}






