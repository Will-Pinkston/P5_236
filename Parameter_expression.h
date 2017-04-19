//
//  Parameter_expression.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Parameter_expression_h
#define Parameter_expression_h

#include <sstream>

#include "Parameter.h"
#include "Parameter_id.h"
#include "Parameter_string.h"

class parameter_expression: public parameter {
public:
    parameter_expression();
    parameter* getLeft();
    parameter* getRight();
    
    bool addExpression();
    bool addOperator(char operatorToken);
    bool addID(std::string idToken);
    bool addString(std::string stringToken);
    bool checkComplete();
    
    std::string toString();
protected:
    parameter* _leftParam;
    char _operator;
    bool operatorSet;
    parameter* _rightParam;
};

//LEFT_PAREN parameter operator parameter RIGHT_PAREN

#endif /* Parameter_expression_h */
