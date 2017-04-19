//
//  Tuple.cpp
//  Relational_Database_p3_part_1
//
//  Created by William Pinkston on 3/20/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Tuple.h"

tuple::tuple()
{
    //
}

bool tuple::addAttribute(std::string addAttribute)
{
    _attributes.push_back(addAttribute);
    return true;
}

std::string tuple::toString()
const {
    std::string retVal;
    for (int i = 0; i < _attributes.size(); i++)
    {
        retVal = retVal + _attributes[i];
    }
    return retVal;
}

std::string tuple::getAttribute(int at)
const {
    return _attributes[at];
}

int tuple::getNumAttributes()
const {
    return (int)_attributes.size();
}

std::vector<std::string> tuple::getAllAttributes()
const {
    return _attributes;
}






