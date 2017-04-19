//
//  Rule.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Rule_h
#define Rule_h

#include <queue>
#include <sstream>

#include "Predicate.h"

class rule
{
public:
    rule(std::string initID);
    bool addParam(std::string inParam);
    bool endPredicate();
    
    std::string toString();
    
    std::queue<predicate> getPredicates();
    
    predicate getHead();
private:
    predicate* headPredicate;
    predicate* currentPredicate;
    std::queue<predicate> predicateList;
    
    bool headComplete;
};

//rule => headPredicate COLON_DASH predicate predicateList PERIOD
#endif /* Rule_h */
