//
//  datalogProgram.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/9/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "datalogProgram.h"

datalogProgram::datalogProgram()
{
    currentPredicate = NULL;
    currentRule = NULL;
    
    schemeSwitch = false;
    factSwitch = false;
    ruleSwitch = false;
    querySwitch = false;
}

bool datalogProgram::addToken2(std::string inToken)
{
    if (currentPredicate == NULL)
    {
        currentPredicate = new predicate(inToken);
        return true;
    }
    
    if (currentPredicate->addParam(inToken)) return true;
    
    return false;
}

bool datalogProgram::addToken(std::string inToken)
{
    if (schemeSwitch || factSwitch || querySwitch)
    {
        return addToken2(inToken);
    }
    else if (ruleSwitch)
    {
        if (currentRule == NULL)
        {
            currentRule = new rule(inToken);
            return true;
        }
        if (currentRule->addParam(inToken)) return true;
    }
    return false;
}

bool datalogProgram::setScheme()
{
    schemeSwitch = true;
    factSwitch = false;
    ruleSwitch = false;
    querySwitch = false;
    return true;
}
bool datalogProgram::setFact()
{
    schemeSwitch = false;
    factSwitch = true;
    ruleSwitch = false;
    querySwitch = false;
    return true;
}
bool datalogProgram::setRule()
{
    schemeSwitch = false;
    factSwitch = false;
    ruleSwitch = true;
    querySwitch = false;
    return true;
}
bool datalogProgram::setQuery()
{
    schemeSwitch = false;
    factSwitch = false;
    ruleSwitch = false;
    querySwitch = true;
    return true;
}

bool datalogProgram::endPredicate()
{
    if (schemeSwitch)
    {
        _Schemes.push(*currentPredicate);
        currentPredicate = NULL;
        return true;
    }
    else if (factSwitch)
    {
        _Facts.push(*currentPredicate);
        currentPredicate = NULL;
        return true;
    }
    else if (ruleSwitch)
    {
        return currentRule->endPredicate();
    }
    else if (querySwitch)
    {
        _Queries.push(*currentPredicate);
        currentPredicate = NULL;
        return true;
    }
    return false;
}

bool datalogProgram::endRule()
{
    _Rules.push(*currentRule);
    currentRule = NULL;
    return true;
}

std::string datalogProgram::toString()
{
    std::stringstream retVal;
    int schemesSize = (int)_Schemes.size();
    retVal << "Schemes(" << schemesSize << "):" << std::endl;
    for (int i = 0; i < schemesSize; i++)
    {
        retVal << "\t" << _Schemes.front().toString() << std::endl;
        _Schemes.pop();
    }
    
    int factsSize = (int)_Facts.size();
    retVal << "Facts(" << factsSize << "):" << std::endl;
    for (int i = 0; i < factsSize; i++)
    {
        retVal << "\t" << _Facts.front().toString() << "." << std::endl;
        _Facts.pop();
    }
    
    int rulesSize = (int)_Rules.size();
    retVal << "Rules(" << rulesSize << "):" << std::endl;
    for (int i = 0; i < rulesSize; i++)
    {
        retVal << "\t" << _Rules.front().toString() << std::endl;
        _Rules.pop();
    }
    
    int queriesSize = (int)_Queries.size();
    retVal << "Queries(" << queriesSize << "):" << std::endl;
    for (int i = 0; i < queriesSize; i++)
    {
        retVal << "\t" << _Queries.front().toString() << "?" << std::endl;
        _Queries.pop();
    }
    
    return retVal.str();
}

std::queue<predicate> datalogProgram::getSchemes()
{
    return _Schemes;
}
std::queue<predicate> datalogProgram::getFacts()
{
    return _Facts;
}
std::queue<rule> datalogProgram::getRules()
{
    return _Rules;
}
std::queue<predicate> datalogProgram::getQueries()
{
    return _Queries;
}






