//
//  Analyzer.h
//  Lexical_Analyzer_p1
//
//  Created by William Pinkston on 2/2/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Analyzer_h
#define Analyzer_h

#include <stdio.h>
#include <vector>
#include <sstream>
#include <ctype.h>
#include <iostream>
#include <stack>

class analyzer {
public:
    analyzer();
    
    std::stack<std::string> flipStack();
    
    std::stack<std::string> run(std::vector<char> Input);
    
    //methods as states
    bool s0(std::vector<char> Input, unsigned int& Index);//WHITESPACE
    bool s1(std::vector<char> Input, unsigned int& Index);//COMMA
    bool s2(std::vector<char> Input, unsigned int& Index);//PERIOD
    bool s3(std::vector<char> Input, unsigned int& Index);//Q_MARK
    bool s4(std::vector<char> Input, unsigned int& Index);//LEFT_PAREN
    bool s5(std::vector<char> Input, unsigned int& Index);//RIGHT_PAREN
    bool s6(std::vector<char> Input, unsigned int& Index);//COLON
    bool s7(std::vector<char> Input, unsigned int& Index);//COLON_DASH
    bool s8(std::vector<char> Input, unsigned int& Index);//MULTIPLY
    bool s9(std::vector<char> Input, unsigned int& Index);//ADD
    bool s10(std::vector<char> Input, unsigned int& Index);//ID
    bool s11(std::vector<char> Input, unsigned int& Index);//ID
    bool s12(std::vector<char> Input, unsigned int& Index);//ID
    bool s13(std::vector<char> Input, unsigned int& Index);//ID
    bool s14(std::vector<char> Input, unsigned int& Index);//ID
    bool s15(std::vector<char> Input, unsigned int& Index);//ID
    bool s16(std::vector<char> Input, unsigned int& Index);//SCHEMES
    bool s17(std::vector<char> Input, unsigned int& Index);//ID
    bool s18(std::vector<char> Input, unsigned int& Index);//ID
    bool s19(std::vector<char> Input, unsigned int& Index);//ID
    bool s20(std::vector<char> Input, unsigned int& Index);//ID
    bool s21(std::vector<char> Input, unsigned int& Index);//FACTS
    bool s22(std::vector<char> Input, unsigned int& Index);//ID
    bool s23(std::vector<char> Input, unsigned int& Index);//ID
    bool s24(std::vector<char> Input, unsigned int& Index);//ID
    bool s25(std::vector<char> Input, unsigned int& Index);//ID
    bool s26(std::vector<char> Input, unsigned int& Index);//RULES
    bool s27(std::vector<char> Input, unsigned int& Index);//ID
    bool s28(std::vector<char> Input, unsigned int& Index);//ID
    bool s29(std::vector<char> Input, unsigned int& Index);//ID
    bool s30(std::vector<char> Input, unsigned int& Index);//ID
    bool s31(std::vector<char> Input, unsigned int& Index);//ID
    bool s32(std::vector<char> Input, unsigned int& Index);//ID
    bool s33(std::vector<char> Input, unsigned int& Index);//QUERIES
    bool s34(std::vector<char> Input, unsigned int& Index);//ID
    bool s35(std::vector<char> Input, unsigned int& Index);//UNDEFINED
    bool s36(std::vector<char> Input, unsigned int& Index);//sub string
    bool s37(std::vector<char> Input, unsigned int& Index);//sub string
    bool s38(std::vector<char> Input, unsigned int& Index);//STRING
    bool s39(std::vector<char> Input, unsigned int& Index);//sub comment
    bool s40(std::vector<char> Input, unsigned int& Index);//COMMENT
    bool s41(std::vector<char> Input, unsigned int& Index);//sub comment
    bool s42(std::vector<char> Input, unsigned int& Index);//sub comment
    bool s43(std::vector<char> Input, unsigned int& Index);//COMMENT
    bool s44(std::vector<char> Input, unsigned int& Index);//UNDEFINED
    bool s45(std::vector<char> Input, unsigned int& Index);//EOF
    
private:
    unsigned int Token_counter;
    unsigned int Line_counter;
    unsigned int Token_starting_line;
    std::stringstream Token_list;
    std::stringstream Stringholder;
    bool (analyzer::*CurrentState)(std::vector<char> Input, unsigned int& Index);
    
    std::stringstream tokenHolder;
    std::stack<std::string> _Token_list;
    std::stack<std::string> _Flip_assist;
};

#endif /* Analyzer_h */





