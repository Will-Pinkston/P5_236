//
//  Database.cpp
//  Relational_database_p3_part_2
//
//  Created by William Pinkston on 3/25/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Database.h"
#include <algorithm>

database::database(datalogProgram &Program)
{
    std::queue<predicate> Schemes = Program.getSchemes();
    int numSchemes = (int)Schemes.size();
    for (int i = 0; i < numSchemes; i++)
    {
        std::queue<parameter*> holdParameterList = Schemes.front().getParameterList();
        std::vector<std::string> schemeIDs = getParameters(holdParameterList);
        relation* holdRelation = new relation(Schemes.front().getId(), schemeIDs);
        _relations.push_back(holdRelation);
        Schemes.pop();
    }
    
    std::queue<predicate> Facts = Program.getFacts();
    int numFacts = (int)Facts.size();
    for (int i = 0; i < numFacts; i++)
    {
        std::queue<parameter*> holdParameterList = Facts.front().getParameterList();
        std::vector<std::string> factStrings = getParameters(holdParameterList);
        
        std::string factName = Facts.front().getId();
        for (int i = 0; i < _relations.size(); i++)
        {
            if (factName == _relations[i]->getName())
            {
                _relations[i]->addTuple(factStrings);
            }
        }
        Facts.pop();
    }
    
    _queries = Program.getQueries();
    std::queue<rule> ruleHold = Program.getRules();
    int loopSize = (int)ruleHold.size();
    for (int i = 0; i < loopSize; i++)
    {
        _rules.push_back(ruleHold.front());
        ruleHold.pop();
        
    }
}

std::vector<std::string> database::getParameters(std::queue<parameter*> holdParameterList)
{
    std::vector<std::string> parameters;
    int numParams = (int)holdParameterList.size();
    for (int j = 0; j < numParams; j++)
    {
        parameters.push_back(holdParameterList.front()->toString());
        holdParameterList.pop();
    }
    return parameters;
}


std::string database::answerQueries()
{
    std::stringstream retVal;
//    retVal << "\n";
    int numQueries = (int)_queries.size();
    for (int i = 0; i < numQueries; i++)
    {
        std::queue<parameter*> queryParametersQ = _queries.front().getParameterList();
        std::vector<parameter*> queryParameters;
        int numParam = (int)queryParametersQ.size();
        for (int i = 0; i < numParam; i++)
        {
            queryParameters.push_back(queryParametersQ.front());
            queryParametersQ.pop();
        }
        
        retVal << _queries.front().toString() << "?";
        std::string queryName = _queries.front().getId();
        for (int j = 0; j < _relations.size(); j++)
        {
            if (queryName == _relations[j]->getName())
            {
                retVal << evalQuery(j, queryParameters);
            }
        }
        _queries.pop();
    }
    std::string retValStr = retVal.str();
    retValStr = retValStr.substr(0, retValStr.length() - 1);
    return retValStr;
}

std::string database::evalQuery(int &relationSelect, std::vector<parameter*> &parameterList)
{
    _relations[relationSelect]->clearProjectionMap();
    _relations[relationSelect]->resetBaseMap();
    _relations[relationSelect]->startInner();
    
    std::vector<std::string> projectionHolder;
    
    for (int i = 0; i < parameterList.size(); i++)
    {
        evalHelper(parameterList, i, relationSelect, projectionHolder);
    }
    if (projectionHolder.size() != 0)
    {
        _relations[relationSelect]->innerProject(projectionHolder);
    }
    
    std::set<tuple, relation::tuple_compare> response(_relations[relationSelect]->endInner());
    std::vector<std::string> responseMap = _relations[relationSelect]->getMap();
    std::string retVal;
    if (responseMap.size() == 0)
    {
        if (response.size() == 0)
        {
            retVal = " No\n";
        }
        else retVal = " Yes(1)\n";
    }
    else retVal = answerToString(response,responseMap);
    return retVal;
}

