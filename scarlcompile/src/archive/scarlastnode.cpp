
#include <iterator>

#include "scarlastnode.h"

using namespace std;

SCARL_AST_Node::SCARL_AST_Node(int typeFlag) {
    this->typeFlag = typeFlag;
    this->intValue = -1;
    this->strValue = "";
    children = list<SCARL_AST_Node*>(); //default list
}

SCARL_AST_Node::SCARL_AST_Node(int typeFlag, int value) {
    this->typeFlag = typeFlag;
    this->intValue = value;
    this->strValue = "";
    children = list<SCARL_AST_Node*>(); //default list
}

SCARL_AST_Node::SCARL_AST_Node(int typeFlag, string strValue) {
    this->typeFlag = typeFlag;
    this->intValue = -1;
    this->strValue = strValue;
    children = list<SCARL_AST_Node*>(); //default list
}

SCARL_AST_Node::~SCARL_AST_Node() {
    // delete all children before
    // removing self

    for (list<SCARL_AST_Node*>::iterator itr = this->children.begin();
            itr != this->children.end(); itr++) {
        SCARL_AST_Node *nodeObj = *itr;
        delete nodeObj;
    }
}

void SCARL_AST_Node::addChild(SCARL_AST_Node *node) {
    this->children.push_back(node);
}

void SCARL_AST_Node::addChildFront(SCARL_AST_Node *node) {
    this->children.push_front(node);
}

list<SCARL_AST_Node*> &SCARL_AST_Node::getChildren() {
    return this->children;
}

bool SCARL_AST_Node::hasChildren() {
    return this->children.size() > 0;
}

int SCARL_AST_Node::getType() {
    return this->typeFlag;
}

