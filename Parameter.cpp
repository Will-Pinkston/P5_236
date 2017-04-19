//
//  Parameter.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/9/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Parameter.h"

std::string parameter::getType()
{
    return _type;
}

//functions for expressions
parameter* parameter::getLeft() {return NULL;}
parameter* parameter::getRight() {return NULL;}
bool parameter::addExpression() {return false;}
bool parameter::addOperator(char operatorToken) {return false;}
bool parameter::addID(std::string idToken) {return false;}
bool parameter::addString(std::string stringToken) {return false;}
bool parameter::checkComplete() {return false;}

std::string parameter::toString()
{
    return "unclassed parameter";
}
