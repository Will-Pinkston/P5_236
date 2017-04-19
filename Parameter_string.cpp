//
//  Parameter_String.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Parameter_string.h"
parameter_string::parameter_string(std::string inParam)
{
    _type = "STRING";
    _data = inParam;
}

bool parameter_string::checkComplete() {return true;}

std::string parameter_string::toString()
{
    return _data;
}
