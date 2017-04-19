//
//  Parser.cpp
//  Datalog_Parser_p2
//
//  Created by William Pinkston on 2/21/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Parser.h"


parser::parser(std::stack<std::string>& tokens)
{
    _Tokens = tokens;
}


void parser::getCurrentToken()
{
    std::stringstream tokenHolder_ss;
    tokenHolder_ss << _Tokens.top();
    tokenHolder_ss.get();
    
    std::getline(tokenHolder_ss, _Current_Token, ',');
    
    if (_Current_Token == "COMMENT")
    {
        _Tokens.pop();
        getCurrentToken();
    }
    if (_Current_Token == "UNDEFINED")
    {
        throw _Tokens.top();
    }
}

void parser::addToDomain(std::string token)
{
    std::stringstream holder;
    holder << token;
    std::string addDomain;
    std::getline(holder, addDomain, '"');
    std::getline(holder, addDomain, '"');
    _Domain.insert(addDomain);
}

void parser::printDomain()
{
    std::cout << "Domain(" << _Domain.size() << "):" << std::endl;
    std::set<std::string>::iterator step;
    for (step = _Domain.begin(); step != _Domain.end(); ++step)
    {
        std::cout << "\t" << *step << std::endl;
    }
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------

bool parser::run()
{
//    bool parse_program;
    
    try
    {
        _datalogProgram();
    }
    catch (std::string fault)
    {
//        std::cout << "Failure!\n\t" << fault << std::endl;
        return false;
    }
    
//    std::cout << "Success!" << std::endl;
    
//    std::cout << _Program.toString();
//    printDomain();
    return true;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//methods represent each rule in the grammar

bool parser::schemeHelper()
{
    getCurrentToken();
    if (_Current_Token != "SCHEMES")
    {
        throw _Tokens.top();
        return false;
    }
    _Program.setScheme();
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "COLON")
    {
        throw _Tokens.top();
        return false;
    }
    
    return (_scheme() && _schemeList());
}

bool parser::factHelper()
{
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "COLON")
    {
        throw _Tokens.top();
        return false;
    }
    
    return _factList();
}

bool parser::ruleHelper()
{
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "COLON")
    {
        throw _Tokens.top();
        return false;
    }
    
    return _ruleList();
}

bool parser::queryHelper()
{
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "COLON")
    {
        throw _Tokens.top();
        return false;
    }
    
    return (_query() && _queryList());
}

bool parser::_datalogProgram()
{
    bool schemes = schemeHelper();
    
    bool facts = factHelper();

    bool rules = ruleHelper();

    bool queries = queryHelper();
    
    return (schemes && facts && rules && queries);
}

bool parser::_scheme()
{
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "ID")
    {
        throw _Tokens.top();
        return false;
    }
    _Program.addToken(_Tokens.top());
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "LEFT_PAREN")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "ID")
    {
        throw _Tokens.top();
        return false;
    }
    _Program.addToken(_Tokens.top());
    
    bool testIdList = _idList();
    
    //_Tokens.pop();
    //getCurrentToken();
    if (_Current_Token != "RIGHT_PAREN")
    {
        throw _Tokens.top();
        return false;
    }
    
    return testIdList;
}

bool parser::_schemeList()
{
    while (true)
    {
        _Tokens.pop();
        getCurrentToken();
        if (_Current_Token == "ID")
        {
            _Tokens.push("_fill");
            _scheme();
        }
        else if (_Current_Token == "FACTS")
        {
            _Program.setFact();
            return true;
        }
        else
        {
            throw _Tokens.top();
            return false;
        }
    }
}

bool parser::_idList()
{
    while (true)
    {
        _Tokens.pop();
        getCurrentToken();
        if (_Current_Token == "COMMA")
        {
            _Tokens.pop();
            getCurrentToken();
            if (_Current_Token == "ID")
            {
                _Program.addToken(_Tokens.top());
            }
            else
            {
                throw _Tokens.top();
                return false;
            }
        }
        else if (_Current_Token == "RIGHT_PAREN")
        {
            _Program.endPredicate();
            return true;
        }
        else
        {
            throw _Tokens.top();
            return false;
        }
    }
}

bool parser::_fact()
{
    //ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "LEFT_PAREN")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "STRING")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Program.addToken(_Tokens.top());
    addToDomain(_Tokens.top());
    
    bool checkStringList = _stringList();
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "PERIOD")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Program.endPredicate();
    return checkStringList;
}

bool parser::_factList()
{
    _Tokens.pop();
    getCurrentToken();
    while (_Current_Token == "ID")
    {
        _Program.addToken(_Tokens.top());
        _fact();
        _Tokens.pop();
        getCurrentToken();
    }
    
    if (_Current_Token != "RULES")
    {
        throw _Tokens.top();
        return false;
    }
    _Program.setRule();
    return true;
}

