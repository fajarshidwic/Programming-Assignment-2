#include "Node.h"

Node::Node(){
    data = nullptr;
    next = nullptr;
};

Node::Node(FoodItem* item, Node* next)
: data(data), next(next) {}

Node::~Node(){
};
