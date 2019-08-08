





Node::Node()
{}

Node::Node(int fieldName1)
        : _fieldName1(fieldName1)
{}

Node::~Node() {
    for (auto ptr: _fieldName2) {
        delete ptr;
    }
    _fieldName2.clear();
}

void Node:setData(string data) {
    _data = data;
}

string Node::getData() {
    return _data;
}

bool Node::hasData() {
    return !_data.empty();
}

void Node::setFieldName(type fieldName) {
    _fieldName = fieldName;
}

void Node::setParent(Node *parent) {
    _parent = parent;
}

Node* Node::getParent() {
    return _parent;
}

const vector<Node*> &Node::getChildren() {
    return _children;
}

Node* Node::getChild(int index) {
    return _children[index];
}

void Node::addChild(ASTNode* child) {
    child->setParent(this);
    child->setChildIndex(_children.size());
    _children.push_back(child);
}

bool Node::subtreeContains(ASTNode* node) {
    while(node->getParent()) {
        if (node == this) {
            return true;
        }
        node = node->getParent;
    }
    return false;
}

bool Node::checkIfSwapOkay(Node* node) {
    if (this == node) {          // use log here?
        cerr << "Error" << endl; // should turn this into a better error handler function
        return false;
    }
    //other checks here...
    return true;
}

bool Node::swap(Node* node) {
    if (!this->checkIfSwapOkay(node)) {
        return false;
    }
    Node* currParent = this->getParent();
    Node* otherParent = node->getParent();
    if ((!currParent) || (!otherParent)) {
        cerr << "Error" << endl;    // should turn this into a better error handler function; use logs?
        return false;
    }
    int currChildIndex = this->getChildIndex();
    int otherChildIndex = node->getChildIndex();

    this->setChildIndex(otherChildIndex);
    node->setChildIndex(currChildIndex);

    currParent->_children[currChildIndex] = node;
    otherParent->_children[otherChildIndex] = this;

    this->setParent(otherParent);
    node->setParent(currParent);
    return true;
}

void Node::toProto(protobuf::Node* protoMessage) {
    protoMessage->set_fieldname(this->getFieldName());
    if (this->hasFieldName()) {
        protoMessage->set_fieldname(this->getFieldName());
    }
    for (uint64_t i = 0; i < (uint64_t) this->getChildCount(); i++) {
        protobuf::Node* childProtoMessage = protoMessage->add_children();
        this->getChild(i)->astToProto(childProtoMessage);
    }
}

void Node::fromProto(const protobuf::Node &deserializedProto) {
    this->setFieldName(deserializedProto.fieldName());
    if ( !deserializedProto.fieldName().empty() ) {
        this->setFieldName(deserializedProto.fieldName());
    }
    for (uint64_t i = 0; i < (uint64_t) deserializedProto.children_size(); i++) {
        Node* tempNode = new Node();
        tempNode->fromProto(deserializedProto.children(i));
        this->addChild(tempNode);
    }
}

vector<Node*> Node::getFlatTree() {
    vector<vector<Node*>> childStack;
    vector<Node*> flatTree;
    vector<Node*> temp{this};
    childStack.push_back(temp);
    // while (not empty...)
    //      do stuff
    return flatTree;
}

void Node::produce(string &production) {
    if (!_data.empty()) {
        production.append(_data);
    }
    for (uint64_t i = 0; i < this->getChildCount(); i++) {
        this->getChild(i)->produce(production);
    }
}

Node* Node::copyNode() {
    Node* tempNode = new Node(this->getFieldName());
    if ( !this->getData().empty() ) {
        tempNode->setData(this->getData());
    }
    return tempNode;
}