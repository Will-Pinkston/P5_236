//
//  Database.h
//  Relational_database_p3_part_2
//
//  Created by William Pinkston on 3/25/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Database_h
#define Database_h

#include <vector>

#include "Relation.h"
#include "Parser.h"
#include "Graph.h"

class database
{
public:
    database(datalogProgram &Program);
    std::vector<std::string> getParameters(std::queue<parameter*> holdParameterList);
    
    std::string answerQueries();
    std::string evalQuery(int &relationSelect, std::vector<parameter*> &parameterList);
    std::set<tuple, relation::tuple_compare> getQuery(int relationSelect, std::vector<parameter*> &parameterList); //for rules
    bool evalHelper(std::vector<parameter*>& parameterList, int i, int relationSelect, std::vector<std::string>& projectionHolder);
    
    std::string answerToString(std::set<tuple, relation::tuple_compare> &response, std::vector<std::string> &responseMap);
    
    //part 4
    bool relUnion (relation* rLeft, relation &rRight);
    relation relJoin (relation &rLeft, relation &rRight);
    //join helper functions
    bool rightCriteriaFinder(std::vector<std::string> &rightCriteria, std::vector<int> &rightFound, std::vector<std::string> &rMap);
    bool leftCriteriaFinder(std::vector<std::string> &leftCriteria,relation &rLeft);
    bool checkFailConditions(std::vector<std::string> &leftCriteria,
                             std::vector<std::string> &rightCriteria,
                             relation &rLeft, relation &rRight,
                             std::vector<int> &rightFound,
                             bool &leftFoundTest);
    bool relJoinHelper(int leftSize, int rightSize,
                       std::vector<int> &leftFound,
                       std::vector<int> &rightFound,
                       std::set<tuple, relation::tuple_compare> &rightTuples,
                       std::set<tuple, relation::tuple_compare>::iterator leftCounter,
                       relation &retVal);
    bool relJoinCheckParallel(std::vector<int> &leftFound,
                              std::vector<int> &rightFound,
                              std::set<tuple, relation::tuple_compare>::iterator leftCounter,
                              std::set<tuple, relation::tuple_compare>::iterator rightCounter);
    bool addNonParallel(std::vector<std::string> &jointAttributes,std::set<tuple, relation::tuple_compare>::iterator rightCounter, std::vector<int> &rightFound);
    
    
    relation crossProduct (relation &rLeft, relation &rRight);
    bool addAttributes(std::vector<std::string> &hold,
                       std::set<tuple, relation::tuple_compare>::iterator counter);
    bool removeAttributes(std::vector<std::string> &hold, int numAttributes);
    std::string fillRules();
    bool evalRule(rule &check);
    bool evalRuleHelper(std::vector<std::string> &headMap, relation &projected);
    int findRelation(std::string relName);
    std::vector<std::string> findJoin(relation &rLeft, relation &rRight);
    
    //part 5
    std::vector<rule> getRules();
    bool checkTrivial(std::set<graph::node*, graph::node_compare>& here);
    bool checkChildrenForLoop(graph::childNode* here, int check);
    int ruleFillHelper(std::set<graph::node*, graph::node_compare>::iterator innerCounter,
                       std::vector<std::set<graph::node*, graph::node_compare>> &rulesDAG,
                       int &i);
private:
    std::vector<relation*> _relations;
    std::queue<predicate> _queries;
    std::vector<rule> _rules;
};










#endif /* Database_h */
