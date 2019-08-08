// Never use namespace in a headerfile

class Node
{
public:
    size_t _fieldname1;
    int _fieldname2;
    std::string _data;
    Node* _parent = nullptr; // in C++, must be pointer if using same type as class
    std::vector<Node*> _children;


    Node();
    Node(int fieldname1);
    ~Node();

    void setData(std::string data);
    std::string getData();
    bool hasData();

    void setFieldName(type fieldname);
    type getFieldName();

private:
    void setParent(Node *parent);
public:
    Node* getParent();
    bool hasParent();

    const std::vector<Node*> &getChildren();        // What I probably did before was std::vector<Node*> getChildren();
    Node* getChild(int index);
    void add Child(Node* child);

    bool subtreeContains(Node* node);
    bool checkIfSwapOkay(Node* node);
    bool swap(Node* node);

    toProto(protobuf::Node* protoMessage);
    fromProto(const protobuf::Node &protoMessage);

    std::vector<Node*> getFlatTree();
    void produce(std::string &production);
    Node* copyNode();
    Node* copySubTree();
}