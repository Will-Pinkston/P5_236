//
//  Relation.cpp
//  Relational_Database_p3_part_1
//
//  Created by William Pinkston on 3/20/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Relation.h"

relation::relation(std::string setName, std::vector<std::string> setAttributeMap)
{
    attributeMap = setAttributeMap;
    originalMap = setAttributeMap;
    _name = setName;
    _numAttributes = (int)setAttributeMap.size();
}

std::string relation::getName()
{
    return _name;
}

bool relation::addTuple(std::vector<std::string> &attributes)
{
    if (attributes.size() != _numAttributes) return false;
    tuple* insert = new tuple;
    for (int i = 0; i < attributes.size(); i++)
    {
        insert->addAttribute(attributes[i]);
    }
    /*bool unique = checkTuple(insert);
    if (unique)*/ _tuples.insert(*insert);
    return true;
}

bool relation::checkTuple(tuple* check)
{
    bool retVal = true;
    int numTuples = (int)_tuples.size();
    std::set<tuple, tuple_compare>::iterator tupleCounter = _tuples.begin();
    for (int i = 0; i < numTuples; i++)
    {
        if (check->toString() ==  tupleCounter->toString()) retVal = false;
        tupleCounter++;
    }
    
    return retVal;
}



//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------



bool relation::helperCheck(tuple* check, std::set<tuple, tuple_compare> &checkAgainst)
{
    if (checkAgainst.size() == 0) return true;
    bool retVal = true;
    
    int numTuples = (int)checkAgainst.size();
    std::set<tuple, tuple_compare>::iterator tupleCounter = checkAgainst.begin();
    for (int i = 0; i < numTuples; i++)
    {
        if (check->toString() == tupleCounter->toString()) retVal = false;
        tupleCounter++;
    }
    
    return retVal;
}

std::set<tuple, relation::tuple_compare> relation::project(std::vector<std::string> &columns)
{
    std::vector<int> mapped;
    for (int i = 0; i < columns.size(); i++)
    {
        mapped.push_back(findInMap(columns[i]));
    }
    
    std::set<tuple, tuple_compare> retVal;
    for (int i = 0; i < mapped.size(); i++)
    {
        if (mapped[i] == -1) return retVal;
    }
    int numTuples = (int)_tuples.size();
    std::set<tuple, tuple_compare>::iterator tupleCounter = _tuples.begin();
    for (int i = 0; i < numTuples; i++)
    {
        tuple* holder = new tuple;
        projectHelper(holder, tupleCounter, mapped);
        /*bool unique = helperCheck(holder, retVal);
        if (unique)*/ retVal.insert(*holder);
        tupleCounter++;
    }
    
    return retVal;
}

bool relation::projectHelper(tuple*& holder, std::set<tuple, tuple_compare>::iterator tupleCounter, std::vector<int> &mapped)
{
    for (int j = 0; j < _numAttributes; j++)
    {
        for (int k = 0; k < mapped.size(); k++)
        {
            if (j == mapped[k])
            {
                holder->addAttribute(tupleCounter->getAttribute(j));
            }
        }
    }
    return true;
}

int relation::findInMap(std::string &find)
{
    for (int i = 0; i < attributeMap.size(); i++)
    {
        if (attributeMap[i] == find) return i;
    }
    return -1;
}

int relation::getSize()
{
    return (int)_tuples.size();
}

std::vector<tuple> relation::select(std::string &target, std::string &criterion)
{
    std::vector<tuple> retVal;
    
    int map = findInMap(target);
    if (map == -1) return retVal;
    
    int numTuples = (int)_tuples.size();
    std::set<tuple, tuple_compare>::iterator tupleCounter = _tuples.begin();
    for (int i = 0; i < numTuples; i++)
    {
        if (tupleCounter->getAttribute(map) == criterion)
        {
            retVal.push_back(*tupleCounter);
        }
        tupleCounter++;
    }
    
    return retVal;
}

bool relation::rename(int index, std::string newName)
{
    attributeMap[index] = newName;
    return true;
}

bool relation::fullRename(int index, std::string newName)
{
    originalMap[index] = newName;
    return true;
}

bool relation::startInner()
{
    _tempTuples = _tuples;
    return true;
}

