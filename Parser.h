//
//  Parser.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 2/21/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Parser_h
#define Parser_h

#include <stack>
#include <sstream>
#include <stdio.h>
#include <string>
#include <iostream>
#include <set>

#include "datalogProgram.h"

class parser {
public:
    parser(std::stack<std::string>& tokens);
    
    void getCurrentToken();
//    bool check(std::string expected_Token);
//    std::string lookAhead(std::stack<std::string> tokens_copy);
    void addToDomain(std::string token);
    void printDomain();
    
    bool run();
    
    bool _datalogProgram();
    
    bool schemeHelper();
    bool factHelper();
    bool ruleHelper();
    bool queryHelper();
    
    bool _scheme();
    bool _schemeList();
    bool _idList();
    bool _fact();
    bool _factList();
    bool _rule();
    bool _ruleList();
    bool _headPredicate();
    bool _predicate();
    bool _predicateList();
    bool _parameter();
    bool _parameterList();
    bool _expression();
    bool _operator();
    bool _query();
    bool _queryList();
    bool _stringList();
    
    datalogProgram* getProgram();
private:
    std::stack<std::string> _Tokens;
    std::string _Current_Token;
    std::set<std::string> _Domain;
    
    datalogProgram _Program;
};

#endif /* Parser_h */






