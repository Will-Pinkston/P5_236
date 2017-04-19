//
//  Relation.h
//  Relational_Database_p3_part_1
//
//  Created by William Pinkston on 3/20/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Relation_h
#define Relation_h

#include <string>
#include <vector>
#include <set>

#include "Tuple.h"

class relation
{
public:
    struct tuple_compare {
        bool operator() (const tuple& leftT, const tuple& rightT) const{
            return leftT.tuple::toString() < rightT.tuple::toString();
        }
    };

    relation(std::string setName, std::vector<std::string> setAttributeMap);
    std::string getName();
    bool addTuple(std::vector<std::string> &attributes);
    bool checkTuple(tuple* check);
    bool helperCheck(tuple* check, std::set<tuple, tuple_compare> &checkAgainst);
    
    std::set<tuple, tuple_compare> project(std::vector<std::string> &columns);
    bool projectHelper(tuple*& holder, std::set<tuple, tuple_compare>::iterator tupleCounter, std::vector<int> &mapped);
    int findInMap(std::string &find);
    
    int getSize();
    
    std::vector<tuple> select(std::string &target, std::string &criterion);
    
    bool rename(int index, std::string newName);
    
    bool startInner();
    bool innerProject(std::vector<std::string> &columns);
    bool innerSelect(int targetIndex, std::string criterion);
    bool innerSelectParallel(std::string map);
    std::set<tuple, tuple_compare> endInner();
    std::vector<std::string> getMap();
    std::vector<std::string> getFullMap();
    bool clearProjectionMap();
    bool resetBaseMap();
    
    //part 4
    std::vector<std::string> getMapOriginal();
    std::set<tuple, tuple_compare> getTuples();
    bool copyTuples(std::set<tuple, tuple_compare> newTuples);
    bool fullRename(int index, std::string newName);
    bool mapProject(std::vector<std::string> &map);
    
protected:
    std::string _name;
    int _numAttributes;
    std::set<tuple, tuple_compare> _tuples;
    std::set<tuple, tuple_compare> _tempTuples;
    std::vector<std::string> attributeMap;
    std::vector<std::string> projectionAttributeMap;
    
    //project 4 edits
    std::vector<std::string> originalMap;
};

#endif /* Relation_h */








