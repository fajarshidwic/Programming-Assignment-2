#include "Node.h"
#include <cmath>

FoodItem::FoodItem(std::string id, std::string name, std::string description,  double price, unsigned on_hand)
: id(id), name(name), description(description), on_hand(on_hand) 
{
    price = price * 100;
    this->price.dollars = int(price / 100);
    this->price.cents = int(round(price - this->price.dollars*100));
}

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
