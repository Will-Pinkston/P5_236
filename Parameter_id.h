//
//  Parameter_Id.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/10/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Parameter_Id_h
#define Parameter_Id_h

#include "Parameter.h"

class parameter_id: public parameter {
public:
    parameter_id(std::string inParam);
    bool checkComplete();
    std::string toString();
protected:
    std::string _data;
};

#endif /* Parameter_Id_h */