bool parser::_rule()
{
    //headPredicate COLON_DASH predicate predicateList PERIOD
    bool checkHeadPredicate = _headPredicate();
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "COLON_DASH")
    {
        throw _Tokens.top();
        return false;
    }
    
    return (checkHeadPredicate && _predicate() && _predicateList());
}

bool parser::_ruleList()
{
    //rule ruleList | lambda
    _Tokens.pop();
    getCurrentToken();
    while (_Current_Token == "ID")
    {
        _Program.addToken(_Tokens.top());
        _rule();
        _Tokens.pop();
        getCurrentToken();
    }
    
    if (_Current_Token != "QUERIES")
    {
        throw _Tokens.top();
        return false;
    }
    _Program.setQuery();
    return true;
}

bool parser::_headPredicate()
{
    //ID LEFT_PAREN ID idList RIGHT_PAREN
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "LEFT_PAREN")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "ID")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Program.addToken(_Tokens.top());
    bool checkIdList = _idList();
    
    return checkIdList;
}

bool parser::_predicate()
{
    //ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "ID")
    {
        throw _Tokens.top();
        return false;
    }
    
    _Program.addToken(_Tokens.top());
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "LEFT_PAREN")
    {
        throw _Tokens.top();
        return false;
    }
    
    return (_parameter() && _parameterList());
}

bool parser::_predicateList()
{
    //COMMA predicate predicateList | lambda
    while (true)
    {
        _Tokens.pop();
        getCurrentToken();
        if (_Current_Token == "COMMA")
        {
            _predicate();
        }
        else if (_Current_Token == "PERIOD")
        {
            _Program.endRule();
            return true;
        }
        else
        {
            throw _Tokens.top();
            return false;
        }
    }
}

bool parser::_parameter() //review this...
{
    //STRING | ID | expression
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token == "STRING")
    {
        _Program.addToken(_Tokens.top());
        return true;
    }
    if (_Current_Token == "ID")
    {
        _Program.addToken(_Tokens.top());
        return true;
    }
    if (_Current_Token == "LEFT_PAREN")
    {
        _Program.addToken(_Tokens.top());
        return _expression();
    }
    throw _Tokens.top();
    return false;
}

bool parser::_parameterList()
{
    //COMMA parameter parameterList | lambda
    while (true)
    {
        _Tokens.pop();
        getCurrentToken();
        if (_Current_Token == "COMMA")
        {
            _parameter();
        }
        else if (_Current_Token == "RIGHT_PAREN")
        {
            _Program.endPredicate();
            return true;
        }
        else
        {
            throw _Tokens.top();
            return false;
        }
    }
}

bool parser::_expression()
{
    bool checkParam1 = _parameter();
    bool checkOperator = _operator();
    bool checkParam2 = _parameter();
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "RIGHT_PAREN")
    {
        throw _Tokens.top();
        return false;
    }
    _Program.addToken(_Tokens.top());
    return (checkParam1 && checkOperator && checkParam2);
}

bool parser::_operator()
{
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token == "MULTIPLY")
    {
        _Program.addToken(_Tokens.top());
        return true;
    }
    if (_Current_Token == "ADD")
    {
        _Program.addToken(_Tokens.top());
        return true;
    }
    else
    {
        throw _Tokens.top();
        return false;
    }
}

bool parser::_query()
{
    //predicate Q_MARK
    bool checkPredicate = _predicate();
    
    _Tokens.pop();
    getCurrentToken();
    if (_Current_Token != "Q_MARK")
    {
        throw _Tokens.top();
        return false;
    }
    return checkPredicate;
}

bool parser::_queryList()
{
    //query queryList | lambda
    while (true)
    {
        _Tokens.pop();
        getCurrentToken();
        if (_Current_Token == "ID")
        {
            _Tokens.push("_Fill");
            _query();
        }
        else if (_Current_Token == "EOF")
        {
            return true;
        }
        else
        {
            throw _Tokens.top();
            return false;
        }
    }
}

bool parser::_stringList()
{
    while (true)
    {
        _Tokens.pop();
        getCurrentToken();
        if (_Current_Token == "COMMA")
        {
            _Tokens.pop();
            getCurrentToken();
            if (_Current_Token == "STRING")
            {
                _Program.addToken(_Tokens.top());
                addToDomain(_Tokens.top());
            }
            else throw _Tokens.top();
        }
        else if (_Current_Token == "RIGHT_PAREN")
        {
            return true;
        }
        else
        {
            throw _Tokens.top();
            return false;
        }
    }
}


datalogProgram* parser::getProgram()
{
    return &_Program;
}



