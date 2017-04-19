//
//  Analyzer.cpp
//  Lexical_Analyzer_p1
//
//  Created by William Pinkston on 2/2/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Analyzer.h"
#include <stack>

analyzer::analyzer()
{
    CurrentState = &analyzer::s0;
    Token_counter = 0;
    Line_counter = 1;
};

std::stack<std::string> analyzer::flipStack()
{
    while(!_Token_list.empty())
    {
        _Flip_assist.push(_Token_list.top());
        _Token_list.pop();
    }
    return _Flip_assist;
}



//brain of the FSA
std::stack<std::string> analyzer::run(std::vector<char> Input)
{
    unsigned int Index = 0;
    bool Result = (this->*CurrentState)(Input,Index);
    while (CurrentState != nullptr && Result)
    {
        Result = (this->*CurrentState)(Input, Index);
    }
//    tokenHolder << "Total Tokens = " << Token_counter << std::endl;
//    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    _Token_list = flipStack();
    //std::cout << Token_list.str();
    return _Token_list;
}



bool analyzer::s0(std::vector<char> Input, unsigned int& Index)//WHITESPACE
{
    //std::cout << Input[Index];
    if (isspace(Input[Index]))
    {
        if (Input[Index] == '\n' || Input[Index] == '\r')
        {
            Line_counter++;
        }
        Index++;
        return true;
    }
    
    switch (Input[Index]) {
        case ',':
        {
            //std::cout << "COMMA" << std::endl;
            CurrentState = &analyzer::s1;
        }
            break;
        case '.':
        {
            //std::cout << "PERIOD" << std::endl;
            CurrentState = &analyzer::s2;
        }
            break;
        case '?':
        {
            //std::cout << "Q_MARK" << std::endl;
            CurrentState = &analyzer::s3;
        }
            break;
        case '(':
        {
            //std::cout << "LEFT_PAREN" << std::endl;
            CurrentState = &analyzer::s4;
        }
            break;
        case ')':
        {
            //std::cout << "RIGHT_PAREN" << std::endl;
            CurrentState = &analyzer::s5;
        }
            break;
        case ':':
        {
            //std::cout << "COLON" << std::endl;
            CurrentState = &analyzer::s6;
        }
            break;
        case '*':
        {
            //std::cout << "MULTIPLY" << std::endl;
            CurrentState = &analyzer::s8;
        }
            break;
        case '+':
        {
            //std::cout << "ADD" << std::endl;
            CurrentState = &analyzer::s9;
        }
            break;
        case '\0'://keep an eye on this
        {
            //std::cout << "We've reached the end" << std::endl;
            CurrentState = &analyzer::s45;
        }
            break;
        case 'S':
        {
            //std::cout << "S" << std::endl;
            CurrentState = &analyzer::s10;
            Stringholder << "S";
        }
            break;
        case 'F':
        {
            //std::cout << "F" << std::endl;
            CurrentState = &analyzer::s17;
            Stringholder << "F";
        }
            break;
        case 'R':
        {
            //std::cout << "R" << std::endl;
            CurrentState = &analyzer::s22;
            Stringholder << "R";
        }
            break;
        case 'Q':
        {
            //std::cout << "Q" << std::endl;
            CurrentState = &analyzer::s27;
            Stringholder << "Q";
        }
            break;
        case '\'':
        {
            //std::cout << "String started" << std::endl;
            CurrentState = &analyzer::s36;
            Stringholder << "'";
            Token_starting_line = Line_counter;
        }
            break;
        case '#':
        {
            //std::cout << "Comment started" << std::endl;
            CurrentState = &analyzer::s38;
            Stringholder << "#";
            Token_starting_line = Line_counter;
        }
            break;
        default:
        {
            if (isalpha(Input[Index]))
            {
                CurrentState = &analyzer::s34;
                Stringholder << Input[Index];
            }
            else
            {
                CurrentState = &analyzer::s44;
                Stringholder << Input[Index];
                Index++;
            }
            
        }
            break;
    }
    return true;
}

