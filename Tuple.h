//
//  Tuple.h
//  Relational_Database_p3_part_1
//
//  Created by William Pinkston on 3/20/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Tuple_h
#define Tuple_h

#include <vector>
#include <string>

class tuple
{
public:
    tuple();
    bool addAttribute(std::string inAttribute);
    std::string toString() const;
    std::string getAttribute(int at) const;
    int getNumAttributes() const;
    std::vector<std::string> getAllAttributes() const;
protected:
    std::vector<std::string> _attributes;
};

#endif /* Tuple_h */
