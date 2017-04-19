//
//  Graph.h
//  Rule_optimizer_p5_part1
//
//  Created by William Pinkston on 4/15/17.
//  Copyright © 2017 Xunil_programming. All rights reserved.
//

#ifndef Graph_h
#define Graph_h

#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include <stack>
#include <set>
#include <iostream>

//#include "Database.h"
#include "Rule.h"

class graph {
public:
    //
    class childNode;
    class node {
    public:
        node(std::string inName, int ID)
        {
            name = inName;
            next = NULL;
            children = NULL;
            traversalIndex = -1;
            traversalVisited = false;
            componentVisited = false;
            ruleID = ID;
        }
//        ~node()
//        {
//            while (next != NULL)
//            {
//                node* temp = next->next;
//                delete next;
//                next = temp;
//            }
//            while (children != NULL)
//            {
//                childNode* temp = children->nextChild;
//                delete children;
//                children = temp;
//            }
//        }
        std::string getName() {return name;}
        node*& getNext() {return next;}
        childNode* getChildren() {return children;}
        int getID() const {return ruleID;}
        int getIndex() {return traversalIndex;}
        std::string name;
        node* next;
        childNode* children;
        int ruleID;
        int traversalIndex;
        bool traversalVisited;
        bool componentVisited;
    };
    class childNode {
    public:
        childNode(node* passIn)
        {
            parent = passIn;
            nextChild = NULL;
        }
//        ~childNode()
//        {
//            while (nextChild!= NULL)
//            {
//                childNode* temp = nextChild->nextChild;
//                delete nextChild;
//                nextChild = temp;
//            }
//        }
        childNode*  nextChild;
        node* parent;
    };
    //
    struct node_compare {
        bool operator() (const node* leftT, const node* rightT) const{
            return leftT->node::getID() < rightT->node::getID();
        }
    };
    //
    graph(std::vector<rule> _rules);
    node* graphRules(std::vector<rule> &_rules, int current);
    
    bool evalDependencies(std::vector<rule> &_rules, node* here, int current);
    bool checkUnique(childNode* here, int &checkID);
    node* getNodeByID(int ID, node* here);
    bool fillChildren(node* add, childNode*& here);
    
    bool printGraph();
    std::stringstream printHelper(node* here);
    std::stringstream printChildrenHelper(childNode* here, bool first);

    bool setIndexFromNode(node* startNode);
    bool resetGraphIndices(node* here);
    bool setIndexFromNodeOuter(node* here);
    bool setIndexFromNodeInner(childNode* here);

    std::vector<int> nodesReachableFrom(node* here);
    bool resetGraphFlags(node* here);
    bool resetSCCFlags(node* here);
    std::vector<int> innerTraverse(childNode* here);

    bool reverseGraph();
    node* getGraphNodes(node* here);
    bool crossCopyChildrenOuter(node* to, node* from);
    bool crossCopyChildrenInner(node* to, childNode* from, node* outerFrom);
    childNode* getLastChild(childNode* here);
    //
    //
    std::vector<std::set<node*, node_compare>> getSCC();
    std::stack<int> searchAllOuter(node* here);
    std::stack<int> searchAllInner(childNode* here);
    std::set<node*, node_compare> getNodesAtIDs(std::vector<int> filter);
    
    node*& getGraphHead();
    node* getBackGraph();
private:
    node* graphHead;
    node* backGraph;
    std::vector<std::string> ruleNames;
    int indexHolder;
};


#endif /* Graph_h */








