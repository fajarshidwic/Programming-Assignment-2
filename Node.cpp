#include "Node.h"

FoodItem::FoodItem(std::string id, std::string name, std::string description, double price, unsigned on_hand)
: id(id), name(name), description(description), on_hand(on_hand) {}

FoodItem::~FoodItem(){
};

Node::Node(){
    data = nullptr;
    next = nullptr;
};

Node::Node(FoodItem* data, Node* next)
: data(data), next(next) {}

Node::~Node(){
};