bool analyzer::s1(std::vector<char> Input, unsigned int& Index)//COMMA
{
    Token_counter++;
    
    tokenHolder << "(COMMA,\",\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s2(std::vector<char> Input, unsigned int& Index)//PERIOD
{
    Token_counter++;
    tokenHolder << "(PERIOD,\".\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s3(std::vector<char> Input, unsigned int& Index)//Q_MARK
{
    Token_counter++;
    tokenHolder << "(Q_MARK,\"?\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s4(std::vector<char> Input, unsigned int& Index)//LEFT_PAREN
{
    Token_counter++;
    tokenHolder << "(LEFT_PAREN,\"(\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s5(std::vector<char> Input, unsigned int& Index)//RIGHT_PAREN
{
    Token_counter++;
    tokenHolder << "(RIGHT_PAREN,\")\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s6(std::vector<char> Input, unsigned int& Index)//COLON
{
    Index++;
    if (Input[Index] == '-')
    {
        CurrentState = &analyzer::s7;
    }
    else
    {
        Token_counter++;
        tokenHolder << "(COLON,\":\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s7(std::vector<char> Input, unsigned int& Index)//COLON_DASH
{
    Token_counter++;
    tokenHolder << "(COLON_DASH,\":-\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s8(std::vector<char> Input, unsigned int& Index)//MULTIPLY
{
    Token_counter++;
    tokenHolder << "(MULTIPLY,\"*\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s9(std::vector<char> Input, unsigned int& Index)//ADD
{
    Token_counter++;
    tokenHolder << "(ADD,\"+\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    Index++;
    return true;
}

bool analyzer::s10(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'c')
    {
        CurrentState = &analyzer::s11;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s11(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'h')
    {
        CurrentState = &analyzer::s12;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s12(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'e')
    {
        CurrentState = &analyzer::s13;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder<< "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s13(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'm')
    {
        CurrentState = &analyzer::s14;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s14(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'e')
    {
        CurrentState = &analyzer::s15;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s15(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 's')
    {
        CurrentState = &analyzer::s16;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s16(std::vector<char> Input, unsigned int& Index)//SCHEMES
{
    Index++;
    if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(SCHEMES,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s17(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'a')
    {
        CurrentState = &analyzer::s18;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s18(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'c')
    {
        CurrentState = &analyzer::s19;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s19(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 't')
    {
        CurrentState = &analyzer::s20;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s20(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 's')
    {
        CurrentState = &analyzer::s21;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s21(std::vector<char> Input, unsigned int& Index)//FACTS
{
    Index++;
    if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(FACTS,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s22(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'u')
    {
        CurrentState = &analyzer::s23;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s23(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'l')
    {
        CurrentState = &analyzer::s24;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s24(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'e')
    {
        CurrentState = &analyzer::s25;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s25(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 's')
    {
        CurrentState = &analyzer::s26;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s26(std::vector<char> Input, unsigned int& Index)//RULES
{
    Index++;
    if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(RULES,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s27(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'u')
    {
        CurrentState = &analyzer::s28;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s28(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'e')
    {
        CurrentState = &analyzer::s29;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s29(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'r')
    {
        CurrentState = &analyzer::s30;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s30(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'i')
    {
        CurrentState = &analyzer::s31;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s31(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 'e')
    {
        CurrentState = &analyzer::s32;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s32(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (Input[Index] == 's')
    {
        CurrentState = &analyzer::s33;
        Stringholder << Input[Index];
    }
    else if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s33(std::vector<char> Input, unsigned int& Index)//QUERIES
{
    Index++;
    if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(QUERIES,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s34(std::vector<char> Input, unsigned int& Index)//ID
{
    Index++;
    if (isalnum(Input[Index]))
    {
        CurrentState = &analyzer::s34;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(ID,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s35(std::vector<char> Input, unsigned int& Index)//UNDEFINED ...chopped strings and multi-line comments
{
    Token_counter++;
    tokenHolder << "(UNDEFINED,\"" << Stringholder.str() << "\"," << Token_starting_line << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    CurrentState = &analyzer::s0;
    return true;
}

bool analyzer::s36(std::vector<char> Input, unsigned int& Index)//sub string
{
    Index++;
    if (Input[Index] == '\'')
    {
        CurrentState = &analyzer::s37;
        Stringholder << Input[Index];
    }
    else if (Input[Index] == '\0')
    {
        CurrentState = &analyzer::s35;
        //Stringholder << Input[Index];
    }
    else
    {
        if (Input[Index] == '\n' || Input[Index] == '\r')
        {
            Line_counter++;
        }
        CurrentState = &analyzer::s36;
        Stringholder << Input[Index];
    }
    return true;
}

bool analyzer::s37(std::vector<char> Input, unsigned int& Index)//STRING
{
    Index++;
    if (Input[Index] == '\'')
    {
        CurrentState = &analyzer::s36;
        Stringholder << Input[Index];
    }
    else
    {
        Token_counter++;
        tokenHolder << "(STRING,\"" << Stringholder.str() << "\"," << Token_starting_line << ")" << std::endl;
        _Token_list.push(tokenHolder.str());
        tokenHolder.str(std::string());
        Stringholder.str(std::string());
        CurrentState = &analyzer::s0;
    }
    return true;
}

bool analyzer::s38(std::vector<char> Input, unsigned int& Index)//sub comment
{
    Index++;
    if (Input[Index] == '|')
    {
        CurrentState = &analyzer::s41;
        Stringholder << "|";
    }
    else if (Input[Index] == '\r' || Input[Index] == '\n' || Input[Index] == '\0')
    {
        CurrentState = &analyzer::s40;
    }
    else
    {
        CurrentState = &analyzer::s39;
        Stringholder << Input[Index];
    }
    return true;
}

bool analyzer::s39(std::vector<char> Input, unsigned int& Index)//sub comment
{
    Index++;
    if (Input[Index] == '\r' || Input[Index] == '\n' || Input[Index] == '\0')
    {
        CurrentState = &analyzer::s40;
    }
    else
    {
        CurrentState = &analyzer::s39;
        Stringholder << Input[Index];
    }
    return true;
}

bool analyzer::s40(std::vector<char> Input, unsigned int& Index)//COMMENT
{
    Token_counter++;
    tokenHolder << "(COMMENT,\"" << Stringholder.str() << "\"," << Token_starting_line << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    Stringholder.str(std::string());
    CurrentState = &analyzer::s0;
    return true;
}

bool analyzer::s41(std::vector<char> Input, unsigned int& Index)//sub comment
{
    Index++;
    if (Input[Index] == '\0')
    {
        //Stringholder << Input[Index];
        CurrentState = &analyzer::s35;
    }
    else if (Input[Index] == '|')
    {
        Stringholder << Input[Index];
        CurrentState = &analyzer::s42;
    }
    else
    {
        if (Input[Index] == '\n' || Input[Index] == '\r')
        {
            Line_counter++;
        }
        Stringholder << Input[Index];
        CurrentState = &analyzer::s41;
    }
    return true;
}

bool analyzer::s42(std::vector<char> Input, unsigned int& Index)//sub comment
{
    Index++;
    Stringholder << Input[Index];
    if (Input[Index] == '#')
    {
        CurrentState = &analyzer::s43;
    }
    else if (Input[Index] == '\0')
    {
        CurrentState = &analyzer::s35;
    }
    else
    {
        if (Input[Index] == '\n' || Input[Index] == '\r')
        {
            Line_counter++;
        }
        CurrentState = &analyzer::s41;
    }
    return true;
}

bool analyzer::s43(std::vector<char> Input, unsigned int& Index)//COMMENT
{
    Index++;
    Token_counter++;
    tokenHolder << "(COMMENT,\"" << Stringholder.str() << "\"," << Token_starting_line << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    Stringholder.str(std::string());
    CurrentState = &analyzer::s0;
    return true;
}

bool analyzer::s44(std::vector<char> Input, unsigned int& Index)//UNDEFINED
{
    Token_counter++;
    tokenHolder << "(UNDEFINED,\"" << Stringholder.str() << "\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    Stringholder.str(std::string());
    CurrentState = &analyzer::s0;
    return true;
}

bool analyzer::s45(std::vector<char> Input, unsigned int& Index)//EOF
{
    Token_counter++;
    tokenHolder << "(EOF,\"\"," << Line_counter << ")" << std::endl;
    _Token_list.push(tokenHolder.str());
    tokenHolder.str(std::string());
    return false;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//Helper functions

//bool isalnum(char check) checks if is alphanumeric character

