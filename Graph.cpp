//
//  Graph.cpp
//  Rule_optimizer_p5_part1
//
//  Created by William Pinkston on 4/15/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#include "Graph.h"

graph::graph(std::vector<rule> _rules)
{
    graphHead = NULL;
    graphHead = graphRules(_rules, 0);
    evalDependencies(_rules, graphHead, 0);
}

graph::node* graph::graphRules(std::vector<rule> &_rules, int current)
{
    node *retVal = new node(_rules[current].getHead().getId(), current);
    ruleNames.push_back(retVal->getName());
    if (current < _rules.size() - 1)
    {
        retVal->next = graphRules(_rules, ++current);
    }
    return retVal;
}

bool graph::evalDependencies(std::vector<rule> &_rules, node* here, int current)
{
    if (here != NULL)
    {
        std::vector<predicate> rulePredicates;
        std::queue<predicate> rulePredQueue = _rules[current].getPredicates();
        int numPredicates = (int)rulePredQueue.size();
        for (int i = 0; i < numPredicates; i++)
        {
            rulePredicates.push_back(rulePredQueue.front());
            rulePredQueue.pop();
        }
        
        for (int j = 0; j < ruleNames.size(); j++)
        {
            for (int k = 0; k < rulePredicates.size(); k++)
            {
                if (ruleNames[j] == rulePredicates[k].getId())
                {
//                    if (checkUnique(here->children, j)) fillChildren(getNodeByID(j, graphHead), here->children);
                    fillChildren(getNodeByID(j, graphHead), here->children);
                    break;
                }
            }
        }
        evalDependencies(_rules, here->getNext(), ++current);
    }
    return true;
}

bool graph::checkUnique(childNode* here, int &checkID)
{
    if (here == NULL) return true;
    if (here->parent->getID() == checkID) return false;
    return checkUnique(here->nextChild, checkID);
}

graph::node* graph::getNodeByID(int ID, node* here)
{
    if (here->getID() == ID) return here;
    else return getNodeByID(ID, here->getNext());
}

bool graph::fillChildren(node* add, childNode*& here)
{
    if (here == NULL)
    {
        here = new childNode(add);
    }
    else fillChildren(add, here->nextChild);
    return true;
}


//./././././././....
//./././././././....


bool graph::printGraph()
{
    std::cout << printHelper(graphHead).str() << std::endl;
    
    return true;
}

std::stringstream graph::printHelper(node* here)
{
    std::stringstream ss;
    if (here != NULL)
    {
        ss << "R" << here->getID() << ":" << printChildrenHelper(here->getChildren(), true).str() << std::endl << printHelper(here->getNext()).str();
    }
    return ss;
}

std::stringstream graph::printChildrenHelper(childNode* here, bool first)
{
    std::stringstream ss;
    if (here != NULL)
    {
        if (first) ss << "R" << here->parent->getID() << printChildrenHelper(here->nextChild, false).str();
        else ss << ",R" << here->parent->getID() << printChildrenHelper(here->nextChild, false).str();
    }
    return ss;
}


//./././././././....
//./././././././....


bool graph::setIndexFromNode(node* startNode)
{
    resetGraphIndices(graphHead);
    indexHolder = 0;
    return setIndexFromNodeOuter(startNode);
}

bool graph::resetGraphIndices(node* here)
{//bugcheck??
    if (here == NULL) return true;
    here->traversalIndex = -1;
    here->traversalVisited = false;
    return resetGraphIndices(here->getNext());
}

bool graph::setIndexFromNodeOuter(node* here)
{
    if (here == NULL) return true;
    if (here->traversalVisited == true) return setIndexFromNodeOuter(here->next);
    here->traversalVisited = true;
    setIndexFromNodeInner(here->children);
    here->traversalIndex = indexHolder;
    indexHolder++;
    return setIndexFromNodeOuter(here->next);
}

bool graph::setIndexFromNodeInner(childNode* here)
{
    if (here == NULL) return true;
    if (here->parent->traversalVisited == true) return setIndexFromNodeInner(here->nextChild);
    here->parent->traversalVisited = true;
    setIndexFromNodeInner(here->parent->children);
    here->parent->traversalIndex = indexHolder;
    indexHolder++;
    return setIndexFromNodeInner(here->nextChild);
}


//./././././././....
//./././././././....


std::vector<int> graph::nodesReachableFrom(node* here)
{
    resetGraphFlags(graphHead);
    std::vector<int> retVal;
    if (here->children == NULL)
    {
        if (!here->componentVisited)
        {
            retVal.push_back(here->getID());
            here->componentVisited = true;
        }
        return retVal;
    }
    here->traversalVisited = true;
    here->componentVisited = true;
    retVal = innerTraverse(here->children);
    retVal.push_back(here->getID());
    return retVal;
}

bool graph::resetGraphFlags(node* here)
{
    if (here == NULL) return true;
    here->traversalVisited = false;
    return resetGraphFlags(here->getNext());
}

