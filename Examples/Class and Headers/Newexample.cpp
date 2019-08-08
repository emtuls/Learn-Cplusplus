#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

#include "Nodeproto.pb.h"
#include "Node.h"

void Node::appendChild(std::shared_ptr<Node> child)
{
    child->_parent = this;
    child->_childIndex = _children.size();
    _children.push_back(child);
}

bool Node::subtreeContains(const Node &Node) const {
    // our function needs to reassign 'cur', so it needs to be a pointer
    const Node *cur = &node;
    while(cur->hasParent()) {
        if (cur == this) {
            return true;
        }
        cur = &cur->getParent();
    }
    return false;
}

bool Node::checkIfSwapOkay(const Node &node) const {
    // &node changes a reference (argument we passed in is passed by reference via &), to a pointer to an ASTNode
    // This is the opposite of getParent()
    if (this == &node) {
        cerr << "ERROR swapping: Unable to swap same node." << endl;
        return false;
    // Other Checks here...
}

bool Node::swap(Node &node) {
    if(!this->checkIfSwapOkay(node)) {
        return false;
    }
    if ((!this->hasParent()) || (!node.hasParent())) {
        cerr << "Error" << endl;
        return false
    }
    auto currNodeParent = this->getParent();
    auto otherNodeParent = node.getParent();

    int currChildIndex = this->_childIndex;
    int otherChildIndex = node._childIndex;

    auto currNode = currNodeParent._children[currChildIndex];
    auto otherNode = otherNodeParent._children[otherChildIndex];

    this->_childIndex = otherChildIndex;
    node._childIndex = currChildIndex;

    currNodeParent._children[currChildIndex] = otherNode;
    otherNodeParent._children[otherChildIndex] = currNode;

    this->_parent = &otherNodeParent;
    node._parent = &currNodeParent;
    return true;
}

void Node::toProto(const Node &node, protobuf::Node* protoMessage) {
    protoMessage->set_fieldname1(node.getFieldName1());
    if (node.hasField()) {
        protoMessage->set_fieldname2(node.getFieldName2())
    }
    for (uint64_t i = 0; i < (uint64_t) no.getCount(); i++) {
        protobuf::Node* childProtoMessage = protoMessage->add_children();
        toProto(node.getChild(i), childProtoMessage);
    }
}

std::shared_ptr<Node> Node::fromProto(const protobuf::Node &deserialProto) {
    this->_ruleNum = deserialProto.rulenum();
    if ( !deserialProto.fieldName().empty() ) {
        node->setFieldName(deserialProto.fieldName());
    }
    for (uint64_t i = 0; i < (uint64_t) deserialProto.children_size(); i++) {
        auto tempNode = std::shared_ptr<Node>();
        tempNode->fromProto(deserialProto.children(i));
        this->appendChild(tempNode);
    }
}

// This function should be:
// vector<Node &> Node::getFlatTree(const Node &node)
// but due to some C++ weirdness, we can't have a std::vector<> of references
// Instead, we have to do a std::vector<> of "reference_wrappers"
// So, the function must be:
// vector<std::reference_wrapper<Node>> Node::getFlatTree(const Node &node)
// rather than:
// vector <Node &> Node:getFlatTree(std::shared_ptr<Node> node)
// Note: Should we be using Unique and weak pointers here instead? We will need 
// to operate on the nodes inside this tree
vector<std::shared_ptr<Node>> Node::getFlatTree(std::shared_ptr<Node> node) {
    vector<vector<std::shared_ptr<Node>>> childStack;
    vector<std::shared_ptr<Node>> flatTree;
    vector<std::shared_ptr<Node>> temp{node};
    childStack.push_back(temp);
    // while (!childStack.empty()) {
        //do stuff here
    // }
    return flatTree;
}

// Don't want to make a copy of the string that we pass int, just want to work on it.
void Node::produce(string &production) {
    if (!_field.empty()) {
        production.append(_field);
    }
    for (uint64_t i = 0; i < this->getCount(); i++) {
        this->_children[i]->produce(production);
    }
}

std::shared_ptr<Node> Node::copySubTree() {
    auto tempNode = std::make_shared<Node>(this->getFieldName1());
    if ( !this->getFieldName2.empty() ) {
        tempNode->setFieldName2(this->getFieldName2());
    }
    for (uint64_t i = 0; i < this->getCount(); i++) {
        auto tempChild = this->_children[i]->copySubTree();
        tempNode->appendChild(tempChild);
    }
    return tempNode;
}