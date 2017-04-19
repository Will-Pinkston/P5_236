//
//  Predicate.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/9/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Predicate_h
#define Predicate_h

#include <queue>
#include <sstream>

#include "Parameter.h"
#include "Parameter_string.h"
#include "Parameter_id.h"
#include "Parameter_expression.h"

class predicate {
public:
    predicate(std::string initId);
    bool addParam(std::string paramToken);
    bool fillExpression(std::string tokenName, std::string tokenContents);
    bool fillExpression2(std::string tokenName);
    std::string toString();
    
    std::string getId();
    std::queue<parameter*> getParameterList();
    
    bool popParameter();
private:
    std::string _Id;
    std::queue<parameter*> parameterList;
    parameter_expression* openExpression;
    bool expressionSwitch;
    enum expSwitch {off = 0, on = 1};
    int parenCount;
};

#endif /* Predicate_h */
