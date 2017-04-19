//
//  Rule.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Rule.h"

rule::rule(std::string initID)
{
    headPredicate = new predicate(initID);
    headComplete = false;
    currentPredicate = NULL;
}

bool rule::addParam(std::string inParam)
{
    if (!headComplete)
    {
         return headPredicate->addParam(inParam);
    }
    if (currentPredicate == NULL)
    {
        currentPredicate = new predicate(inParam);
        return true;
    }
    return currentPredicate->addParam(inParam);
}

bool rule::endPredicate()
{
    if (!headComplete)
    {
        headComplete = true;
        return true;
    }
    predicateList.push(*currentPredicate);
    currentPredicate = NULL;
    return true;
}

std::string rule::toString()
{
    std::stringstream retVal;
    retVal << headPredicate->toString() << " :- " << predicateList.front().toString();
    predicateList.pop();
    int numPredicates = (int)predicateList.size();
    for (int i = 0; i < numPredicates; i++)
    {
        retVal << "," << predicateList.front().toString();
        predicateList.pop();
    }
    retVal << ".";
    return retVal.str();
}

//part 4
std::queue<predicate> rule::getPredicates()
{
    return predicateList;
}

predicate rule::getHead()
{
    return *headPredicate;
}



