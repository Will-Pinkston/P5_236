//
//  Parameter.h
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 3/9/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Parameter_h
#define Parameter_h

#include <string>

class parameter {
public:
    parameter() {};
    std::string getType();
    
    virtual parameter* getLeft();
    virtual parameter* getRight();
    virtual bool addExpression();
    virtual bool addOperator(char operatorToken);
    virtual bool addID(std::string idToken);
    virtual bool addString(std::string stringToken);
    virtual bool checkComplete();
    
    virtual std::string toString();
protected:
    std::string _type;
};

//parameter => STRING | ID | expression

//this needs to hold the piece of info
//and be able to tell you what type of info it is
#endif /* Parameter_h */