bool graph::resetSCCFlags(node* here)
{
    if (here == NULL) return true;
    here->componentVisited = false;
    return resetSCCFlags(here->getNext());
}

std::vector<int> graph::innerTraverse(childNode* here)
{
    std::vector<int> retVal;
    if (here == NULL) return retVal;
    if (here->parent->traversalVisited || here->parent->componentVisited) return innerTraverse(here->nextChild);
    here->parent->traversalVisited = true;
    here->parent->componentVisited = true;
    std::vector<int> hold = innerTraverse(here->parent->children);
    for (int i = 0; i < hold.size(); i++)
    {
        retVal.push_back(hold[i]);
    }
    retVal.push_back(here->parent->getID());
    hold = innerTraverse(here->nextChild);
    for (int i = 0; i < hold.size(); i++)
    {
        retVal.push_back(hold[i]);
    }
    return retVal;
}

//./././././././....
//./././././././....


bool graph::reverseGraph()
{
    node* newHead = getGraphNodes(graphHead);

    crossCopyChildrenOuter(newHead, graphHead);
    backGraph = newHead;
    return true;
}

graph::node* graph::getGraphNodes(node* here)
{
    if (here == NULL) return here;
    node* retVal = new node(here->getName(), here->getID());
    retVal->next = getGraphNodes(here->next);
    return retVal;
}

bool graph::crossCopyChildrenOuter(node* to, node* from)
{
    if (from == NULL) return true;
    crossCopyChildrenInner(to, from->children, from);
    return crossCopyChildrenOuter(to, from->next);
}

bool graph::crossCopyChildrenInner(node* to, childNode* from, node* outerFrom)
{
    if (from == NULL) return true;
    node* here = getNodeByID(from->parent->getID(), to);
    if (here->children == NULL)
    {
        here->children = new childNode(getNodeByID(outerFrom->getID(), to));
        return crossCopyChildrenInner(to, from->nextChild, outerFrom);
    }
    childNode* open = getLastChild(here->children);
    open->nextChild = new childNode(getNodeByID(outerFrom->getID(), to));
    return crossCopyChildrenInner(to, from->nextChild, outerFrom);
}

graph::childNode* graph::getLastChild(childNode* here)
{
    if (here->nextChild == NULL) return here;
    return getLastChild(here->nextChild);
}


//./././././././....
//./././././././....


std::vector<std::set<graph::node*, graph::node_compare>> graph::getSCC()
{
    std::vector<std::set<node*, node_compare>> retVal;
    reverseGraph();
    resetGraphFlags(backGraph);
    std::stack<int> traversalIndex = searchAllOuter(backGraph);
    
    resetSCCFlags(graphHead);
    while(traversalIndex.size() != 0)
    {
        if (!getNodeByID(traversalIndex.top(), graphHead)->componentVisited)
        {
            retVal.push_back(getNodesAtIDs(nodesReachableFrom(getNodeByID(traversalIndex.top(),graphHead))));
        }
        traversalIndex.pop();
    }
    
    return retVal;
}

std::set<graph::node*, graph::node_compare> graph::getNodesAtIDs(std::vector<int> filter)
{
    std::set<node*, node_compare> retVal;
    for (int i = 0; i < filter.size(); i++)
    {
        retVal.insert(getNodeByID(filter[i], graphHead));
    }
    return retVal;
}

std::stack<int> graph::searchAllOuter(node* here)
{
    std::stack<int> retVal;
    if (here == NULL) return retVal;
    if (here->traversalVisited == true) return searchAllOuter(here->next);
    here->traversalVisited = true;
    retVal = searchAllInner(here->children);
    retVal.push(here->getID());
    
    std::stack<int> hold = searchAllOuter(here->next);
    std::vector<int> hold2;
    int holdSize = (int)hold.size();
    for (int i = 0; i < holdSize; i++)
    {
        hold2.push_back(hold.top());
        hold.pop();
    }
    for (int i = 0; i < holdSize; i++)
    {
        retVal.push(hold2.back());
        hold2.pop_back();
    }
    
    return retVal;
}
std::stack<int> graph::searchAllInner(childNode* here)
{
    std::stack<int> retVal;
    if (here == NULL) return retVal;
    if (here->parent->traversalVisited == true) return searchAllInner(here->nextChild);
    here->parent->traversalVisited = true;
    retVal = searchAllInner(here->parent->children);
    retVal.push(here->parent->getID());
    
    std::stack<int> hold = searchAllInner(here->nextChild);
    std::vector<int> hold2;
    int holdSize = (int)hold.size();
    for (int i = 0; i < holdSize; i++)
    {
        hold2.push_back(hold.top());
        hold.pop();
    }
    for (int i = 0; i < holdSize; i++)
    {
        retVal.push(hold2.back());
        hold2.pop_back();
    }
    
    return retVal;
}


//./././././././....
//./././././././....


graph::node*& graph::getGraphHead()
{
    return graphHead;
}

graph::node* graph::getBackGraph()
{
    return backGraph;
}


//./././././././....
//./././././././....





