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

    void addPopularItem(FoodItem* data);

    void removeFront();
    void removeBack();
    void removeAt(unsigned index);

    FoodItem* get(std::string id);

    Node* getBack();
    int getIndex(std::string itemID);

    void printItems();
    void printPopularItems();
    void printItems(std::ostream& outfile);
    void printCoins(std::ostream& outfile);

private:
    // the beginning of the list
    Node* head;
    Node* popularHead;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H