std::set<tuple, relation::tuple_compare> database::getQuery(int relationSelect, std::vector<parameter*> &parameterList)
{
    _relations[relationSelect]->clearProjectionMap();
    _relations[relationSelect]->resetBaseMap();
    _relations[relationSelect]->startInner();
    
    std::vector<std::string> projectionHolder;
    
    for (int i = 0; i < parameterList.size(); i++)
    {
        evalHelper(parameterList, i, relationSelect, projectionHolder);
    }
    if (projectionHolder.size() != 0)
    {
        _relations[relationSelect]->innerProject(projectionHolder);
    }
    
    std::set<tuple, relation::tuple_compare> response(_relations[relationSelect]->endInner());
    return response;
}


bool database::evalHelper(std::vector<parameter*>& parameterList, int i, int relationSelect, std::vector<std::string>& projectionHolder)
{
    std::string paramType = parameterList[i]->getType();
    if (paramType == "ID")
    {
        _relations[relationSelect]->rename(i, parameterList[i]->toString());
        bool parallel = false;
        for (int j = 0; j < projectionHolder.size(); j++)
        {
            if (parameterList[i]->toString() == projectionHolder[j])
            {
                _relations[relationSelect]->innerSelectParallel(parameterList[i]->toString());
                parallel = true;
            }
        }
        if (!parallel) projectionHolder.push_back(parameterList[i]->toString());
    }
    else if (paramType == "STRING")
    {
        _relations[relationSelect]->innerSelect(i, parameterList[i]->toString());
    }
    return true;
}

std::string database::answerToString(std::set<tuple, relation::tuple_compare> &response, std::vector<std::string> &responseMap)
{
    std::stringstream retVal;
    
    if (response.size() == 0)
    {
        retVal << " No\n";
    }
    else
    {
        std::set<tuple, relation::tuple_compare>::iterator tupleCounter = response.begin();
        retVal << " Yes(" << response.size() << ")\n";
        for (int i = 0; i < response.size(); i++)
        {
            retVal << "  ";
            retVal << responseMap[0] << "=" << tupleCounter->getAttribute(0);
            for (int j = 1; j < responseMap.size(); j++)
            {
                retVal << ", " << responseMap[j] << "=" << tupleCounter->getAttribute(j);
            }
            retVal << "\n";
            tupleCounter++;
        }
    }
    
    return retVal.str();
}

//part 4 
bool database::relUnion (relation* rLeft, relation &rRight) //left copy into, right copy from
{
    if (rLeft->getName() != rRight.getName()) return false;
    
    std::set<tuple, relation::tuple_compare> holdTuples = rRight.getTuples();
    
    std::set<tuple, relation::tuple_compare>::iterator tupleCounter = holdTuples.begin();
    
    std::vector<std::string> mapL = rLeft->getMapOriginal();
    std::vector<std::string> mapR = rRight.getMapOriginal();
    int mapSize = (int)mapL.size();
    int numTuples = (int)rRight.getTuples().size();
    std::vector<std::string> hold;
    
    for (int h = 0; h < numTuples; h++)//tuples in right relation
    {
        for (int i = 0; i < mapSize; i++)//left
        {
            for (int j = 0; j < mapSize; j++)//right
            {
                if (mapL[i] == mapR[j])
                {
                    hold.push_back(tupleCounter->getAttribute(j));
                }
            }
        }
        rLeft->addTuple(hold);
        while (hold.size() != 0) hold.pop_back();
        tupleCounter++;
    }
    
    return true;
}

relation database::crossProduct(relation &rLeft, relation &rRight)
{
    std::vector<std::string> crossMap = rLeft.getMapOriginal();
    for (int i = 0; i < rRight.getMapOriginal().size(); i++)
    {
        crossMap.push_back(rRight.getMapOriginal()[i]);
    }
    relation retVal(rLeft.getName(), crossMap);
    
    std::set<tuple, relation::tuple_compare> leftTuples = rLeft.getTuples();
    std::set<tuple, relation::tuple_compare> rightTuples = rRight.getTuples();
    
    std::set<tuple, relation::tuple_compare>::iterator leftCounter = leftTuples.begin();
    for (int i = 0; i < rLeft.getSize(); i++)//each left tuple
    {
        std::vector<std::string> hold;
        std::set<tuple, relation::tuple_compare>::iterator rightCounter = rightTuples.begin();
        int numValues = (int)rightCounter->getAllAttributes().size();
        addAttributes(hold, leftCounter);

        for (int j = 0; j < rRight.getSize(); j++)
        {
            addAttributes(hold, rightCounter);
            retVal.addTuple(hold);
            removeAttributes(hold, numValues);
            rightCounter++;
        }
        leftCounter++;
    }
    
    return retVal;
}

