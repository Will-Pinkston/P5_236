//
//  Parameter_expression.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Parameter_expression.h"

parameter_expression::parameter_expression()
{
    _type = "EXPRESSION";
    _leftParam = NULL;
    _rightParam = NULL;
    operatorSet = false;
}

parameter* parameter_expression::getLeft()
{
    return _leftParam;
}
parameter* parameter_expression::getRight()
{
    return _rightParam;
}

bool parameter_expression::addExpression()
{
    if (_leftParam == NULL)
    {
        _leftParam = new parameter_expression;
        return true;
    }
    if (_leftParam->getType() == "EXPRESSION")
    {
        if (_leftParam->addExpression()) return true;
    }
    if (_rightParam == NULL)
    {
        _rightParam = new parameter_expression;
        return true;
    }
    if (_rightParam->getType() == "EXPRESSION")
    {
        if (_rightParam->addExpression()) return true;
    }
    return false;
}

bool parameter_expression::addOperator(char operatorToken)
{
    if (_leftParam != NULL)
    {
        if (_leftParam->getType() == "EXPRESSION" && _leftParam->addOperator(operatorToken)) return true;
    }
    if (!operatorSet)
    {
        _operator = operatorToken;
        operatorSet = true;
        return true;
    }
    if (_rightParam != NULL)
    {
        if (_rightParam->getType() == "EXPRESSION" && _rightParam->addOperator(operatorToken)) return true;
    }
    return false;
}

bool parameter_expression::addID(std::string idToken)
{
    if (_leftParam == NULL)
    {
        _leftParam = new parameter_id(idToken);
        return true;
    }
    if (_leftParam->getType() == "EXPRESSION")
    {
        if (_leftParam->addID(idToken)) return true;
    }
    if (_rightParam == NULL)
    {
        _rightParam = new parameter_id(idToken);
        return true;
    }
    if (_rightParam->getType() == "EXPRESSION")
    {
        if (_rightParam->addID(idToken)) return true;
    }
    return false;
}

bool parameter_expression::addString(std::string stringToken)
{
    if (_leftParam == NULL)
    {
        _leftParam = new parameter_string(stringToken);
        return true;
    }
    if (_leftParam->getType() == "EXPRESSION")
    {
        if (_leftParam->addString(stringToken)) return true;
    }
    if (_rightParam == NULL)
    {
        _rightParam = new parameter_string(stringToken);
        return true;
    }
    if (_rightParam->getType() == "EXPRESSION")
    {
        if (_rightParam->addString(stringToken)) return true;
    }
    return false;
}

bool parameter_expression::checkComplete()
{
    bool left = false;
    bool here = false;
    bool right = false;
    
    if (_leftParam != NULL)
    {
        left = _leftParam->checkComplete();
    }
    if (operatorSet) here = true;
    if (_rightParam != NULL)
    {
        right = _rightParam->checkComplete();
    }
    
    return (left && here && right);
}

std::string parameter_expression::toString()
{
    std::stringstream retVal;
    retVal << "(" << _leftParam->toString() << _operator << _rightParam->toString() << ")";
    return retVal.str();
}






