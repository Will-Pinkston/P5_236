//
//  datalogProgram.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/9/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef datalogProgram_h
#define datalogProgram_h

#include <queue>
#include <sstream>

#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Parameter_string.h"
#include "Parameter_id.h"
#include "Parameter_expression.h"

class datalogProgram {
public:
    datalogProgram();
    bool addToken(std::string inToken);
    bool addToken2(std::string inToken);
    
    bool setScheme();
    bool setFact();
    bool setRule();
    bool setQuery();
    
    bool endPredicate();
    bool endRule();
    
    std::string toString();
    
    std::queue<predicate> getSchemes();
    std::queue<predicate> getFacts();
    std::queue<rule> getRules();
    std::queue<predicate> getQueries();
private:
    std::queue<predicate> _Schemes;
    std::queue<predicate> _Facts;
    std::queue<rule> _Rules;
    std::queue<predicate> _Queries;
    
    predicate* currentPredicate;
    rule* currentRule;
    
    bool schemeSwitch;
    bool factSwitch;
    bool ruleSwitch;
    bool querySwitch;
};

#endif /* datalogProgram_h */
