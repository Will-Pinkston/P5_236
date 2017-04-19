//
//  Parameter_id.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Parameter_id.h"

parameter_id::parameter_id(std::string inParam)
{
    _type = "ID";
    _data = inParam;
}

bool parameter_id::checkComplete() {return true;}

std::string parameter_id::toString()
{
    return _data;
}
