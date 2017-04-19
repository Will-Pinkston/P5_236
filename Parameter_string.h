//
//  Parameter_String.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Parameter_String_h
#define Parameter_String_h

#include "Parameter.h"

class parameter_string: public parameter {
public:
    parameter_string(std::string inParam);
    bool checkComplete();
    std::string toString();
protected:
    std::string _data;
};

#endif /* Parameter_String_h */