bool database::addAttributes(std::vector<std::string> &hold, std::set<tuple, relation::tuple_compare>::iterator counter)
{
//    std::vector<std::string> add;
    for (int i = 0; i < counter->getNumAttributes(); i++)
    {
        hold.push_back(counter->getAttribute(i));
    }
    return true;
}

bool database::removeAttributes(std::vector<std::string> &hold, int numAttributes)
{
    for (int k = 0; k < numAttributes; k++)
    {
        hold.pop_back();
    }
    return true;
}

relation database::relJoin (relation &rLeft, relation &rRight)
{
    std::vector<std::string> leftCriteria = findJoin(rLeft, rRight);
    if (leftCriteria.size() == 0)
    {
        return crossProduct(rLeft, rRight);
    }
    
    
    std::vector<std::string> rightCriteria = leftCriteria;
    
    std::vector<std::string> rMap = rRight.getMapOriginal();
    std::vector<int> rightFound;
    
    //pushes the index to the relation for each id in rightCriteria into rightFound
    rightCriteriaFinder(rightCriteria, rightFound, rMap);
    
    bool leftFoundTest = leftCriteriaFinder(leftCriteria, rLeft);
    std::vector<int> rightFindHelper = rightFound;
    std::sort(rightFindHelper.begin(), rightFindHelper.end());
    
    //constructs schema of the joint relation
    std::vector<std::string> joinMap = rLeft.getMapOriginal();
    
    int helperIndex = 0;
    for (int i = 0; i < rMap.size(); i++)
    {
        if (i == rightFindHelper[helperIndex])
        {
            helperIndex++;
        }
        else joinMap.push_back(rMap[i]);
    }
    
    relation retVal(rLeft.getName() + "_" + rRight.getName() + "_Join", joinMap);
    
    if (!checkFailConditions(leftCriteria, rightCriteria, rLeft, rRight, rightFound, leftFoundTest)) return retVal;
    
    std::vector<int> leftFound;
    
    for (int i = 0; i < leftCriteria.size(); i++)
    {
        leftFound.push_back(rLeft.findInMap(leftCriteria[i]));
    }
    
    std::set<tuple, relation::tuple_compare> leftTuples = rLeft.getTuples();
    std::set<tuple, relation::tuple_compare> rightTuples = rRight.getTuples();
    
    std::set<tuple, relation::tuple_compare>::iterator leftCounter = leftTuples.begin();
    
    relJoinHelper(rLeft.getSize(), rRight.getSize(), leftFound, rightFound, rightTuples, leftCounter, retVal);
    
    return retVal;
}

bool database::rightCriteriaFinder(std::vector<std::string> &rightCriteria, std::vector<int> &rightFound, std::vector<std::string> &rMap)
{
    for (int i = 0; i < rightCriteria.size(); i++)
    {
        for (int j = 0; j < rMap.size(); j++)
        {
            if (rMap[j] == rightCriteria[i])
            {
                rightFound.push_back(j);
            }
        }
    }
    return true;
}

bool database::leftCriteriaFinder(std::vector<std::string> &leftCriteria,relation &rLeft)
{
    for (int i = 0; i < leftCriteria.size(); i++)
    {
        for (int j = 0; j < rLeft.getMapOriginal().size(); j++)
        {
            if (rLeft.getMapOriginal()[j] == leftCriteria[i])
            {
                return true;
            }
        }
    }
    return false;
}