bool relation::innerProject(std::vector<std::string> &columns)
{
    std::vector<int> mapped;
    for (int i = 0; i < columns.size(); i++)
    {
        mapped.push_back(findInMap(columns[i]));
    }
    projectionAttributeMap = columns;
    
    std::set<tuple, tuple_compare> retVal;
    
    int numTuples = (int)_tempTuples.size();
    std::set<tuple, tuple_compare>::iterator tupleCounter = _tempTuples.begin();
    for (int i = 0; i < numTuples; i++)
    {
        tuple* holder = new tuple;
        for (int j = 0; j < _numAttributes; j++)
        {
            for (int k = 0; k < mapped.size(); k++)
            {
                if (j == mapped[k])
                {
                    holder->addAttribute(tupleCounter->getAttribute(j));
                }
            }
        }
        /*bool unique = helperCheck(holder, retVal);
        if (unique)*/ retVal.insert(*holder);
        tupleCounter++;
    }
    
    _tempTuples = retVal;
    return true;
}

bool relation::innerSelect(int targetIndex, std::string criterion)
{
    std::set<tuple, tuple_compare> retVal;
    
    std::set<tuple, tuple_compare>::iterator tupleCounter = _tempTuples.begin();
    for (int i = 0; i < _tempTuples.size(); i++)
    {
        if (tupleCounter->getAttribute(targetIndex) == criterion)
        {
            retVal.insert(*tupleCounter);
        }
        tupleCounter++;
    }
    
    _tempTuples = retVal;
    return true;
}

bool relation::innerSelectParallel(std::string map)
{
    std::set<tuple, tuple_compare> retVal;
    std::set<tuple, tuple_compare>::iterator tupleCounter = _tempTuples.begin();
    
    std::vector<int> parallels;
    for (int i = 0; i < attributeMap.size(); i++)
    {
        if (map == attributeMap[i])
        {
            parallels.push_back(i);
        }
    }
    
    for (int i = 0; i < _tempTuples.size(); i++)
    {
        std::string currentCompare = tupleCounter->getAttribute(parallels[0]);
        bool sameVal = true;
        int j = 1;
        while (j < parallels.size() && sameVal)
        {
            if (currentCompare != tupleCounter->getAttribute(parallels[j]))
            {
                sameVal = false;
            }
            j++;
        }
        if (sameVal)
        {
            retVal.insert(*tupleCounter);
        }
        
        tupleCounter++;
    }

    _tempTuples = retVal;
    return true;
}

std::set<tuple, relation::tuple_compare> relation::endInner()
{
    return _tempTuples;
}

std::vector<std::string> relation::getMap()
{
    return projectionAttributeMap;
}

std::vector<std::string> relation::getFullMap()
{
    return attributeMap;
}

bool relation::clearProjectionMap()
{
    while (projectionAttributeMap.size() != 0) projectionAttributeMap.pop_back();
    return true;
}

bool relation::resetBaseMap()
{
    for (int i = 0; i < attributeMap.size(); i++)
    {
        attributeMap[i] = "$";
    }
    return true;
}

//part 4
std::vector<std::string> relation::getMapOriginal()
{
    return originalMap;
}

std::set<tuple, relation::tuple_compare> relation::getTuples()
{
    return _tuples;
}
bool relation::copyTuples(std::set<tuple, tuple_compare> newTuples)
{
    std::set<tuple, tuple_compare>::iterator tupleCounter = newTuples.begin();
    for (int i = 0; i < newTuples.size(); i++)
    {
        std::vector<std::string> holdAttributes;
        for (int j = 0; j < tupleCounter->getNumAttributes(); j++)
        {
            holdAttributes.push_back(tupleCounter->getAttribute(j));
        }
        addTuple(holdAttributes);
        tupleCounter++;
    }
    return true;
}

bool relation::mapProject(std::vector<std::string> &map)
{
    std::vector<bool> mapProjection(originalMap.size());
    for (int i = 0; i < mapProjection.size(); i++)
    {
        mapProjection[i] = false;
    }
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < originalMap.size(); j++)
        {
            if (map[i] == originalMap[j])
            {
                mapProjection[j] = true;
            }
        }
    }
    
    for (int i = (int)originalMap.size() - 1; i  >= 0; i--)
    {
        if (!mapProjection[i])
        {
            originalMap.erase(originalMap.begin() + i);
        }
    }
    return true;
}







