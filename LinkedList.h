#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    Coin* purse;

    // more functions to be added perhaps...

    void addFront(FoodItem* data);
    void addBack(FoodItem* data);
    void addAt(FoodItem* data, unsigned index);

    void removeFront();
    void removeBack();
    void removeAt(unsigned index);

    void printItems();

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H