bool database::checkFailConditions(std::vector<std::string> &leftCriteria, std::vector<std::string> &rightCriteria, relation &rLeft, relation &rRight, std::vector<int> &rightFound, bool &leftFoundTest)
{
    if (leftCriteria.size() != rightCriteria.size()) return false;
    if (rightFound.size() == 0 || leftFoundTest == false) return false;
    return true;
}

bool database::relJoinHelper(int leftSize, int rightSize, std::vector<int> &leftFound, std::vector<int> &rightFound, std::set<tuple, relation::tuple_compare> &rightTuples, std::set<tuple, relation::tuple_compare>::iterator leftCounter, relation &retVal)
{
    std::set<tuple, relation::tuple_compare>::iterator rightCounter;
    for (int i = 0; i < leftSize; i++)
    {
        rightCounter = rightTuples.begin();
        for (int j = 0; j < rightSize; j++)
        {
            bool parallel = relJoinCheckParallel(leftFound, rightFound, leftCounter, rightCounter);
            if (parallel)
            {
                std::vector<std::string> jointAttributes;
                addAttributes(jointAttributes, leftCounter);
                addNonParallel(jointAttributes, rightCounter, rightFound);
                retVal.addTuple(jointAttributes);
            }
            rightCounter++;
        }
        leftCounter++;
    }
    return true;
}

bool database::addNonParallel(std::vector<std::string> &jointAttributes,std::set<tuple, relation::tuple_compare>::iterator rightCounter, std::vector<int> &rightFound)
{
    for (int l = 0; l < rightCounter->getNumAttributes(); l++)
    {
        bool skip = false;
        for (int m = 0; m < rightFound.size(); m++)
        {
            if (l == rightFound[m]) skip = true;
        }
        if (!skip) jointAttributes.push_back(rightCounter->getAttribute(l));
    }
    return true;
}

bool database::relJoinCheckParallel(std::vector<int> &leftFound, std::vector<int> &rightFound, std::set<tuple, relation::tuple_compare>::iterator leftCounter, std::set<tuple, relation::tuple_compare>::iterator rightCounter)
{
    for (int k = 0; k < leftFound.size(); k++)
    {
        if (leftCounter->getAttribute(leftFound[k]) != rightCounter->getAttribute(rightFound[k]))
        {
            return false;
        }
    }
    return true;
}

std::string database::fillRules()
{
    //part 5
    
    graph rulesGraph(_rules);
    std::cout << "Dependency Graph" << std::endl;
    rulesGraph.printGraph();
    std::cout << "Rule Evaluation" << std::endl;
    
    std::vector<std::set<graph::node*, graph::node_compare>> rulesDAG = rulesGraph.getSCC();
    std::stringstream ss;
    
    for (int i = 0; i < rulesDAG.size(); i++)
    {
        std::set<graph::node*, graph::node_compare>::iterator innerCounter;
        int numPasses = 0;
        std::vector<bool> changed;
        changed.push_back(true);
        while (changed[0])
        {
            innerCounter = rulesDAG[i].begin();
            if (checkTrivial(rulesDAG[i])) //rule is trivial
            {
                evalRule(_rules[(*innerCounter)->getID()]);
//                numPasses = 1;
                changed[0] = false;
            }
            else //rule is nontrivial
            {
                for (int j = 0; j < rulesDAG[i].size(); j++)
                {
                    if (j == 0) changed[j] = evalRule(_rules[(*innerCounter)->getID()]);
                    else
                    {
                        changed.push_back(evalRule(_rules[(*innerCounter)->getID()]));
                        changed[0] = changed[0] || changed[j];
                    }
                    while (changed.size() > 1) changed.pop_back();
                    innerCounter++;
                }
            }
            numPasses++;
        }
        innerCounter = rulesDAG[i].begin();
        ss << numPasses << " passes: R" << (*innerCounter)->getID();
        innerCounter++;
        for (int j = 1; j < rulesDAG[i].size(); j++)
        {
            ss << ",R" << (*innerCounter)->getID();
        }
        ss << std::endl;
    }
    
    return ss.str();
}

