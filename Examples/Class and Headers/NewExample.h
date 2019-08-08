#ifndef Node_H
#define Node_H

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "NodeProto.pb.h"

class Node
{
public:
    Node(int fieldName1) : _fieldName1(fieldName1) { }

    // if return type is 'small' or 'basic', we can return by value (i.e. not by reference)
    // In addition, since we are returning 'by value' (which means a copy is being made)
    // we wouldn't make this a const
    // Good rule of thumb: all 'get' functions will likely be const ( after the () )
    int getFieldName1() const { return _fieldName1; }


    // if we return a reference, we can modify the underlying data
    // if we don't use a reference, we copy (could be potentially LARGE amount of data)
    // but our changes don't effect the underlying actual data.
    // std::string getData() { // this returns a copy of _data
    //    return _data;
    // }
    // Returns a 'read-only view' of some data inside the class
    const std::string &getData() const { return _data; }

    // setData coudl be this and performance wise, there is no difference
    // The difference is that it's a bit 'nicer' to call the setData function
    // Users of this would have to do:
    //   std::string myData = "abc";
    //   myNode.setData(&myData);
    // void setData(const std::string *data) { _data = *data; }

    // setData should be this to be "more C++ like"
    // Users of this would have to do:
    //   std::string myData = "abc";
    //   myNode.setData(myData); // This does not actually copy the parameter, since param is
    // actually a reference (the constedness of the reference does not matter)
    void setData(const std::string &data) { _data = data; }

    bool hasData() const { return !_data.empty(); }

    // This is one possibility for getParent. We return a const pointer
    // Users would write:
    //   auto x = myNode.getParent();
    //   x->getData();
    // const Node *getParent() const { return _parent; }

    // This would be the better possibility for getParent. We return a const reference.
    // Users would write:
    //   const auto &x = myNode.getParent();
    //   x.getData();
    // We return *_parent because _parent is a pointer (so we need to derefence it and pass by reference)
    const Node &getParent() const { return *_parent; }

    bool hasFieldName2() const { return _FieldName2 != nullptr; }

    size_t getCount() const { return _fieldName3.size(); }

    bool hasFieldName3 const { return !_fieldName3.empty(); }

    void appendChild(std::shared_ptr<Node> child);

    // std::vector<Node &> getFlatTree(std::shared_ptr<Node> node);
    // std::vector<std::reference_wrapper<Node> getFlatTree(const Node &node);
    std::vector<std::shared_ptr<Node>> getFlatTree(std::shared_ptr<Node> node);

    bool swap(Node &node);

    std::shared_ptr<Node> copySubTree();

    void produce(std::string &production);

    void toProto(const Node &node, protobuf::Node* protoMessage);

private:
    bool subtreeContains(const Node &node) const;

    bool checkIfSwapOkay(const Node &node) const;

    // to get the const reference, we need to dereference (*) the raw pointer (.get())
    const Node &getChild(uint64_t index) const { return *_children[index].get(); }

    fromProto(std::shared_ptr<Node> node, const protobuf::Node &deserialProto);

    std::shared_ptr<Node> copyNode();

    // If member data is a "basic data type" (i.e. ints, shorts, pointers, chars) then
    // it should be initialized
    int _fieldName1 = -1;
    int _FieldName2 = -1;
    std::string _data;

    // Two things here:
    // 1. We want to either use a reference or a pointer because this 'parent' exists outside
    // of this class.
    // 2. We could use a reference, but references CANNOT be reassigned, so we couldn't implement
    // a "setParent" function. Instead, we use a pointer and expose it as a reference in the "get"
    // function above.
    Node *_parent = nullptr;
    std::vector<std::shared_ptr<Node>> _children;
};

#endif

}