bool database::checkTrivial(std::set<graph::node*, graph::node_compare>& here)
{
    if (here.size() != 1) return false;
    std::set<graph::node*, graph::node_compare>::iterator setCounter = here.begin();
    for (int i = 0; i < here.size(); i++)
    {
        if (checkChildrenForLoop((*setCounter)->getChildren(), (*setCounter)->getID())) return false;
    }
    return true;
}

bool database::checkChildrenForLoop(graph::childNode* here, int check)
{
    if (here == NULL) return false;
    if (here->parent->getID() == check) return true;
    return checkChildrenForLoop(here->nextChild, check);
}

bool database::evalRule(rule &check)
{
    std::queue<predicate> predicateList = check.getPredicates();
    
    std::vector<relation> predicateRelations;
    int listSize = (int)predicateList.size();
    
    //make a relation for each predicate
    for (int i = 0; i < listSize; i++)
    {
        std::string relName = predicateList.front().getId();
        int relIndex = findRelation(relName);
        
        std::vector<std::string> ruleParameters;
        std::vector<parameter*> forQuery;
        int loopSize = (int)predicateList.front().getParameterList().size();
//        bool preprojectFlag = false;
        for (int j = 0; j < loopSize; j++)
        {
            forQuery.push_back(predicateList.front().getParameterList().front());
            if (forQuery[j]->getType() != "STRING")
                ruleParameters.push_back(predicateList.front().getParameterList().front()->toString());
            predicateList.front().popParameter();
        }
//        std::stringstream addName; addName << relName << "_" << i;
        relation add(relName, ruleParameters);
        
        add.copyTuples(getQuery(relIndex, forQuery));
        
        predicateRelations.push_back(add);
        predicateList.pop();
    }
    
    //natural join all relations into the first, then erase all other relations except the first
    for (int i = (int)predicateRelations.size() - 1; i > 0; i--)
    {
        predicateRelations[0] = relJoin(predicateRelations[0], predicateRelations[i]);
    }
    std::queue<parameter*> rawMap = check.getHead().getParameterList();
    std::vector<std::string> headMap;
    
    int mapSize = (int)rawMap.size();
    for (int i = 0; i < mapSize; i++)
    {
        headMap.push_back(rawMap.front()->toString());
        rawMap.pop();
    }
    
    //project joined relation back to the original scheme of the rule
    
    predicateRelations[0].mapProject(headMap);
    
    relation projected(check.getHead().getId(), predicateRelations[0].getMapOriginal());
    projected.copyTuples(predicateRelations[0].project(headMap));
    
    //give tuples in projected the correct name relating to their scheme
    evalRuleHelper(headMap, projected);
    
    //Union the new tuples into the original relation
    int beforeSize = (int)_relations[findRelation(projected.getName())]->getSize();
    relUnion(_relations[findRelation(projected.getName())], projected);
    int afterSize = (int)_relations[findRelation(projected.getName())]->getSize();
    
    if (beforeSize == afterSize) return false; //no new tuples were added to the relation
    return true;
}

bool database::evalRuleHelper(std::vector<std::string> &headMap, relation &projected)
{
    for (int i = 0; i < headMap.size(); i++)
    {
        for (int j = 0; j < headMap.size(); j++)
        {
            if (projected.getMapOriginal()[j] == headMap[i])
            {
                projected.fullRename(j, _relations[findRelation(projected.getName())]->getMapOriginal()[i]);
            }
        }
    }
    return true;
}

int database::findRelation(std::string relName)
{
    for (int i = 0; i < _relations.size(); i++)
    {
        if (relName == _relations[i]->getName()) return i;
    }
    
    return -1;
}

std::vector<std::string> database::findJoin(relation &rLeft, relation &rRight)
{
    std::vector<std::string> retVal;
    for (int i = 0; i < rLeft.getMapOriginal().size(); i++)
    {
        for (int j = 0; j < rRight.getMapOriginal().size(); j++)
        {
            if (rLeft.getMapOriginal()[i] == rRight.getMapOriginal()[j])
                retVal.push_back(rLeft.getMapOriginal()[i]);
        }
    }
    return retVal;
}

std::vector<rule> database::getRules()
{
    return _rules;
}



